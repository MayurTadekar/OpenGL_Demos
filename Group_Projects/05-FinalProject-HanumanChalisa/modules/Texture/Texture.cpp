// header files
#include "../include/common.h"
#include "./Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb/stb_image.h"

#include <wincodec.h>
#include <fstream>

// global variables
static int creditsTextureCount = 0;

GLuint shaderProgramObjectTextures = 0;
GLuint modelMatrixUniformTextures = 0;
GLuint viewMatrixUniformTextures = 0;
GLuint projectionMatrixUniformTextures = 0;
GLuint textureSamplerUniformTextures = 0;

// mat4 is datatype means 4 * 4 matrix (present in vmath.h)
static mat4 perspectiveProjectionMatrix;

GLuint vaoTextures = 0;
GLuint vboTextures = 0;
GLuint eboTextures = 0;

struct Texture creditsTexture[10];
GLuint creditsTextureNum = 0;
GLuint alphaUniformTextures = 0;
GLfloat alpha = 0.0f;

Texture loadTexture(const char *filename, BOOL bFlipImage)
{
	// local variables
	Texture texture;
	unsigned char *pData = NULL;

	// code

	stbi_set_flip_vertically_on_load((bFlipImage == TRUE) ? 1 : 0);

	pData = stbi_load(filename, &texture.width, &texture.height, &texture.components, 0);
	if (pData == NULL)
	{
		LOG("loadTexture() failed to load %s\n", filename);
		uninitialize();
		exit(EXIT_FAILURE);
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &texture.id);
	glBindTexture(GL_TEXTURE_2D, texture.id);
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		GLenum format;
		switch (texture.components)
		{
		case 1:
			format = GL_R;
			break;
		case 2:
			format = GL_RG;
			break;
		case 3:
			format = GL_RGB;
			break;
		case 4:
			format = GL_RGBA;
			break;
		default:
			format = GL_RGBA;
			break;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, format, texture.width, texture.height, 0, format, GL_UNSIGNED_BYTE, pData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	glBindTexture(GL_TEXTURE_2D, 0);

	if (pData)
	{
		stbi_image_free(pData);
		pData = NULL;
	}

	stbi_set_flip_vertically_on_load(0);

	return (texture);
}

BOOL loadTerrainTexture(GLuint *texture, const char *ImageFilePath)
{
	int width, height, channels;

	// Try loading as 16-bit first
	stbi_us *data16 = stbi_load_16(ImageFilePath, &width, &height, &channels, 0);

	bool is16Bit = (data16 != nullptr);
	void *data = nullptr;

	if (is16Bit)
	{
		data = data16;
	}
	else
	{
		data = stbi_load(ImageFilePath, &width, &height, &channels, 0);
	}

	if (!data)
	{
		printf("Failed to load texture: %s\n", ImageFilePath);
		return (GL_FALSE);
	}

	GLenum format, internalFormat, type;

	// ---------------- FORMAT SELECTION ----------------
	if (channels == 1)
	{
		format = GL_RED;
		internalFormat = is16Bit ? GL_R16 : GL_R8;
	}
	else if (channels == 3)
	{
		format = GL_RGB;
		internalFormat = is16Bit ? GL_RGB16 : GL_RGB8;
	}
	else if (channels == 4)
	{
		format = GL_RGBA;
		internalFormat = is16Bit ? GL_RGBA16 : GL_RGBA8;
	}

	type = is16Bit ? GL_UNSIGNED_SHORT : GL_UNSIGNED_BYTE;

	// ---------------- OPENGL UPLOAD ----------------
	glGenTextures(1, texture);
	glBindTexture(GL_TEXTURE_2D, *texture);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat,
				 width, height, 0,
				 format, type, data);

	// ---------------- CLEANUP ----------------
	if (is16Bit)
		stbi_image_free(data16);
	else
		stbi_image_free(data);

	return (GL_TRUE);
}

