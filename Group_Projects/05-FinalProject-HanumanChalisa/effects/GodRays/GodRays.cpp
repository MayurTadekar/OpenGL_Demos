// ============================================================
// GodRays.cpp
// Screen-space volumetric god rays (light shaft) effect
//
// TECHNIQUE — Radial blur / light shaft march:
//   Pass 1 (Occlusion) : render a black disc at sun screen pos
//                         into an FBO — this masks the sun shape
//   Pass 2 (Ray March)  : radial blur from sun screen position
//                         outward — N samples along the ray vector
//                         weighted by decay/density/weight
//   Pass 3 (Composite)  : additive blend result onto scene
//
// Follows exact Skydome code style:
//   - step-numbered shader compile/link
//   - static GLuint globals for all state
//   - SkydomeParams → GodRaysParams pattern
//   - displayGodRaysImGui mirrors displaySkydomeImGui
// ============================================================

// header files
#include "../../include/common.h"
#include "../../modules/Camera/Camera.h"
#include "GodRays.h"

// ============================================================
// globals — shader programs
// ============================================================
static GLuint gProgOcclusion  = 0;   // pass 1: draw black sun disc
static GLuint gProgRayMarch   = 0;   // pass 2: radial blur
static GLuint gProgComposite  = 0;   // pass 3: additive blend

// ============================================================
// globals — occlusion disc uniforms
// ============================================================
static GLuint uOccSunScreenPos = 0;
static GLuint uOccDiscRadius   = 0;
static GLuint uOccResolution   = 0;

// ============================================================
// globals — ray march uniforms
// ============================================================
static GLuint uRayOcclusionTex = 0;
static GLuint uRaySunScreenPos = 0;
static GLuint uRayExposure     = 0;
static GLuint uRayDecay        = 0;
static GLuint uRayDensity      = 0;
static GLuint uRayWeight       = 0;
static GLuint uRayNumSamples   = 0;
static GLuint uRayColor        = 0;

// ============================================================
// globals — composite uniforms
// ============================================================
static GLuint uCompRayTex      = 0;
static GLuint uCompCoronaPos   = 0;
static GLuint uCompCoronaColor = 0;
static GLuint uCompCoronaSize  = 0;
static GLuint uCompCoronaStr   = 0;
static GLuint uCompShowCorona  = 0;
static GLuint uCompResolution  = 0;

// ============================================================
// globals — FBOs and textures
// ============================================================
static GLuint gFboOcclusion     = 0;
static GLuint gTexOcclusion     = 0;
static GLuint gFboRay           = 0;
static GLuint gTexRay           = 0;

// ============================================================
// globals — fullscreen quad geometry
// ============================================================
static GLuint gVAO              = 0;
static GLuint gVBO              = 0;

// FBO resolution — lower than screen for performance
// God rays at half-res look identical to full-res
static const int RAY_W = 512;
static const int RAY_H = 288;

// ============================================================
// Internal helper: compile one shader, log errors to gpFILE
// Follows project step numbering pattern
// ============================================================
static GLuint grCompileShader(GLenum type, const GLchar* src, const char* name)
{
	// step A : create shader object
	GLuint shaderObject = glCreateShader(type);

	// step B : give source code
	glShaderSource(shaderObject, 1, (const GLchar**)&src, NULL);

	// step C : compile
	glCompileShader(shaderObject);

	// step D : check compile status
	GLint  status       = 0;
	GLint  infoLogLength= 0;
	GLchar *szInfoLog   = NULL;

	glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		glGetShaderiv(shaderObject, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0)
		{
			szInfoLog = (GLchar*)malloc(sizeof(GLchar) * (infoLogLength + 1));
			if (szInfoLog != NULL)
			{
				glGetShaderInfoLog(shaderObject, infoLogLength + 1, NULL, szInfoLog);
				fprintf(gpFILE, "GodRays [%s] shader compile error: %s\n", name, szInfoLog);
				free(szInfoLog);
				szInfoLog = NULL;
			}
		}
	}

	return shaderObject;
}

