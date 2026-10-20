// header files
#include "../../include/common.h"
#include "../../modules/Camera/Camera.h"
#include "Skydome.h"

// globalS
static GLuint shaderProgramObject = 0;

// uniforms
static GLuint modelMatrixUniform = 0;
static GLuint viewMatrixUniform = 0;
static GLuint projectionMatrixUniform = 0;

// gradient uniforms
static GLuint uColorZenithUniform = 0;
static GLuint uColorMidUpperUniform = 0;
static GLuint uColorMidLowerUniform = 0;
static GLuint uColorHorizonUniform = 0;
static GLuint uStopMidUpperUniform = 0;
static GLuint uStopMidLowerUniform = 0;
static GLuint uStopHorizonUniform = 0;

// sun uniforms
static GLuint uShowSunUniform = 0;
static GLuint uSunColorUniform = 0;
static GLuint uSunDirectionUniform = 0;
static GLuint uSunSizeUniform = 0;
static GLuint uSunGlowSizeUniform = 0;
static GLuint uSunGlowStrengthUniform = 0;

// exposure
static GLuint uExposureUniform = 0;

// geometry
static GLuint vao = 0;
static GLuint vbo = 0;
static GLuint ebo = 0;
static GLuint g_indexCount = 0;

// Global selection scene
extern int selected_scene;