Texture loadCubemapTexture(const char *filenames[6])
{
	// local variable
	Texture texture;
	unsigned char *pData = NULL;

	GLenum cubemapTextureTypes[] =
		{
			GL_TEXTURE_CUBE_MAP_POSITIVE_X,
			GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
			GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
			GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
			GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
			GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
		};

	// code

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &texture.id);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture.id);
	{
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		for (int i = 0; i < 6; i++)
		{
			pData = stbi_load(filenames[i], &texture.width, &texture.height, &texture.components, 0);
			if (pData == NULL)
			{
				LOG("loadCubemapTexture() failed to load %s\n", filenames[i]);
				uninitialize();
				exit(EXIT_FAILURE);
			}

			GLenum format;
			switch (texture.components)
			{
			case 1:
				format = GL_R;
				break;
			case 2:
				format = GL_RG;
				break;
			case 3:
				format = GL_RGB;
				break;
			case 4:
				format = GL_RGBA;
				break;
			default:
				format = GL_RGBA;
				break;
			}

			glTexImage2D(cubemapTextureTypes[i], 0, format, texture.width, texture.height, 0, format, GL_UNSIGNED_BYTE, pData);

			if (pData)
			{
				stbi_image_free(pData);
				pData = NULL;
			}
		}
	}
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	return (texture);
}

void initializeTextures(void)
{
	// function declarations
	void uninitializeTextures(void);

	// Vertex Shader
	// step 1 : vertex shader code
	const GLchar *vertexShaderSourceCode =
		"#version 460 core"
		"\n"
		"in vec4 aPosition;"
		"in vec2 aTexCoord;"
		"uniform mat4 uModelMatrix;"
		"uniform mat4 uViewMatrix;"
		"uniform mat4 uProjectionMatrix;"
		"out vec2 oTexCoord;"
		"void main(void)"
		"{"
		"gl_Position= uProjectionMatrix * uViewMatrix * uModelMatrix * aPosition;"
		"oTexCoord = aTexCoord;"
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
		uninitializeTextures();
	}

	// Fragment shader
	// step 6 : write the fragement shader code
	const GLchar *fragmentShaderCode =
		"#version 460 core"
		"\n"
		"in vec2 oTexCoord;"
		"uniform sampler2D uTextureSampler;"
		"uniform float alpha;"
		"out vec4 FragColor;"
		"void main(void)"
		"{"
		"FragColor = vec4( vec3(texture(uTextureSampler,oTexCoord)), alpha );"
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
		uninitializeTextures();
	}

	// shader program
	// step 11 : create shader program
	shaderProgramObjectTextures = glCreateProgram();

	// step 12 : attach shader to this program
	glAttachShader(shaderProgramObjectTextures, vertexShaderObject);
	glAttachShader(shaderProgramObjectTextures, fragmentShaderObject);

	// step 13 : bind attribute location with the shader program object
	glBindAttribLocation(shaderProgramObjectTextures, AMC_ATTRIBUTE_POSITION, "aPosition");
	glBindAttribLocation(shaderProgramObjectTextures, AMC_ATTRIBUTE_TEXCOORD, "aTexCoord");

	// step 14 : link the shader program
	glLinkProgram(shaderProgramObjectTextures);

	// step 15 : linking error check
	status = 0;
	infoLogLength = 0;
	szInfoLog = NULL;

	// step 15 a : get linking status
	glGetProgramiv(shaderProgramObjectTextures, GL_LINK_STATUS, &status);

	if (status == GL_FALSE)
	{
		// step 15 b :
		glGetProgramiv(shaderProgramObjectTextures, GL_INFO_LOG_LENGTH, &infoLogLength);

		if (infoLogLength > 0)
		{
			// step 15 c:
			szInfoLog = (GLchar *)malloc(sizeof(GLchar) * (infoLogLength + 1));

			if (szInfoLog != NULL)
			{
				// step 15 d:
				glGetProgramInfoLog(shaderProgramObjectTextures, infoLogLength + 1, NULL, szInfoLog);

				// step 15 e:
				fprintf(gpFILE, "Shader program linking error log : %s \n", szInfoLog);

				// step 15 f:
				free(szInfoLog);

				szInfoLog = NULL;
			}
		}

		// step 15 e:
		uninitializeTextures();
	}

	// get shader uniform location
	modelMatrixUniformTextures = glGetUniformLocation(shaderProgramObjectTextures, "uModelMatrix");
	viewMatrixUniformTextures = glGetUniformLocation(shaderProgramObjectTextures, "uViewMatrix");
	projectionMatrixUniformTextures = glGetUniformLocation(shaderProgramObjectTextures, "uProjectionMatrix");
	textureSamplerUniformTextures = glGetUniformLocation(shaderProgramObjectTextures, "uTextureSampler");
	alphaUniformTextures = glGetUniformLocation(shaderProgramObjectTextures, "alpha");

	// step 16: declare position
	// cube vertices (interleaved data)
	GLfloat cubeVertices[] =
		{
			// position + texcoord
			1.25f,
			1.0f,
			0.0f,
			1.0f,
			1.0f,
			-1.25f,
			1.0f,
			0.0f,
			0.0f,
			1.0f,
			-1.25f,
			-1.0f,
			0.0f,
			0.0f,
			0.0f,
			1.25f,
			-1.0f,
			0.0f,
			1.0f,
			0.0f,
		};

	GLushort cubeIndices[] =
		{
			// front face
			0, 1, 3,
			3, 1, 2};

	// step 17 : create VAO (vertex array object)
	glGenVertexArrays(1, &vaoTextures);

	// step 18 : bind with VAO (vertex array object)
	glBindVertexArray(vaoTextures);

	// step 19 : VBO(Vertex Buffer Object) for position + texcoord
	glGenBuffers(1, &vboTextures);

	// step 20 : bind with VBO( Vertex Buffer Object) for position
	glBindBuffer(GL_ARRAY_BUFFER, vboTextures);

	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(AMC_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, NULL);

	glEnableVertexAttribArray(AMC_ATTRIBUTE_POSITION);

	glVertexAttribPointer(AMC_ATTRIBUTE_TEXCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, (const void *)(sizeof(GLfloat) * 3));

	glEnableVertexAttribArray(AMC_ATTRIBUTE_TEXCOORD);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//  EBO
	glGenBuffers(1, &eboTextures);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboTextures);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	// for enable depth
	glClearDepth(1.0f);		 // compulsory
	glEnable(GL_DEPTH_TEST); // compulsory
	glDepthFunc(GL_LEQUAL);	 // compulsory

	// step 7 : - set clear color of window to blue (here OpenGL Start)
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// load textures
	creditsTexture[0] = loadTexture("./resources/Texture/credits/ProjectSlide.png", true);
	creditsTextureCount++;

	// initialize orthographic projection matrix
	perspectiveProjectionMatrix = vmath::mat4::identity();
}