// ============================================================
// Internal helper: link program, log errors to gpFILE
// ============================================================
static GLuint grLinkProgram(GLuint vs, GLuint fs, GLuint attribLoc, const char* attribName, const char* name)
{
	// step E : create program
	GLuint prog = glCreateProgram();

	// step F : attach
	glAttachShader(prog, vs);
	glAttachShader(prog, fs);

	// step G : bind attrib
	glBindAttribLocation(prog, attribLoc, attribName);

	// step H : link
	glLinkProgram(prog);

	// step I : check link status
	GLint  status       = 0;
	GLint  infoLogLength= 0;
	GLchar *szInfoLog   = NULL;

	glGetProgramiv(prog, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0)
		{
			szInfoLog = (GLchar*)malloc(sizeof(GLchar) * (infoLogLength + 1));
			if (szInfoLog != NULL)
			{
				glGetProgramInfoLog(prog, infoLogLength + 1, NULL, szInfoLog);
				fprintf(gpFILE, "GodRays [%s] program link error: %s\n", name, szInfoLog);
				free(szInfoLog);
				szInfoLog = NULL;
			}
		}
	}

	// step J : detach and delete individual shaders
	glDetachShader(prog, vs); glDeleteShader(vs);
	glDetachShader(prog, fs); glDeleteShader(fs);

	return prog;
}

// ============================================================
// Internal helper: create RGBA8 FBO at given resolution
// ============================================================
static void grMakeFBO(GLuint &fbo, GLuint &tex, int w, int h)
{
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex, 0);

	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE)
		fprintf(gpFILE, "GodRays FBO incomplete: 0x%X\n", status);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

