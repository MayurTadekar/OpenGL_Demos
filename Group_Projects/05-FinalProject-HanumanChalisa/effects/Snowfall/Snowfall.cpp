// header files
#include "../../include/common.h"
#include "../../modules/Camera/Camera.h"
#include "../../include/stb/stb_image.h"
#include "Snowfall.h"

#define SNOW_ATTRIB_POSITION 6
#define SNOW_ATTRIB_COLOR 7
#define SNOW_ATTRIB_SIZE 8
#define SNOW_ATTRIB_ROTATION 9
#define SNOW_ATTRIB_SPEED 10

static GLuint g_prog = 0;

// uniforms
static GLuint g_uTime = 0;
static GLuint g_uProjection = 0;
static GLuint g_uView = 0;
static GLuint g_uWorldSize = 0;
static GLuint g_uGravity = 0;
static GLuint g_uWind = 0;
static GLuint g_uTexture = 0;
static GLuint g_uCameraPos = 0;

// VAO / VBOs
static GLuint g_vao = 0;
static GLuint g_vboPosition = 0;
static GLuint g_vboColor = 0;
static GLuint g_vboSize = 0;
static GLuint g_vboRotation = 0;
static GLuint g_vboSpeed = 0;

static GLuint g_snowTexture = 0;
static int g_flakeCount = 0;

static GLfloat g_worldHalfW = 0.0f;
static GLfloat g_worldHalfH = 0.0f;
static GLfloat g_worldDepth = 0.0f;

static GLfloat g_windCurrent = 0.0f;
static GLfloat g_windForce = 0.0f;
static GLfloat g_windTarget = 0.1f;

static GLuint compileShaderSN(GLenum type, const GLchar *src, const char *name)
{
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);

	GLint status = 0;
	GLint logLen = 0;
	GLchar *szLog = NULL;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLen);
		if (logLen > 0)
		{
			szLog = (GLchar *)malloc(sizeof(GLchar) * (logLen + 1));
			if (szLog)
			{
				glGetShaderInfoLog(shader, logLen + 1, NULL, szLog);
				fprintf(gpFILE, "Snowfall %s compile error: %s\n", name, szLog);
				free(szLog);
				szLog = NULL;
			}
		}
		uninitialize();
	}
	return shader;
}