bool LoadTextureFromFile(const char *filepath, GLuint *texture)
{
	if (!filepath || !texture)
	{
		LOG("log.txt", "LoadTextureFromFile: Invalid parameters (filepath or texture is null)");
		return false;
	}

	// Check if file exists
	std::ifstream file(filepath, std::ios::binary);
	if (!file.is_open())
	{
		char logMsg[256];
		sprintf_s(logMsg, sizeof(logMsg), "LoadTextureFromFile: File not found - %s", filepath);
		LOG("log.txt", logMsg);
		return false;
	}
	file.close();

	// Initialize COM
	CoInitialize(NULL);

	// Convert char* to LPCWSTR for Windows APIs
	int len = MultiByteToWideChar(CP_UTF8, 0, filepath, -1, NULL, 0);
	wchar_t *wcFilepath = new wchar_t[len];
	MultiByteToWideChar(CP_UTF8, 0, filepath, -1, wcFilepath, len);

	// Use Windows Imaging Component (WIC) to load image
	IWICImagingFactory *pFactory = NULL;
	IWICBitmapDecoder *pDecoder = NULL;
	IWICBitmapFrameDecode *pFrame = NULL;
	IWICFormatConverter *pConverter = NULL;
	IWICBitmap *pBitmap = NULL;

	HRESULT hr = S_OK;
	int imageWidth = 0;
	int imageHeight = 0;
	unsigned char *imageData = NULL;

	// Create WIC factory
	hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID *)&pFactory);

	if (SUCCEEDED(hr))
	{
		// Create decoder
		hr = pFactory->CreateDecoderFromFilename(
			wcFilepath,
			NULL,
			GENERIC_READ,
			WICDecodeMetadataCacheOnLoad,
			&pDecoder);
	}

	if (SUCCEEDED(hr))
	{
		// Get first frame
		hr = pDecoder->GetFrame(0, &pFrame);
	}

	if (SUCCEEDED(hr))
	{
		// Get image dimensions
		hr = pFrame->GetSize((UINT *)&imageWidth, (UINT *)&imageHeight);
	}

	if (SUCCEEDED(hr))
	{
		// Create format converter for RGB
		hr = pFactory->CreateFormatConverter(&pConverter);
	}

	if (SUCCEEDED(hr))
	{
		// Convert to 24-bit RGB
		hr = pConverter->Initialize(
			pFrame,
			GUID_WICPixelFormat32bppBGRA, // GUID_WICPixelFormat24bppBGR,
			WICBitmapDitherTypeNone,
			NULL,
			0.0,
			WICBitmapPaletteTypeCustom);
	}

	if (SUCCEEDED(hr))
	{
		// Allocate image buffer
		imageData = new unsigned char[imageWidth * imageHeight * 4];

		// Copy pixels
		hr = pConverter->CopyPixels(
			NULL,
			imageWidth * 4,
			imageWidth * imageHeight * 4,
			imageData);
	}

	// Create OpenGL texture if loading was successful
	if (SUCCEEDED(hr) && imageData)
	{
		glGenTextures(1, texture);
		glBindTexture(GL_TEXTURE_2D, *texture);
		{
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, imageData);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		glBindTexture(GL_TEXTURE_2D, 0);

		char logMsg[256];
		sprintf_s(logMsg, sizeof(logMsg), "LoadTextureFromFile: Successfully loaded %dx%d texture from %s", imageWidth, imageHeight, filepath);
		LOG("log.txt", logMsg);
	}
	else
	{
		char logMsg[512];
		sprintf_s(logMsg, sizeof(logMsg), "LoadTextureFromFile: Failed to load texture from %s (HRESULT: 0x%08X)", filepath, hr);
		LOG("log.txt", logMsg);
	}

	// Cleanup
	if (imageData)
		delete[] imageData;
	if (pConverter)
		pConverter->Release();
	if (pBitmap)
		pBitmap->Release();
	if (pFrame)
		pFrame->Release();
	if (pDecoder)
		pDecoder->Release();
	if (pFactory)
		pFactory->Release();
	if (wcFilepath)
		delete[] wcFilepath;

	CoUninitialize();

	return SUCCEEDED(hr) && imageData != NULL;
}

