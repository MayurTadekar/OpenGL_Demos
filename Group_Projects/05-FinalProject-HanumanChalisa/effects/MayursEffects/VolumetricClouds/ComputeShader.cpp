
#include <GL/glew.h>
#include <GL/GL.h>

#include "../Common/Shader.h"
#include "../Common/Program.h"
#include "../Common/macros.h"
#include "../Common/common.h"
#include "ComputeShader.hpp"

ComputeShader::ComputeShader(
	const char *computeShaderPath,
	GLuint width,
	GLuint height)
{
	// TEXTURE_DIMENSION = width;
	// TEXTURE_HEIGHT = height;

	shader = new Shader(
		computeShaderPath,
		GL_COMPUTE_SHADER,
		"log.txt");

	program = new Program(
		1,
		shader->GetObject());

	program->LinkProgram("log.txt");

	CreateImageObject();
}

ComputeShader::~ComputeShader()
{
	if (texture)
	{
		glDeleteTextures(1, &texture);
		texture = 0;
	}

	delete program;
	delete shader;
}

void ComputeShader::CreateImageObject()
{
	if (texture)
	{
		glDeleteTextures(1, &texture);
		texture = 0;
	}

	glGenTextures(1, &texture);

	glBindTexture(GL_TEXTURE_3D, texture);

	glTexStorage3D(
		GL_TEXTURE_3D,
		1,
		GL_RGBA16F,
		TEXTURE_DIMENSION,
		TEXTURE_DIMENSION,
		TEXTURE_DIMENSION);

	// glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	// glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// glTexImage2D(
	// 	GL_TEXTURE_3D,
	// 	0,
	// 	GL_RGBA16F,
	// 	TEXTURE_DIMENSION,
	// 	TEXTURE_HEIGHT,
	// 	0,
	// 	GL_RGBA,
	// 	GL_FLOAT,
	// 	nullptr);

	glBindTexture(GL_TEXTURE_3D, 0);
}

void ComputeShader::BindTexture(GLuint texUnit)
{
	glActiveTexture(GL_TEXTURE0 + texUnit);
	glBindTexture(GL_TEXTURE_3D, texture);
}

void ComputeShader::Resize(GLuint width, GLuint height)
{
	// TEXTURE_DIMENSION = width;
	// TEXTURE_HEIGHT = height;

	// if (texture)
	// {
	// 	glDeleteTextures(1, &texture);
	// 	texture = 0;
	// }

	// CreateImageObject();
}