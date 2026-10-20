// header files
#include "../include/common.h"
#include "../modules/Texture/Texture.h"
#include "../modules/Camera/Camera.h"

// global variables
static GLuint shaderProgramObject = 0;
static GLuint modelMatrixUniform = 0;
static GLuint viewMatrixUniform = 0;
static GLuint projectionMatrixUniform = 0;
static GLuint textureSamplerUniform = 0;

static GLuint clippingPlaneUniform = 0;

static GLuint vao = 0;
static GLuint vbo = 0;
static GLuint ebo = 0;

static const char *cubemapFilenames[] =
{
	"./resources/Texture/skybox/px.png",
	"./resources/Texture/skybox/nx.png",
	"./resources/Texture/skybox/py.png",
	"./resources/Texture/skybox/ny.png",
	"./resources/Texture/skybox/pz.png",
	"./resources/Texture/skybox/nz.png",
};

struct Texture cubemapTexture;

BOOL initializeSkybox(void)
{
	// code
	// Vertex Shader
	// step 1 : vertex shader code
	const GLchar *vertexShaderSourceCode =
		"#version 460 core"
		"\n"
		"in vec4 aPosition;"
		"in vec3 aTexCoord;"
		"uniform mat4 uModelMatrix;"
		"uniform mat4 uViewMatrix;"
		"uniform mat4 uProjectionMatrix;"
		"uniform vec4 uClippingPlane;"
		"out vec3 oTexCoord;"
		"void main(void)"
		"{"
		"vec4 worldSpacePosition = uModelMatrix * aPosition;"
		"gl_Position= uProjectionMatrix * uViewMatrix * worldSpacePosition;"
		"oTexCoord = aTexCoord;"
		"gl_ClipDistance[0] = dot(worldSpacePosition,uClippingPlane);"
		"}";

	// step 2 : create vertex shader object
	GLuint vertexShaderObject = glCreateShader(GL_VERTEX_SHADER);

	// step 3 : give vertex source code to openGL
	glShaderSource(vertexShaderObject, 1, (const GLchar **)&vertexShaderSourceCode, NULL);

	// step 4 : let OpenGL compile vertex shader
	glCompileShader(vertexShaderObject);

	// step 5 :
	GLint status = 0;
	GLint infoLogLength = 0;
	GLchar *szInfoLog = NULL;

	// step 5 a:
	glGetShaderiv(vertexShaderObject, GL_COMPILE_STATUS, &status);

	// step 5 b:
	if (status == GL_FALSE)
	{
		glGetShaderiv(vertexShaderObject, GL_INFO_LOG_LENGTH, &infoLogLength);

		if (infoLogLength > 0)
		{
			// step 5 c:
			szInfoLog = (GLchar *)malloc(sizeof(GLchar) * (infoLogLength + 1));

			if (szInfoLog != NULL)
			{

				// step 5 d:
				glGetShaderInfoLog(vertexShaderObject, infoLogLength + 1, NULL, szInfoLog);

				// step 5 e:
				fprintf(gpFILE, "Vertex shader compilation error log : %s\n", szInfoLog);

				// step 5 f:
				free(szInfoLog);

				szInfoLog = NULL;
			}
		}

		// step 5 g:
		uninitialize();
	}

	// Fragment shader
	// step 6 : write the fragement shader code
	const GLchar *fragmentShaderCode =
		"#version 460 core"
		"\n"
		"in vec3 oTexCoord;"
		"uniform samplerCube uTextureSampler;"
		"out vec4 FragColor;"
		"void main(void)"
		"{"
		"FragColor = texture(uTextureSampler,oTexCoord);"
		"}";

	// step 7 : create fragment shader object
	GLuint fragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);

	// step 8 : give fragment shader source code to OpenGL
	glShaderSource(fragmentShaderObject, 1, (const GLchar **)&fragmentShaderCode, NULL);

	// step 9 : let OpenGL compile fragment shader
	glCompileShader(fragmentShaderObject);

	// step 10 :
	status = 0;
	infoLogLength = 0;
	szInfoLog = NULL;

	// step 10 a:
	glGetShaderiv(fragmentShaderObject, GL_COMPILE_STATUS, &status);

	// step 10 b:
	if (status == GL_FALSE)
	{
		glGetShaderiv(fragmentShaderObject, GL_INFO_LOG_LENGTH, &infoLogLength);

		if (infoLogLength > 0)
		{
			// step 10 c:
			szInfoLog = (GLchar *)malloc(sizeof(GLchar) * (infoLogLength + 1));
			if (szInfoLog != NULL)
			{
				// step 10 d:
				glGetShaderInfoLog(fragmentShaderObject, infoLogLength + 1, NULL, szInfoLog);

				// step 10 e:
				fprintf(gpFILE, "fragmenet shader compilation log : %s\n", szInfoLog);

				// step 10 f:
				free(szInfoLog);

				szInfoLog = NULL;
			}
		}

		// step 10 g:
		uninitialize();
	}

	// shader program
	// step 11 : create shader program
	shaderProgramObject = glCreateProgram();

	// step 12 : attach shader to this program
	glAttachShader(shaderProgramObject, vertexShaderObject);
	glAttachShader(shaderProgramObject, fragmentShaderObject);

	// step 13 : bind attribute location with the shader program object
	glBindAttribLocation(shaderProgramObject, AMC_ATTRIBUTE_POSITION, "aPosition");
	glBindAttribLocation(shaderProgramObject, AMC_ATTRIBUTE_TEXCOORD, "aTexCoord");

	// step 14 : link the shader program
	glLinkProgram(shaderProgramObject);

	// step 15 : linking error check
	status = 0;
	infoLogLength = 0;
	szInfoLog = NULL;

	// step 15 a : get linking status
	glGetProgramiv(shaderProgramObject, GL_LINK_STATUS, &status);

	if (status == GL_FALSE)
	{
		// step 15 b :
		glGetProgramiv(shaderProgramObject, GL_INFO_LOG_LENGTH, &infoLogLength);

		if (infoLogLength > 0)
		{
			// step 15 c:
			szInfoLog = (GLchar *)malloc(sizeof(GLchar) * (infoLogLength + 1));

			if (szInfoLog != NULL)
			{
				// step 15 d:
				glGetProgramInfoLog(shaderProgramObject, infoLogLength + 1, NULL, szInfoLog);

				// step 15 e:
				fprintf(gpFILE, "Shader program linking error log : %s \n", szInfoLog);

				// step 15 f:
				free(szInfoLog);

				szInfoLog = NULL;
			}
		}

		// step 15 e:
		uninitialize();
	}

	// get shader uniform location
	modelMatrixUniform = glGetUniformLocation(shaderProgramObject, "uModelMatrix");
	viewMatrixUniform = glGetUniformLocation(shaderProgramObject, "uViewMatrix");
	projectionMatrixUniform = glGetUniformLocation(shaderProgramObject, "uProjectionMatrix");
	textureSamplerUniform = glGetUniformLocation(shaderProgramObject, "uTextureSampler");
	clippingPlaneUniform = glGetUniformLocation(shaderProgramObject, "uClippingPlane");

	// step 16: declare position
	// cube vertices (interleaved data)
	GLfloat cubeVertices[] =
		{
			// position + texcoord
			1.0f,
			1.0f,
			1.0f,
			1.0f,
			1.0f,
			1.0f, // 0
			-1.0f,
			1.0f,
			1.0f,
			-1.0f,
			1.0f,
			1.0f, // 1
			-1.0f,
			-1.0f,
			1.0f,
			-1.0f,
			-1.0f,
			1.0f, // 2
			1.0f,
			-1.0f,
			1.0f,
			1.0f,
			-1.0f,
			1.0f, // 3
			1.0f,
			1.0f,
			-1.0f,
			1.0f,
			1.0f,
			-1.0f, // 4
			-1.0f,
			1.0f,
			-1.0f,
			-1.0f,
			1.0f,
			-1.0f, // 5
			-1.0f,
			-1.0f,
			-1.0f,
			-1.0f,
			-1.0f,
			-1.0f, // 6
			1.0f,
			-1.0f,
			-1.0f,
			1.0f,
			-1.0f,
			-1.0f, // 7
		};

	GLushort cubeIndices[] =
		{
			// front face
			0, 1, 3,
			3, 1, 2,

			// right face
			4, 0, 7,
			7, 0, 3,

			// back face
			4, 5, 7,
			7, 5, 6,

			// left face
			1, 5, 2,
			2, 5, 6,

			// top face
			4, 5, 0,
			0, 5, 1,

			// bottom face
			3, 2, 7,
			7, 2, 6};

	// step 17 : create VAO (vertex array object)
	glGenVertexArrays(1, &vao);

	// step 18 : bind with VAO (vertex array object)
	glBindVertexArray(vao);

	// step 19 : VBO(Vertex Buffer Object) for position + texcoord
	glGenBuffers(1, &vbo);

	// step 20 : bind with VBO( Vertex Buffer Object) for position
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(AMC_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, NULL);

	glEnableVertexAttribArray(AMC_ATTRIBUTE_POSITION);

	glVertexAttribPointer(AMC_ATTRIBUTE_TEXCOORD, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (const void *)(sizeof(GLfloat) * 3));

	glEnableVertexAttribArray(AMC_ATTRIBUTE_TEXCOORD);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//  EBO
	glGenBuffers(1, &ebo);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	// create cubemap texture
	cubemapTexture = loadCubemapTexture(cubemapFilenames);

	return (TRUE);
}