BOOL initializeSkydome(void)
{
	// code

	// Vertex Shader
	// step 1 : vertex shader code
	const GLchar *vertexShaderSourceCode =
		"#version 460 core\n"
		"in vec4 aPosition;\n"

		"uniform mat4 uModelMatrix;\n"
		"uniform mat4 uViewMatrix;\n"
		"uniform mat4 uProjectionMatrix;\n"

		"out vec3 oWorldPos;\n"

		"void main(void)\n"
		"{\n"
		"   vec4 worldPos   = uModelMatrix * aPosition;\n"
		"   oWorldPos       = worldPos.xyz;\n"
		"   mat4 viewNoTrans       = uViewMatrix;\n"
		"   viewNoTrans[3][0]      = 0.0;\n"
		"   viewNoTrans[3][1]      = 0.0;\n"
		"   viewNoTrans[3][2]      = 0.0;\n"

		"   vec4 clipPos    = uProjectionMatrix * viewNoTrans * uModelMatrix * aPosition;\n"
		"   gl_Position = clipPos.xyww;\n"
		"}\n";

	// step 2 : create vertex shader object
	GLuint vertexShaderObject = glCreateShader(GL_VERTEX_SHADER);

	// step 3 : give vertex source code to openGL
	glShaderSource(vertexShaderObject, 1, (const GLchar **)&vertexShaderSourceCode, NULL);

	// step 4 : let OpenGL compile vertex shader
	glCompileShader(vertexShaderObject);

	// step 5
	GLint status = 0;
	GLint infoLogLength = 0;
	GLchar *szInfoLog = NULL;

	// step 5 a
	glGetShaderiv(vertexShaderObject, GL_COMPILE_STATUS, &status);

	// step 5 b
	if (status == GL_FALSE)
	{
		glGetShaderiv(vertexShaderObject, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0)
		{
			// step 5 c
			szInfoLog = (GLchar *)malloc(sizeof(GLchar) * (infoLogLength + 1));
			if (szInfoLog != NULL)
			{
				// step 5 d
				glGetShaderInfoLog(vertexShaderObject, infoLogLength + 1, NULL, szInfoLog);
				// step 5 e
				fprintf(gpFILE, "Skydome vertex shader compilation error log : %s\n", szInfoLog);
				// step 5 f
				free(szInfoLog);
				szInfoLog = NULL;
			}
		}
		// step 5 g
		uninitialize();
	}

	// Fragment Shader
	// step 6 : fragment shader code
	const GLchar *fragmentShaderSourceCode =
		"#version 460 core\n"
		"in vec3 oWorldPos;\n"

		// gradient
		"uniform vec3  uColorZenith;\n"
		"uniform vec3  uColorMidUpper;\n"
		"uniform vec3  uColorMidLower;\n"
		"uniform vec3  uColorHorizon;\n"
		"uniform float uStopMidUpper;\n"
		"uniform float uStopMidLower;\n"
		"uniform float uStopHorizon;\n"

		// sun
		"uniform int   uShowSun;\n"
		"uniform vec3  uSunColor;\n"
		"uniform vec3  uSunDirection;\n" // normalised, points TOWARD sun
		"uniform float uSunSize;\n"
		"uniform float uSunGlowSize;\n"
		"uniform float uSunGlowStrength;\n"

		// exposure
		"uniform float uExposure;\n"

		"out vec4 FragColor;\n"

		"void main(void)\n"
		"{\n"

		"   vec3  dir    = normalize(oWorldPos);\n"
		"   float height = clamp(dir.y, 0.0, 1.0);\n"

		// ---- 4-stop gradient ----
		// stop0=horizon(0)  stop1=midLower  stop2=midUpper  stop3=zenith(1)
		"   vec3 skyColor;\n"

		// horizon → midLower
		"   if (height < uStopMidLower)\n"
		"   {\n"
		"       float t = height / uStopMidLower;\n"
		"       skyColor = mix(uColorHorizon, uColorMidLower, smoothstep(0.0, 1.0, t));\n"
		"   }\n"
		// midLower → midUpper
		"   else if (height < uStopMidUpper)\n"
		"   {\n"
		"       float t = (height - uStopMidLower) / (uStopMidUpper - uStopMidLower);\n"
		"       skyColor = mix(uColorMidLower, uColorMidUpper, smoothstep(0.0, 1.0, t));\n"
		"   }\n"
		// midUpper → zenith
		"   else\n"
		"   {\n"
		"       float t = (height - uStopMidUpper) / (1.0 - uStopMidUpper);\n"
		"       skyColor = mix(uColorMidUpper, uColorZenith, smoothstep(0.0, 1.0, t));\n"
		"   }\n"

		// ---- Sun disc + glow ----
		"   if (uShowSun == 1)\n"
		"   {\n"
		"       vec3  sunDir  = normalize(uSunDirection);\n"
		"       float cosAngle = dot(dir, sunDir);\n"

		// sharp disc
		"       float disc = smoothstep(uSunSize - 0.0005, uSunSize, cosAngle);\n"

		// soft glow around disc
		"       float glow = smoothstep(uSunGlowSize, uSunSize, cosAngle) * uSunGlowStrength;\n"

		"       skyColor += uSunColor * disc;\n"
		"       skyColor += uSunColor * glow;\n"
		"   }\n"

		// exposure
		"   skyColor *= uExposure;\n"

		"   FragColor = vec4(skyColor, 1.0);\n"
		"}\n";

	// step 7 : create fragment shader object
	GLuint fragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);

	// step 8 : give fragment shader source code to OpenGL
	glShaderSource(fragmentShaderObject, 1, (const GLchar **)&fragmentShaderSourceCode, NULL);

	// step 9 : let OpenGL compile fragment shader
	glCompileShader(fragmentShaderObject);

	// step 10
	status = 0;
	infoLogLength = 0;
	szInfoLog = NULL;

	// step 10 a
	glGetShaderiv(fragmentShaderObject, GL_COMPILE_STATUS, &status);

	// step 10 b
	if (status == GL_FALSE)
	{
		glGetShaderiv(fragmentShaderObject, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0)
		{
			// step 10 c
			szInfoLog = (GLchar *)malloc(sizeof(GLchar) * (infoLogLength + 1));
			if (szInfoLog != NULL)
			{
				// step 10 d
				glGetShaderInfoLog(fragmentShaderObject, infoLogLength + 1, NULL, szInfoLog);
				// step 10 e
				fprintf(gpFILE, "Skydome fragment shader compilation error log : %s\n", szInfoLog);
				// step 10 f
				free(szInfoLog);
				szInfoLog = NULL;
			}
		}
		// step 10 g
		uninitialize();
	}

	// step 11 : create shader program object
	shaderProgramObject = glCreateProgram();

	// step 12 : attach shaders
	glAttachShader(shaderProgramObject, vertexShaderObject);
	glAttachShader(shaderProgramObject, fragmentShaderObject);

	// step 13 : bind attribute location
	glBindAttribLocation(shaderProgramObject, AMC_ATTRIBUTE_POSITION, "aPosition");

	// step 14 : link the shader program
	glLinkProgram(shaderProgramObject);

	// step 15 : linking error check
	status = 0;
	infoLogLength = 0;
	szInfoLog = NULL;

	// step 15 a
	glGetProgramiv(shaderProgramObject, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		glGetProgramiv(shaderProgramObject, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0)
		{
			// step 15 c
			szInfoLog = (GLchar *)malloc(sizeof(GLchar) * (infoLogLength + 1));
			if (szInfoLog != NULL)
			{
				// step 15 d
				glGetProgramInfoLog(shaderProgramObject, infoLogLength + 1, NULL, szInfoLog);
				// step 15 e
				fprintf(gpFILE, "Skydome shader program linking error log : %s\n", szInfoLog);
				// step 15 f
				free(szInfoLog);
				szInfoLog = NULL;
			}
		}
		// step 15 g
		uninitialize();
	}

	// step 16 : get uniform locations
	modelMatrixUniform = glGetUniformLocation(shaderProgramObject, "uModelMatrix");
	viewMatrixUniform = glGetUniformLocation(shaderProgramObject, "uViewMatrix");
	projectionMatrixUniform = glGetUniformLocation(shaderProgramObject, "uProjectionMatrix");

	uColorZenithUniform = glGetUniformLocation(shaderProgramObject, "uColorZenith");
	uColorMidUpperUniform = glGetUniformLocation(shaderProgramObject, "uColorMidUpper");
	uColorMidLowerUniform = glGetUniformLocation(shaderProgramObject, "uColorMidLower");
	uColorHorizonUniform = glGetUniformLocation(shaderProgramObject, "uColorHorizon");
	uStopMidUpperUniform = glGetUniformLocation(shaderProgramObject, "uStopMidUpper");
	uStopMidLowerUniform = glGetUniformLocation(shaderProgramObject, "uStopMidLower");
	uStopHorizonUniform = glGetUniformLocation(shaderProgramObject, "uStopHorizon");

	uShowSunUniform = glGetUniformLocation(shaderProgramObject, "uShowSun");
	uSunColorUniform = glGetUniformLocation(shaderProgramObject, "uSunColor");
	uSunDirectionUniform = glGetUniformLocation(shaderProgramObject, "uSunDirection");
	uSunSizeUniform = glGetUniformLocation(shaderProgramObject, "uSunSize");
	uSunGlowSizeUniform = glGetUniformLocation(shaderProgramObject, "uSunGlowSize");
	uSunGlowStrengthUniform = glGetUniformLocation(shaderProgramObject, "uSunGlowStrength");

	uExposureUniform = glGetUniformLocation(shaderProgramObject, "uExposure");

	// step 17 : build dome sphere geometry
	const int STACKS = 32;
	const int SECTORS = 64;
	int vertCount = (STACKS + 1) * (SECTORS + 1);
	float *verts = (float *)malloc(sizeof(float) * vertCount * 3);

	int vi = 0;
	for (int s = 0; s <= STACKS; s++)
	{
		// phi: from PI (bottom) to 0 (top) — full sphere
		float phi = (float)M_PI - ((float)s / (float)STACKS) * (float)M_PI;
		float sinPhi = sinf(phi);
		float cosPhi = cosf(phi);

		for (int t = 0; t <= SECTORS; t++)
		{
			float theta = ((float)t / (float)SECTORS) * 2.0f * (float)M_PI;
			float sinTheta = sinf(theta);
			float cosTheta = cosf(theta);

			verts[vi++] = cosTheta * sinPhi; // x
			verts[vi++] = cosPhi;			 // y
			verts[vi++] = sinTheta * sinPhi; // z
		}
	}

	// indices
	int idxCount = STACKS * SECTORS * 6;
	GLuint *indices = (GLuint *)malloc(sizeof(GLuint) * idxCount);
	g_indexCount = idxCount;

	int ii = 0;
	for (int s = 0; s < STACKS; s++)
	{
		for (int t = 0; t < SECTORS; t++)
		{
			GLuint tl = s * (SECTORS + 1) + t;
			GLuint tr = s * (SECTORS + 1) + t + 1;
			GLuint bl = (s + 1) * (SECTORS + 1) + t;
			GLuint br = (s + 1) * (SECTORS + 1) + t + 1;

			indices[ii++] = tl;
			indices[ii++] = bl;
			indices[ii++] = tr;
			indices[ii++] = tr;
			indices[ii++] = bl;
			indices[ii++] = br;
		}
	}

	// step 18 : create VAO
	glGenVertexArrays(1, &vao);

	// step 19 : bind VAO
	glBindVertexArray(vao);

	// step 20 : VBO for positions
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertCount * 3, verts, GL_STATIC_DRAW);
	glVertexAttribPointer(AMC_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(AMC_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// EBO
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * idxCount, indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	free(verts);
	free(indices);

	fprintf(gpFILE, "Skydome initialized : %d verts, %d indices\n", vertCount, idxCount);

	return (TRUE);
}

void renderSkydome(SkydomeParams &params, Camera *pCamera, vmath::mat4 projectionMatrix)
{
	// variable declarations
	if (selected_scene == SCENE_OCEAN)
	{
		params.sunDirection = vmath::vec3(0.0f, 100.0f, -800.0f);
	}
	else if (selected_scene == SCENE_RAM_VACHAN)
	{
		params.sunDirection = vmath::vec3(0.0f, 150.0f, -800.0f);
	}
	else
	{
		params.sunDirection = vmath::vec3(0.0f, 100.0f, -800.0f);
	}

	// code
	glUseProgram(shaderProgramObject);

	// model matrix: scale unit sphere to domeRadius, apply Y offset
	vmath::mat4 modelMatrix =
		vmath::translate(0.0f, params.domeYOffset, 0.0f) *
		vmath::scale(params.domeRadius, params.domeRadius, params.domeRadius);

	glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, modelMatrix);
	glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, pCamera->getLookAtMatrix());
	glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, projectionMatrix);

	// gradient uniforms
	glUniform3fv(uColorZenithUniform, 1, params.colorZenith);
	glUniform3fv(uColorMidUpperUniform, 1, params.colorMidUpper);
	glUniform3fv(uColorMidLowerUniform, 1, params.colorMidLower);
	glUniform3fv(uColorHorizonUniform, 1, params.colorHorizon);
	glUniform1f(uStopMidUpperUniform, params.stopMidUpper);
	glUniform1f(uStopMidLowerUniform, params.stopMidLower);
	glUniform1f(uStopHorizonUniform, params.stopHorizon);

	// sun uniforms
	glUniform1i(uShowSunUniform, params.bShowSun ? 1 : 0);
	glUniform3fv(uSunColorUniform, 1, params.sunColor);
	vmath::vec3 sunDirN = vmath::normalize(params.sunDirection);
	glUniform3fv(uSunDirectionUniform, 1, sunDirN);
	glUniform1f(uSunSizeUniform, params.sunSize);
	glUniform1f(uSunGlowSizeUniform, params.sunGlowSize);
	glUniform1f(uSunGlowStrengthUniform, params.sunGlowStrength);

	// exposure
	glUniform1f(uExposureUniform, params.exposure);

	glDepthMask(GL_FALSE);
	glDepthFunc(GL_LEQUAL);

	glBindVertexArray(vao);
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glDrawElements(GL_TRIANGLES, g_indexCount, GL_UNSIGNED_INT, NULL);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	glBindVertexArray(0);

	// restore depth state
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);

	glUseProgram(0);
}