BOOL initializeSnowfall(SnowfallParams &params, int screenW, int screenH)
{
	// code
	// vertex shader
	const GLchar *vertSrc =
		"#version 460 core\n"
		"layout(location = 6)  in vec3 aPosition;\n"
		"layout(location = 7)  in vec4 aColor;\n"
		"layout(location = 8)  in float aSize;\n"
		"layout(location = 9)  in vec3 aRotation;\n"
		"layout(location = 10) in vec3 aSpeed;\n"

		"uniform float uTime;\n"
		"uniform mat4  uProjection;\n"
		"uniform mat4  uView;\n"
		"uniform vec3  uWorldSize;\n"
		"uniform float uGravity;\n"
		"uniform float uWind;\n"
		"uniform vec3  uCameraPos;\n"

		"out vec4  vColor;\n"
		"out float vRotation;\n"

		"void main(void)\n"
		"{\n"
		"   vColor    = aColor;\n"
		"   vRotation = aRotation.x + uTime * aRotation.y;\n"

		"   vec3 pos = aPosition;\n"
		"   float W = uWorldSize.x * 2.0;\n"
		"   float H = uWorldSize.y * 2.0;\n"
		"   float D = uWorldSize.z * 2.0;\n"

		"   pos.x = mod(pos.x - uCameraPos.x + uTime * 0.01 + uWind * aSpeed.x + uWorldSize.x, W)"
		"           - uWorldSize.x + uCameraPos.x;\n"

		"   pos.y = mod(pos.y - uCameraPos.y - uTime * aSpeed.y * uGravity + uWorldSize.y, H)"
		"           - uWorldSize.y + uCameraPos.y;\n"

		"   pos.x += sin(uTime * aSpeed.z) * aRotation.z;\n"
		"   pos.z  = mod(pos.z - uCameraPos.z + cos(uTime * aSpeed.z) * aRotation.z + uWorldSize.z, D)"
		"           - uWorldSize.z + uCameraPos.z;\n"

		"   vec4 viewPos  = uView * vec4(pos, 1.0);\n"
		"   gl_Position   = uProjection * viewPos;\n"

		"   float dist    = max(-viewPos.z, 0.1);\n"
"   gl_PointSize  = aSize * (15.0 / dist);\n"
		"}\n";

	// fragment shader
	const GLchar *fragSrc =
		"#version 460 core\n"
		"in vec4  vColor;\n"
		"in float vRotation;\n"
		"uniform sampler2D uTexture;\n"
		"out vec4 FragColor;\n"

		"void main(void)\n"
		"{\n"
		"   float c  = cos(vRotation);\n"
		"   float s  = sin(vRotation);\n"
		"   vec2  uv = vec2(\n"
		"       c * (gl_PointCoord.x - 0.5) + s * (gl_PointCoord.y - 0.5) + 0.5,\n"
		"       c * (gl_PointCoord.y - 0.5) - s * (gl_PointCoord.x - 0.5) + 0.5\n"
		"   );\n"
		"   vec4 flake  = texture(uTexture, uv);\n"
		"   FragColor   = vec4(flake.rgb * vColor.rgb, flake.a * vColor.a);\n"
		"}\n";

	GLuint vs = compileShaderSN(GL_VERTEX_SHADER, vertSrc, "vertex");
	GLuint fs = compileShaderSN(GL_FRAGMENT_SHADER, fragSrc, "fragment");

	g_prog = glCreateProgram();
	glAttachShader(g_prog, vs);
	glAttachShader(g_prog, fs);
	glBindAttribLocation(g_prog, SNOW_ATTRIB_POSITION, "aPosition");
	glBindAttribLocation(g_prog, SNOW_ATTRIB_COLOR, "aColor");
	glBindAttribLocation(g_prog, SNOW_ATTRIB_SIZE, "aSize");
	glBindAttribLocation(g_prog, SNOW_ATTRIB_ROTATION, "aRotation");
	glBindAttribLocation(g_prog, SNOW_ATTRIB_SPEED, "aSpeed");
	glLinkProgram(g_prog);

	GLint status = 0;
	GLint logLen = 0;
	GLchar *szLog = NULL;

	glGetProgramiv(g_prog, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		glGetProgramiv(g_prog, GL_INFO_LOG_LENGTH, &logLen);
		if (logLen > 0)
		{
			szLog = (GLchar *)malloc(sizeof(GLchar) * (logLen + 1));
			if (szLog)
			{
				glGetProgramInfoLog(g_prog, logLen + 1, NULL, szLog);
				fprintf(gpFILE, "Snowfall eFfect link error: %s\n", szLog);
				free(szLog);
				szLog = NULL;
			}
		}
		uninitialize();
		return FALSE;
	}

	g_uTime = glGetUniformLocation(g_prog, "uTime");
	g_uProjection = glGetUniformLocation(g_prog, "uProjection");
	g_uView = glGetUniformLocation(g_prog, "uView");
	g_uWorldSize = glGetUniformLocation(g_prog, "uWorldSize");
	g_uGravity = glGetUniformLocation(g_prog, "uGravity");
	g_uWind = glGetUniformLocation(g_prog, "uWind");
	g_uTexture = glGetUniformLocation(g_prog, "uTexture");
	g_uCameraPos = glGetUniformLocation(g_prog, "uCameraPos");

	GLfloat aspect = (screenH > 0) ? (GLfloat)screenW / (GLfloat)screenH : 1.777f;
	GLfloat halfH = 1.0f / params.density;
	GLfloat halfW = aspect * halfH;
	GLfloat depth = params.depth;
	int count = (int)((GLfloat)params.count * aspect);

	g_worldHalfW = halfW;
	g_worldHalfH = halfH;
	g_worldDepth = depth;
	g_flakeCount = count;

	std::vector<GLfloat> pos, col, sz, rot, spd;
	pos.reserve(count * 3);
	col.reserve(count * 4);
	sz.reserve(count);
	rot.reserve(count * 3);
	spd.reserve(count * 3);

	srand(1337);
	auto frand = []()
	{ return (GLfloat)rand() / (GLfloat)RAND_MAX; };

	for (int i = 0; i < count; i++)
	{
		GLfloat px =
			params.cameraStartPos[0] +
			(-halfW + frand() * halfW * 2.0f);

		GLfloat py =
			params.cameraStartPos[1] +
			(-halfH + frand() * halfH * 2.0f);

		GLfloat pz =
			params.cameraStartPos[2] +
			(-depth + frand() * depth * 2.0f);

		pos.push_back(px);
		pos.push_back(py);
		pos.push_back(pz);

		spd.push_back(1.0f + frand());
		spd.push_back(1.0f + frand());
		spd.push_back(frand() * 10.0f);

		rot.push_back(frand() * 2.0f * (GLfloat)M_PI);
		rot.push_back(frand() * 20.0f);
		rot.push_back(frand() * 10.0f);

		col.push_back(params.color[0]);
		col.push_back(params.color[1]);
		col.push_back(params.color[2]);

		col.push_back(
			0.5f + frand() * params.opacity);

		GLfloat s =
			params.sizeMin +
			frand() * (params.sizeMax - params.sizeMin);

		sz.push_back(s);
	}

	glGenVertexArrays(1, &g_vao);
	glBindVertexArray(g_vao);

	auto uploadVBO = [](GLuint *vbo, GLuint attrib, int compSize,
						const std::vector<GLfloat> &data)
	{
		glGenBuffers(1, vbo);
		glBindBuffer(GL_ARRAY_BUFFER, *vbo);
		glBufferData(GL_ARRAY_BUFFER,
					 sizeof(GLfloat) * data.size(), data.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(attrib, compSize, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(attrib);
	};

	uploadVBO(&g_vboPosition, SNOW_ATTRIB_POSITION, 3, pos);
	uploadVBO(&g_vboColor, SNOW_ATTRIB_COLOR, 4, col);
	uploadVBO(&g_vboSize, SNOW_ATTRIB_SIZE, 1, sz);
	uploadVBO(&g_vboRotation, SNOW_ATTRIB_ROTATION, 3, rot);
	uploadVBO(&g_vboSpeed, SNOW_ATTRIB_SPEED, 3, spd);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glGenTextures(1, &g_snowTexture);
	glBindTexture(GL_TEXTURE_2D, g_snowTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	if (params.texturePath && strlen(params.texturePath) > 0)
	{
		int tw = 0, th = 0, tc = 0;
		stbi_set_flip_vertically_on_load(TRUE);
		unsigned char *pData = stbi_load(params.texturePath, &tw, &th, &tc, 4);
		if (pData)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0,
						 GL_RGBA, GL_UNSIGNED_BYTE, pData);
			stbi_image_free(pData);
			fprintf(gpFILE, "Snowfall: loaded texture '%s' %dx%d\n",
					params.texturePath, tw, th);
		}
		else
		{
			fprintf(gpFILE, "Snowfall: texture load failed '%s', using white fallback\n",
					params.texturePath);			
			unsigned char white[4] = {255, 255, 255, 255};
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0,
						 GL_RGBA, GL_UNSIGNED_BYTE, white);
		}
	}
	else
	{		
		const int SZ = 64;
		unsigned char pixels[SZ * SZ * 4];
		for (int py = 0; py < SZ; py++)
		{
			for (int px = 0; px < SZ; px++)
			{
				float dx = (px / (float)(SZ - 1)) - 0.5f;
				float dy = (py / (float)(SZ - 1)) - 0.5f;
				float dist = sqrtf(dx * dx + dy * dy) * 2.0f;
				float a = (dist < 1.0f) ? (1.0f - dist) : 0.0f;
				a = a * a;
				int idx = (py * SZ + px) * 4;
				pixels[idx + 0] = 255;
				pixels[idx + 1] = 255;
				pixels[idx + 2] = 255;
				pixels[idx + 3] = (unsigned char)(a * 255);
			}
		}
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SZ, SZ, 0,
					 GL_RGBA, GL_UNSIGNED_BYTE, pixels);
		fprintf(gpFILE, "Snowfall: using procedural soft-circle texture\n");
	}

	glBindTexture(GL_TEXTURE_2D, 0);

	g_windCurrent = 0.0f;
	g_windForce = params.windForce;
	g_windTarget = params.windMin;

	fprintf(gpFILE, "Snowfall: initialized %d flakes | worldHW=(%.1f,%.1f) depth=%.1f\n",
			count, halfW, halfH, depth);

	return TRUE;
}