// ============================================================
// initializeGodRays
// ============================================================
BOOL initializeGodRays(void)
{
	// code

	// =========================================================
	// PASS 1 — OCCLUSION DISC SHADER
	// Draws a black filled disc at the sun's screen position.
	// This creates the shadow mask that makes rays visible.
	//
	// Vertex shader : fullscreen quad, passes UV
	// Fragment shader: if pixel is within discRadius of sun → black
	//                  else → white (lit area)
	// =========================================================

	// step 1 : vertex shader code — occlusion pass
	const GLchar *vsOccSource =
		"#version 460 core\n"
		"in vec2 aPosition;\n"
		"out vec2 oUV;\n"
		"void main(void)\n"
		"{\n"
		"   oUV = aPosition * 0.5 + 0.5;\n"
		"   gl_Position = vec4(aPosition, 0.0, 1.0);\n"
		"}\n";

	// step 2 : fragment shader code — occlusion pass
	const GLchar *fsOccSource =
		"#version 460 core\n"
		"in vec2 oUV;\n"
		"uniform vec2  uSunScreenPos;\n"   // sun position in 0..1 UV space
		"uniform float uDiscRadius;\n"     // angular radius in screen space
		"uniform vec2  uResolution;\n"     // screen size for aspect correction
		"out vec4 FragColor;\n"
		"void main(void)\n"
		"{\n"
		"   vec2 aspect = vec2(uResolution.x / uResolution.y, 1.0);\n"
		"   vec2 delta  = (oUV - uSunScreenPos) * aspect;\n"
		"   float dist  = length(delta);\n"
		// black inside disc, white outside
		"   float mask  = step(uDiscRadius, dist);\n"
		"   FragColor   = vec4(mask, mask, mask, 1.0);\n"
		"}\n";

	// step 3 : compile occlusion shaders
	GLuint vsOcc = grCompileShader(GL_VERTEX_SHADER,   vsOccSource, "Occlusion VS");
	GLuint fsOcc = grCompileShader(GL_FRAGMENT_SHADER, fsOccSource, "Occlusion FS");

	// step 4 : link occlusion program
	gProgOcclusion = grLinkProgram(vsOcc, fsOcc, 0, "aPosition", "Occlusion");

	// step 5 : get occlusion uniform locations
	uOccSunScreenPos = glGetUniformLocation(gProgOcclusion, "uSunScreenPos");
	uOccDiscRadius   = glGetUniformLocation(gProgOcclusion, "uDiscRadius");
	uOccResolution   = glGetUniformLocation(gProgOcclusion, "uResolution");

	// =========================================================
	// PASS 2 — RAY MARCH SHADER
	// Radial blur from sun screen position outward.
	// Classic Crepuscular Rays technique (Volumetric Light Scattering).
	//
	// Each sample steps from current pixel toward sun,
	// accumulating the occlusion texture value, weighted by:
	//   illuminationDecay (fades with distance from sun)
	//   weight (per-sample brightness)
	// =========================================================

	// step 6 : vertex shader code — ray march pass (same quad VS)
	const GLchar *vsRaySource =
		"#version 460 core\n"
		"in vec2 aPosition;\n"
		"out vec2 oUV;\n"
		"void main(void)\n"
		"{\n"
		"   oUV = aPosition * 0.5 + 0.5;\n"
		"   gl_Position = vec4(aPosition, 0.0, 1.0);\n"
		"}\n";

	// step 7 : fragment shader code — ray march pass
	const GLchar *fsRaySource =
		"#version 460 core\n"
		"in vec2 oUV;\n"
		"uniform sampler2D uOcclusionTex;\n"  // result of pass 1
		"uniform vec2  uSunScreenPos;\n"      // sun UV position
		"uniform float uExposure;\n"
		"uniform float uDecay;\n"
		"uniform float uDensity;\n"
		"uniform float uWeight;\n"
		"uniform int   uNumSamples;\n"
		"uniform vec3  uRayColor;\n"
		"out vec4 FragColor;\n"
		"void main(void)\n"
		"{\n"
		// direction from pixel toward sun
		"   vec2 texCoord   = oUV;\n"
		"   vec2 deltaTexCoord = texCoord - uSunScreenPos;\n"
		"   deltaTexCoord  *= (1.0 / float(uNumSamples)) * uDensity;\n"
		"   float illuminationDecay = 1.0;\n"
		"   vec3  accumColor = vec3(0.0);\n"
		// march from pixel toward sun
		"   for (int i = 0; i < uNumSamples; i++)\n"
		"   {\n"
		"       texCoord    -= deltaTexCoord;\n"
		"       vec3 samp    = texture(uOcclusionTex, texCoord).rgb;\n"
		"       samp        *= illuminationDecay * uWeight;\n"
		"       accumColor  += samp;\n"
		"       illuminationDecay *= uDecay;\n"
		"   }\n"
		// apply exposure and tint
		"   accumColor   *= uExposure;\n"
		"   accumColor   *= uRayColor;\n"
		"   FragColor     = vec4(accumColor, 1.0);\n"
		"}\n";

	// step 8 : compile ray march shaders
	GLuint vsRay = grCompileShader(GL_VERTEX_SHADER,   vsRaySource, "RayMarch VS");
	GLuint fsRay = grCompileShader(GL_FRAGMENT_SHADER, fsRaySource, "RayMarch FS");

	// step 9 : link ray march program
	gProgRayMarch = grLinkProgram(vsRay, fsRay, 0, "aPosition", "RayMarch");

	// step 10 : get ray march uniform locations
	uRayOcclusionTex = glGetUniformLocation(gProgRayMarch, "uOcclusionTex");
	uRaySunScreenPos = glGetUniformLocation(gProgRayMarch, "uSunScreenPos");
	uRayExposure     = glGetUniformLocation(gProgRayMarch, "uExposure");
	uRayDecay        = glGetUniformLocation(gProgRayMarch, "uDecay");
	uRayDensity      = glGetUniformLocation(gProgRayMarch, "uDensity");
	uRayWeight       = glGetUniformLocation(gProgRayMarch, "uWeight");
	uRayNumSamples   = glGetUniformLocation(gProgRayMarch, "uNumSamples");
	uRayColor        = glGetUniformLocation(gProgRayMarch, "uRayColor");

	// =========================================================
	// PASS 3 — COMPOSITE SHADER
	// Additively blends ray texture onto the scene.
	// Also draws optional bright corona disc at sun center.
	// =========================================================

	// step 11 : vertex shader code — composite pass (same quad VS)
	const GLchar *vsCompSource =
		"#version 460 core\n"
		"in vec2 aPosition;\n"
		"out vec2 oUV;\n"
		"void main(void)\n"
		"{\n"
		"   oUV = aPosition * 0.5 + 0.5;\n"
		"   gl_Position = vec4(aPosition, 0.0, 1.0);\n"
		"}\n";

	// step 12 : fragment shader code — composite pass
	const GLchar *fsCompSource =
		"#version 460 core\n"
		"in vec2 oUV;\n"
		"uniform sampler2D uRayTex;\n"       // ray march result
		"uniform vec2  uCoronaPos;\n"        // sun screen pos UV
		"uniform vec3  uCoronaColor;\n"
		"uniform float uCoronaSize;\n"
		"uniform float uCoronaStrength;\n"
		"uniform int   uShowCorona;\n"
		"uniform vec2  uResolution;\n"
		"out vec4 FragColor;\n"
		"void main(void)\n"
		"{\n"
		"   vec3 rays = texture(uRayTex, oUV).rgb;\n"
		// corona — bright disc at sun center
		"   vec3 corona = vec3(0.0);\n"
		"   if (uShowCorona == 1)\n"
		"   {\n"
		"       vec2 aspect = vec2(uResolution.x / uResolution.y, 1.0);\n"
		"       vec2 delta  = (oUV - uCoronaPos) * aspect;\n"
		"       float dist  = length(delta);\n"
		// smooth soft disc falloff
		"       float corDisc = smoothstep(uCoronaSize, 0.0, dist);\n"
		"       corona = uCoronaColor * corDisc * uCoronaStrength;\n"
		"   }\n"
		"   FragColor = vec4(rays + corona, 1.0);\n"
		"}\n";

	// step 13 : compile composite shaders
	GLuint vsComp = grCompileShader(GL_VERTEX_SHADER,   vsCompSource, "Composite VS");
	GLuint fsComp = grCompileShader(GL_FRAGMENT_SHADER, fsCompSource, "Composite FS");

	// step 14 : link composite program
	gProgComposite = grLinkProgram(vsComp, fsComp, 0, "aPosition", "Composite");

	// step 15 : get composite uniform locations
	uCompRayTex      = glGetUniformLocation(gProgComposite, "uRayTex");
	uCompCoronaPos   = glGetUniformLocation(gProgComposite, "uCoronaPos");
	uCompCoronaColor = glGetUniformLocation(gProgComposite, "uCoronaColor");
	uCompCoronaSize  = glGetUniformLocation(gProgComposite, "uCoronaSize");
	uCompCoronaStr   = glGetUniformLocation(gProgComposite, "uCoronaStrength");
	uCompShowCorona  = glGetUniformLocation(gProgComposite, "uShowCorona");
	uCompResolution  = glGetUniformLocation(gProgComposite, "uResolution");

	// =========================================================
	// step 16 : create FBOs
	// gFboOcclusion — sun disc mask at half resolution
	// gFboRay       — ray march result at half resolution
	// =========================================================
	grMakeFBO(gFboOcclusion, gTexOcclusion, RAY_W, RAY_H);
	grMakeFBO(gFboRay,       gTexRay,       RAY_W, RAY_H);

	// =========================================================
	// step 17 : create fullscreen quad VAO/VBO
	// =========================================================
	GLfloat quadVerts[] = {
		-1.0f, -1.0f,
		 1.0f, -1.0f,
		-1.0f,  1.0f,
		-1.0f,  1.0f,
		 1.0f, -1.0f,
		 1.0f,  1.0f
	};

	glGenVertexArrays(1, &gVAO);
	// step 18 : bind VAO
	glBindVertexArray(gVAO);

	// step 19 : VBO
	glGenBuffers(1, &gVBO);
	glBindBuffer(GL_ARRAY_BUFFER, gVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVerts), quadVerts, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	fprintf(gpFILE, "GodRays initialized : FBO %dx%d\n", RAY_W, RAY_H);

	return TRUE;
}