void setupSkydomeDefaults(SkydomeParams skydomeParams[])
{
	// Evening scene: blue above, orange-red near horizon
	skydomeParams[0].colorZenith     = vmath::vec3(0.42f, 0.58f, 0.78f);
	skydomeParams[0].colorMidUpper   = vmath::vec3(0.48f, 0.62f, 0.80f);
	skydomeParams[0].colorMidLower   = vmath::vec3(103.0f / 255.0f, 146.0f / 255.0f, 215.0f / 255.0f);
	skydomeParams[0].colorHorizon    = vmath::vec3(218.0f / 255.0f, 231.0f / 255.0f, 254.0f / 255.0f);

	skydomeParams[0].stopMidUpper    = 0.78f;
	skydomeParams[0].stopMidLower    = 0.18f;
	skydomeParams[0].stopHorizon     = 0.05f;

	skydomeParams[0].bShowSun        = TRUE;
	skydomeParams[0].sunDirection    = vmath::vec3(0.0f, 22.0f, -800.0f);

	skydomeParams[0].sunColor        = vmath::vec3(0.84f, 0.55f, 0.13f);
	skydomeParams[0].sunSize         = 0.9985f;
	skydomeParams[0].sunGlowSize     = 0.985f;
	skydomeParams[0].sunGlowStrength = 0.37f;

	skydomeParams[0].domeRadius      = 900.0f;
	skydomeParams[0].domeYOffset     = -100.0f;

	skydomeParams[0].domeStacks      = 32;
	skydomeParams[0].domeSectors     = 64;

	skydomeParams[0].exposure        = 0.920f;

	// Index 1: Flying
		// skydomeParams[1].colorZenith = vmath::vec3(0.1f, 0.2f, 0.4f);
		// skydomeParams[1].colorMidUpper = vmath::vec3(0.2f, 0.4f, 0.6f);
		// skydomeParams[1].colorMidLower = vmath::vec3(0.4f, 0.6f, 0.8f);
		// skydomeParams[1].colorHorizon = vmath::vec3(0.6f, 0.8f, 1.0f);

		// skydomeParams[1].stopMidUpper = 0.72f;
		// skydomeParams[1].stopMidLower = 0.30f;
		// skydomeParams[1].stopHorizon = 0.08f;

		// skydomeParams[1].bShowSun = TRUE;
		// skydomeParams[1].sunDirection = vmath::vec3(0.0f, 100.0f, -800.0f); // same as godRays sun

		// skydomeParams[1].sunColor = vmath::vec3(1.00f, 0.82f, 0.65f);
		// skydomeParams[1].sunSize = 0.9975f;
		// skydomeParams[1].sunGlowSize = 0.978f;
		// skydomeParams[1].sunGlowStrength = 0.40f;

		// skydomeParams[1].domeRadius = 900.0f;
		// skydomeParams[1].domeYOffset = -100.0f;

		// skydomeParams[1].domeStacks = 32;
		// skydomeParams[1].domeSectors = 64;

		// skydomeParams[1].exposure = 1.08f;

	// Index 2: Ocean (Stormy/Darker Blue)
		// skydomeParams[2].colorZenith = vmath::vec3(0.05f, 0.10f, 0.20f);
		// skydomeParams[2].colorMidUpper = vmath::vec3(0.10f, 0.15f, 0.25f);
		// skydomeParams[2].colorMidLower = vmath::vec3(0.15f, 0.20f, 0.30f);
		// skydomeParams[2].colorHorizon = vmath::vec3(0.25f, 0.30f, 0.35f);

		// skydomeParams[2].stopMidUpper = 0.75f;
		// skydomeParams[2].stopMidLower = 0.35f;
		// skydomeParams[2].stopHorizon = 0.10f;

		// skydomeParams[2].bShowSun = TRUE;
		// skydomeParams[2].sunDirection = vmath::vec3(0.0f, 100.0f, -800.0f);
		// skydomeParams[2].sunColor = vmath::vec3(0.9f, 0.85f, 0.75f);
		// skydomeParams[2].sunSize = 0.998f;
		// skydomeParams[2].sunGlowSize = 0.985f;
		// skydomeParams[2].sunGlowStrength = 0.30f;

		// skydomeParams[2].domeRadius = 1500.0f;
		// skydomeParams[2].domeYOffset = -150.0f;
		// skydomeParams[2].exposure = 1.0f;

	// Index 3: Ram Vachan (Twilight/Night)
		skydomeParams[3].colorZenith = vmath::vec3(0.32f, 0.28f, 0.38f);
		skydomeParams[3].colorMidUpper = vmath::vec3(0.55f, 0.42f, 0.45f);
		skydomeParams[3].colorMidLower = vmath::vec3(0.82f, 0.55f, 0.42f);
		skydomeParams[3].colorHorizon = vmath::vec3(1.00f, 0.72f, 0.50f);

		skydomeParams[3].stopMidUpper = 0.72f;
		skydomeParams[3].stopMidLower = 0.30f;
		skydomeParams[3].stopHorizon = 0.08f;

		skydomeParams[3].bShowSun = TRUE;
		skydomeParams[3].sunDirection = vmath::vec3(0.0f, 100.0f, -800.0f); // same as godRays sun

		skydomeParams[3].sunColor = vmath::vec3(1.00f, 0.82f, 0.65f);
		skydomeParams[3].sunSize = 0.9975f;
		skydomeParams[3].sunGlowSize = 0.978f;
		skydomeParams[3].sunGlowStrength = 0.40f;

		skydomeParams[3].domeRadius = 900.0f;
		skydomeParams[3].domeYOffset = -100.0f;

		skydomeParams[3].domeStacks = 32;
		skydomeParams[3].domeSectors = 64;

		skydomeParams[3].exposure = 1.08f;

	// Index 4: Ram Worship (Divine/Morning Gold)
		skydomeParams[4].colorZenith = vmath::vec3(0.20f, 0.45f, 0.85f);
		skydomeParams[4].colorMidUpper = vmath::vec3(0.40f, 0.65f, 0.95f);
		skydomeParams[4].colorMidLower = vmath::vec3(0.85f, 0.75f, 0.45f);
		skydomeParams[4].colorHorizon = vmath::vec3(1.00f, 0.90f, 0.60f);

		skydomeParams[4].stopMidUpper = 0.70f;
		skydomeParams[4].stopMidLower = 0.25f;
		skydomeParams[4].stopHorizon = 0.05f;

		skydomeParams[4].bShowSun = TRUE;
		skydomeParams[4].sunDirection = vmath::vec3(1.0f, 0.5f, -1.0f);
		skydomeParams[4].sunColor = vmath::vec3(1.0f, 1.0f, 0.9f);
		skydomeParams[4].sunSize = 0.9975f;
		skydomeParams[4].sunGlowSize = 0.975f;
		skydomeParams[4].sunGlowStrength = 0.50f;

		skydomeParams[4].domeRadius = 2000.0f;
		skydomeParams[4].domeYOffset = -200.0f;
		skydomeParams[4].exposure = 1.15f;	
}