void updateSnowfall(SnowfallParams &params, GLfloat deltaTime)
{
	// code
	if (!params.bEnable)
		return;

	params._time += deltaTime * params.speed * 1000.0f;

	if ((GLfloat)rand() / (GLfloat)RAND_MAX > 0.995f)
	{
		GLfloat r = (GLfloat)rand() / (GLfloat)RAND_MAX;
		g_windTarget = (params.windMin + r * (params.windMax - params.windMin)) * (((GLfloat)rand() / (GLfloat)RAND_MAX > 0.5f) ? 1.0f : -1.0f);
	}

	g_windForce += (g_windTarget - g_windForce) * params.windEasing;
	g_windCurrent += g_windForce * (deltaTime * 200.0f);

	params._windCurrent = g_windCurrent;
}

void renderSnowfall(SnowfallParams &params,
					Camera *pCamera,
					vmath::mat4 projectionMatrix,
					int screenW,
					int screenH)
{
	if (!params.bEnable || g_flakeCount <= 0)
		return;

	glUseProgram(g_prog);

	vmath::vec3 camPos = pCamera->m_position;

	glUniform3f(
		g_uCameraPos,
		camPos[0],
		camPos[1],
		camPos[2]);

	glUniformMatrix4fv(
		g_uProjection,
		1,
		GL_FALSE,
		projectionMatrix);

	glUniformMatrix4fv(
		g_uView,
		1,
		GL_FALSE,
		pCamera->getLookAtMatrix());

	glUniform3f(
		g_uWorldSize,
		g_worldHalfW,
		g_worldHalfH,
		g_worldDepth);

	glUniform1f(g_uTime, params._time);
	glUniform1f(g_uGravity, params.gravity);
	glUniform1f(g_uWind, g_windCurrent);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, g_snowTexture);
	glUniform1i(g_uTexture, 0);

	glEnable(GL_PROGRAM_POINT_SIZE);
	glEnable(GL_POINT_SPRITE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);
	glDisable(GL_CULL_FACE);
	glBindVertexArray(g_vao);
		glDrawArrays(GL_POINTS, 0, g_flakeCount);
	glBindVertexArray(0);

	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
	glDisable(GL_PROGRAM_POINT_SIZE);

	glBindTexture(GL_TEXTURE_2D, 0);

	glUseProgram(0);
}