// ============================================================
// renderGodRays
// Call after scene is rendered to screen.
// sceneDepthTexture : pass 0 to skip depth-based occlusion.
// ============================================================
void renderGodRays(GodRaysParams &params, Camera *pCamera,
                   vmath::mat4 projectionMatrix,
                   GLuint sceneDepthTexture)
{
	// code

	// ---- Project sun world position to screen UV space ----
	vmath::mat4 viewMat = pCamera->getLookAtMatrix();
	vmath::mat4 vpMat   = projectionMatrix * viewMat;

	// vmath does not support mat4*vec4 directly.
	// Multiply manually: sunClip[i] = dot(row_i(vpMat), sunWorld)
	float wx = params.sunWorldPos[0];
	float wy = params.sunWorldPos[1];
	float wz = params.sunWorldPos[2];
	float ww = 1.0f;

	float clipX = vpMat[0][0]*wx + vpMat[1][0]*wy + vpMat[2][0]*wz + vpMat[3][0]*ww;
	float clipY = vpMat[0][1]*wx + vpMat[1][1]*wy + vpMat[2][1]*wz + vpMat[3][1]*ww;
	float clipZ = vpMat[0][2]*wx + vpMat[1][2]*wy + vpMat[2][2]*wz + vpMat[3][2]*ww;
	float clipW = vpMat[0][3]*wx + vpMat[1][3]*wy + vpMat[2][3]*wz + vpMat[3][3]*ww;

	// if sun is behind camera, skip rendering
	if (clipW <= 0.0f)
		return;

	// perspective divide → NDC → UV [0,1]
	float sunNdcX = clipX / clipW;
	float sunNdcY = clipY / clipW;
	float sunUVX  = sunNdcX * 0.5f + 0.5f;
	float sunUVY  = sunNdcY * 0.5f + 0.5f;

	// save screen viewport
	GLint prevVP[4];
	glGetIntegerv(GL_VIEWPORT, prevVP);
	GLint prevFBO;
	glGetIntegerv(GL_FRAMEBUFFER_BINDING, &prevFBO);

	float screenW = (float)prevVP[2];
	float screenH = (float)prevVP[3];

	// =========================================================
	// PASS 1 — render occlusion disc into gFboOcclusion
	// =========================================================
	glBindFramebuffer(GL_FRAMEBUFFER, gFboOcclusion);
	glViewport(0, 0, RAY_W, RAY_H);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);  // white = fully lit
	glClear(GL_COLOR_BUFFER_BIT);

	if (params.bShowOcclusionDisc)
	{
		glUseProgram(gProgOcclusion);
		glUniform2f(uOccSunScreenPos, sunUVX, sunUVY);
		glUniform1f(uOccDiscRadius,   params.discRadius);
		glUniform2f(uOccResolution,   (float)RAY_W, (float)RAY_H);

		glBindVertexArray(gVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
		glUseProgram(0);
	}

	// =========================================================
	// PASS 2 — ray march from sun position → gFboRay
	// =========================================================
	glBindFramebuffer(GL_FRAMEBUFFER, gFboRay);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(gProgRayMarch);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gTexOcclusion);
	glUniform1i(uRayOcclusionTex, 0);

	glUniform2f(uRaySunScreenPos, sunUVX, sunUVY);
	glUniform1f(uRayExposure,     params.exposure);
	glUniform1f(uRayDecay,        params.decay);
	glUniform1f(uRayDensity,      params.density);
	glUniform1f(uRayWeight,       params.weight);
	glUniform1i(uRayNumSamples,   params.numSamples);
	glUniform3fv(uRayColor,    1, params.rayColor);

	glBindVertexArray(gVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);

	// =========================================================
	// PASS 3 — composite onto screen (additive blend)
	// =========================================================
	glBindFramebuffer(GL_FRAMEBUFFER, prevFBO);
	glViewport(prevVP[0], prevVP[1], prevVP[2], prevVP[3]);

	// additive blend — rays add light on top of scene
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);

	// disable depth test — 2D fullscreen overlay
	GLboolean depthWasEnabled = glIsEnabled(GL_DEPTH_TEST);
	glDisable(GL_DEPTH_TEST);

	glUseProgram(gProgComposite);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gTexRay);
	glUniform1i(uCompRayTex, 0);

	glUniform2f(uCompCoronaPos,   sunUVX, sunUVY);
	glUniform3fv(uCompCoronaColor, 1, params.coronaColor);
	glUniform1f(uCompCoronaSize,  params.coronaSize);
	glUniform1f(uCompCoronaStr,   params.coronaStrength);
	glUniform1i(uCompShowCorona,  params.bShowCorona ? 1 : 0);
	glUniform2f(uCompResolution,  screenW, screenH);

	glBindVertexArray(gVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);

	// restore state
	glDisable(GL_BLEND);
	if (depthWasEnabled) glEnable(GL_DEPTH_TEST);
}