void renderSkybox(Camera *pCamera, vmath::mat4 projectionMatrix, vmath::vec4 clippingPlane)
{
	// code
	glUseProgram(shaderProgramObject);

	vmath::mat4 modelMatrix = vmath::scale(600.0f, 600.0f, 600.0f);

	glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, modelMatrix);
	glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, pCamera->getLookAtMatrix());
	glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, projectionMatrix);
	glUniform4fv(clippingPlaneUniform, 1, clippingPlane);

	glBindVertexArray(vao);
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture.id);
		glUniform1i(textureSamplerUniform, 0);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, NULL);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	glBindVertexArray(0);

	glUseProgram(0);
}

void uninitializeSkybox(void)
{
	// code
	if (cubemapTexture.id)
	{
		glDeleteTextures(1, &cubemapTexture.id);
		cubemapTexture.id = 0;
	}

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

	// for shader program object
	if (shaderProgramObject)
	{
		// step 1 : use shader Program object
		glUseProgram(shaderProgramObject);

		// step 2 : get number of attached shader
		GLint numShader = 0;

		glGetProgramiv(shaderProgramObject, GL_ATTACHED_SHADERS, &numShader);

		if (numShader > 0)
		{
			GLuint *pShader = (GLuint *)malloc(numShader * sizeof(GLuint));
			if (pShader != NULL)
			{
				glGetAttachedShaders(shaderProgramObject, numShader, NULL, pShader);

				for (GLint i = 0; i < numShader; i++)
				{
					glDetachShader(shaderProgramObject, pShader[i]);

					glDeleteShader(pShader[i]);

					pShader[i] = NULL;
				}

				free(pShader);

				pShader = NULL;
			}
		}

		glUseProgram(0);

		glDeleteProgram(shaderProgramObject);

		shaderProgramObject = 0;
	}
}

GLuint getSkyboxCubemapID(void)
{
	return cubemapTexture.id;
}