void displaySkydomeImGui(SkydomeParams &params)
{
	if (ImGui::CollapsingHeader("Skydome", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::Separator();
		ImGui::Text("--- Gradient Colors ---");
		ImGui::ColorEdit3("Zenith", &params.colorZenith[0]);
		ImGui::ColorEdit3("Mid Upper", &params.colorMidUpper[0]);
		ImGui::ColorEdit3("Mid Lower", &params.colorMidLower[0]);
		ImGui::ColorEdit3("Horizon", &params.colorHorizon[0]);

		ImGui::Separator();
		ImGui::Text("--- Gradient Stops [0=horizon, 1=zenith] ---");
		ImGui::DragFloat("Stop Mid Upper", &params.stopMidUpper, 0.01f, params.stopMidLower + 0.01f, 1.0f);
		ImGui::DragFloat("Stop Mid Lower", &params.stopMidLower, 0.01f, 0.01f, params.stopMidUpper - 0.01f);

		ImGui::Separator();
		ImGui::Text("--- Sun ---");
		ImGui::Checkbox("Show Sun", (bool *)&params.bShowSun);
		if (params.bShowSun)
		{
			ImGui::ColorEdit3("Sun Color", &params.sunColor[0]);
			ImGui::DragFloat3("Sun Direction", &params.sunDirection[0], 0.01f, -1.0f, 1.0f);
			ImGui::DragFloat("Sun Size", &params.sunSize, 0.0001f, 0.990f, 0.9999f);
			ImGui::DragFloat("Glow Size", &params.sunGlowSize, 0.001f, 0.900f, params.sunSize);
			ImGui::DragFloat("Glow Strength", &params.sunGlowStrength, 0.01f, 0.0f, 2.0f);
		}

		ImGui::Separator();
		ImGui::Text("--- Dome Shape ---");
		ImGui::DragFloat("Dome Radius", &params.domeRadius, 10.0f, 100.0f, 5000.0f);
		ImGui::DragFloat("Y Offset", &params.domeYOffset, 1.0f, -500.0f, 0.0f);
		ImGui::DragFloat("Exposure", &params.exposure, 0.01f, 0.1f, 3.0f);
	}
}

void uninitializeSkydome(void)
{
	// code
	if (ebo)
	{
		glDeleteBuffers(1, &ebo);
		ebo = 0;
	}

	if (vbo)
	{
		glDeleteBuffers(1, &vbo);
		vbo = 0;
	}

	if (vao)
	{
		glDeleteVertexArrays(1, &vao);
		vao = 0;
	}

	if (shaderProgramObject)
	{
		glUseProgram(shaderProgramObject);

		GLint numShaders = 0;
		glGetProgramiv(shaderProgramObject, GL_ATTACHED_SHADERS, &numShaders);

		if (numShaders > 0)
		{
			GLuint *pShaders = (GLuint *)malloc(numShaders * sizeof(GLuint));
			if (pShaders != NULL)
			{
				glGetAttachedShaders(shaderProgramObject, numShaders, NULL, pShaders);
				for (GLint i = 0; i < numShaders; i++)
				{
					glDetachShader(shaderProgramObject, pShaders[i]);
					glDeleteShader(pShaders[i]);
					pShaders[i] = 0;
				}
				free(pShaders);
				pShaders = NULL;
			}
		}

		glUseProgram(0);
		glDeleteProgram(shaderProgramObject);
		shaderProgramObject = 0;
	}
}