// ============================================================
// displayGodRaysImGui
// Follows exact same pattern as displaySkydomeImGui
// ============================================================
void displayGodRaysImGui(GodRaysParams &params)
{
	if (ImGui::CollapsingHeader("God Rays", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::Separator();
		ImGui::Text("--- Sun Position ---");
		ImGui::DragFloat3("Sun World Pos", &params.sunWorldPos[0], 1.0f);

		ImGui::Separator();
		ImGui::Text("--- Ray Appearance ---");
		ImGui::ColorEdit3("Ray Color",    &params.rayColor[0]);
		ImGui::DragFloat("Exposure",      &params.exposure,    0.01f, 0.01f, 2.0f);
		ImGui::DragFloat("Decay",         &params.decay,       0.001f, 0.80f, 1.0f);
		ImGui::DragFloat("Density",       &params.density,     0.01f, 0.1f, 2.0f);
		ImGui::DragFloat("Weight",        &params.weight,      0.01f, 0.01f, 2.0f);
		ImGui::DragInt("Num Samples",     &params.numSamples,  1,     16,    128);

		ImGui::Separator();
		ImGui::Text("--- Occlusion Disc ---");
		ImGui::Checkbox("Show Occlusion Disc", (bool*)&params.bShowOcclusionDisc);
		if (params.bShowOcclusionDisc)
			ImGui::DragFloat("Disc Radius", &params.discRadius, 0.001f, 0.01f, 0.5f);

		ImGui::Separator();
		ImGui::Text("--- Corona ---");
		ImGui::Checkbox("Show Corona",        (bool*)&params.bShowCorona);
		if (params.bShowCorona)
		{
			ImGui::ColorEdit3("Corona Color",  &params.coronaColor[0]);
			ImGui::DragFloat("Corona Size",    &params.coronaSize,     0.001f, 0.01f, 0.5f);
			ImGui::DragFloat("Corona Strength",&params.coronaStrength, 0.1f,   0.1f, 10.0f);
		}
	}
}

// ============================================================
// uninitializeGodRays
// Follows exact same cleanup pattern as uninitializeSkydome
// ============================================================
void uninitializeGodRays(void)
{
	// code

	if (gTexOcclusion)
	{
		glDeleteTextures(1, &gTexOcclusion);
		gTexOcclusion = 0;
	}

	if (gTexRay)
	{
		glDeleteTextures(1, &gTexRay);
		gTexRay = 0;
	}

	if (gFboOcclusion)
	{
		glDeleteFramebuffers(1, &gFboOcclusion);
		gFboOcclusion = 0;
	}

	if (gFboRay)
	{
		glDeleteFramebuffers(1, &gFboRay);
		gFboRay = 0;
	}

	if (gVBO)
	{
		glDeleteBuffers(1, &gVBO);
		gVBO = 0;
	}

	if (gVAO)
	{
		glDeleteVertexArrays(1, &gVAO);
		gVAO = 0;
	}

	if (gProgOcclusion)
	{
		glUseProgram(gProgOcclusion);
		GLint numShaders = 0;
		glGetProgramiv(gProgOcclusion, GL_ATTACHED_SHADERS, &numShaders);
		if (numShaders > 0)
		{
			GLuint *pShaders = (GLuint*)malloc(numShaders * sizeof(GLuint));
			if (pShaders != NULL)
			{
				glGetAttachedShaders(gProgOcclusion, numShaders, NULL, pShaders);
				for (GLint i = 0; i < numShaders; i++) { glDetachShader(gProgOcclusion, pShaders[i]); glDeleteShader(pShaders[i]); }
				free(pShaders);
			}
		}
		glUseProgram(0);
		glDeleteProgram(gProgOcclusion);
		gProgOcclusion = 0;
	}

	if (gProgRayMarch)
	{
		glUseProgram(gProgRayMarch);
		GLint numShaders = 0;
		glGetProgramiv(gProgRayMarch, GL_ATTACHED_SHADERS, &numShaders);
		if (numShaders > 0)
		{
			GLuint *pShaders = (GLuint*)malloc(numShaders * sizeof(GLuint));
			if (pShaders != NULL)
			{
				glGetAttachedShaders(gProgRayMarch, numShaders, NULL, pShaders);
				for (GLint i = 0; i < numShaders; i++) { glDetachShader(gProgRayMarch, pShaders[i]); glDeleteShader(pShaders[i]); }
				free(pShaders);
			}
		}
		glUseProgram(0);
		glDeleteProgram(gProgRayMarch);
		gProgRayMarch = 0;
	}

	if (gProgComposite)
	{
		glUseProgram(gProgComposite);
		GLint numShaders = 0;
		glGetProgramiv(gProgComposite, GL_ATTACHED_SHADERS, &numShaders);
		if (numShaders > 0)
		{
			GLuint *pShaders = (GLuint*)malloc(numShaders * sizeof(GLuint));
			if (pShaders != NULL)
			{
				glGetAttachedShaders(gProgComposite, numShaders, NULL, pShaders);
				for (GLint i = 0; i < numShaders; i++) { glDetachShader(gProgComposite, pShaders[i]); glDeleteShader(pShaders[i]); }
				free(pShaders);
			}
		}
		glUseProgram(0);
		glDeleteProgram(gProgComposite);
		gProgComposite = 0;
	}

	fprintf(gpFILE, "GodRays uninitialized\n");
}