void displaySnowfallImGui(SnowfallParams &params)
{
	if (ImGui::CollapsingHeader("Snowfall", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::Checkbox("Enable Snowfall", (bool *)&params.bEnable);

		if (params.bEnable)
		{
			ImGui::Separator();
			ImGui::Text("--- Density & Volume ---");
			ImGui::DragFloat("Density", &params.density, 0.001f, 0.005f, 0.1f, "%.4f");
			ImGui::DragFloat("Depth", &params.depth, 1.0f, 10.0f, 500.0f);

			ImGui::Separator();
			ImGui::Text("--- Physics ---");
			ImGui::DragFloat("Gravity", &params.gravity, 1.0f, 1.0f, 500.0f);
			ImGui::DragFloat("Speed", &params.speed, 0.00001f, 0.00001f, 0.005f, "%.6f");

			ImGui::Separator();
			ImGui::Text("--- Wind ---");
			ImGui::DragFloat("Wind Min", &params.windMin, 0.01f, 0.0f, 1.0f);
			ImGui::DragFloat("Wind Max", &params.windMax, 0.01f, 0.0f, 2.0f);
			ImGui::DragFloat("Wind Easing", &params.windEasing, 0.001f, 0.0f, 0.1f);
			ImGui::Text("Wind Current: %.4f", g_windCurrent);

			ImGui::Separator();
			ImGui::Text("--- Appearance ---");
			ImGui::ColorEdit3("Snow Color", &params.color[0]);
			ImGui::DragFloat("Opacity", &params.opacity, 0.01f, 0.0f, 1.0f);
			ImGui::DragFloat("Size Min", &params.sizeMin, 0.1f, 0.1f, 20.0f);
			ImGui::DragFloat("Size Max", &params.sizeMax, 0.1f, 0.1f, 50.0f);

			ImGui::Separator();
			ImGui::Text("Flakes: %d  Time: %.2f", g_flakeCount, params._time);
		}
	}
}

void uninitializeSnowfall(void)
{
	// code
	if (g_snowTexture)
	{
		glDeleteTextures(1, &g_snowTexture);
		g_snowTexture = 0;
	}

	if (g_vboSpeed)
	{
		glDeleteBuffers(1, &g_vboSpeed);
		g_vboSpeed = 0;
	}
	if (g_vboRotation)
	{
		glDeleteBuffers(1, &g_vboRotation);
		g_vboRotation = 0;
	}
	if (g_vboSize)
	{
		glDeleteBuffers(1, &g_vboSize);
		g_vboSize = 0;
	}
	if (g_vboColor)
	{
		glDeleteBuffers(1, &g_vboColor);
		g_vboColor = 0;
	}
	if (g_vboPosition)
	{
		glDeleteBuffers(1, &g_vboPosition);
		g_vboPosition = 0;
	}
	if (g_vao)
	{
		glDeleteVertexArrays(1, &g_vao);
		g_vao = 0;
	}

	if (g_prog)
	{
		glUseProgram(g_prog);
		GLint n = 0;
		glGetProgramiv(g_prog, GL_ATTACHED_SHADERS, &n);
		if (n > 0)
		{
			GLuint *sh = (GLuint *)malloc(n * sizeof(GLuint));
			if (sh)
			{
				glGetAttachedShaders(g_prog, n, NULL, sh);
				for (GLint i = 0; i < n; i++)
				{
					glDetachShader(g_prog, sh[i]);
					glDeleteShader(sh[i]);
				}
				free(sh);
			}
		}
		glUseProgram(0);
		glDeleteProgram(g_prog);
		g_prog = 0;
	}
}