// void displayTextures(GLuint textureID, float alpha)
// {
//     glUseProgram(shaderProgramObjectTextures);

//     vmath::mat4 modelMatrix =
//         vmath::translate(0.0f, 0.0f, -3.0f) *
//         vmath::scale(1.0f, 0.8f, 1.0f);

//     glUniformMatrix4fv(modelMatrixUniformTextures, 1, GL_FALSE, modelMatrix);
//     glUniformMatrix4fv(viewMatrixUniformTextures, 1, GL_FALSE, vmath::mat4::identity());
//     glUniformMatrix4fv(projectionMatrixUniformTextures, 1, GL_FALSE, perspectiveProjectionMatrix);

//     glUniform1f(alphaUniformTextures, alpha);

//     glBindVertexArray(vaoTextures);

//     glEnable(GL_BLEND);
//     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboTextures);

//     glActiveTexture(GL_TEXTURE0);
//     glBindTexture(GL_TEXTURE_2D, textureID);
//     glUniform1i(textureSamplerUniformTextures, 0);

//     glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, NULL);

//     glBindTexture(GL_TEXTURE_2D, 0);
//     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//     glBindVertexArray(0);
//     glDisable(GL_BLEND);

//     glUseProgram(0);
// }

void updateTextures(void)
{
	// //code
	// // Texture alpha
	// if(alpha <= 1.0f)
	// {
	// 	alpha = alpha + 0.01f;
	// }
}

void uninitializeTextures(void)
{
	// function declarations
	void ToggleFullScreen(void);

	// code
	//  code
	for (int i = 0; i < creditsTextureCount; i++)
	{
		if (creditsTexture[i].id)
		{
			glDeleteTextures(1, &creditsTexture[i].id);
			creditsTexture[i].id = 0;
		}
	}

	if (eboTextures)
	{
		glDeleteBuffers(1, &eboTextures);
		eboTextures = 0;
	}

	if (vboTextures)
	{
		glDeleteBuffers(1, &vboTextures);
		vboTextures = 0;
	}

	if (vaoTextures)
	{
		glDeleteVertexArrays(1, &vaoTextures);
		vaoTextures = 0;
	}
}
