#ifndef _COMPUTE_SHADER_H
#define _COMPUTE_SHADER_H

#include <GL/glew.h>
#include <GL/GL.h>

#include "Shader.h"
#include "Program.h"
#include "macros.h"

class ComputeShader
{
public:
	ComputeShader(
		const char *computeShaderPath,
		GLuint width = 512,
		GLuint height = 512);

	void Resize(GLuint width, GLuint height);

	~ComputeShader();

	void CreateImageObject();

	// void Render(bool, float, float, float, float);

	void BindTexture(GLuint texUnit);

	GLuint GetTexture() const
	{
		return texture;
	}

	void ComputeShader::Render(bool redChannel,
							   float redscaleA,
							   float redscaleB,
							   float redscaleC,
							   float redpersistence,
							   bool greenChannel,
							   float greenscaleA,
							   float greenscaleB,
							   float greenscaleC,
							   float greenpersistence,
							   bool blueChannel,
							   float bluescaleA,
							   float bluescaleB,
							   float bluescaleC,
							   float bluepersistence)
	{
		glUseProgram(program->GetObject());

		// --------------------------------------------------------
		// Bind image texture
		// --------------------------------------------------------
		glBindImageTexture(
			0,
			texture,
			0,
			GL_TRUE,
			0,
			GL_WRITE_ONLY,
			GL_RGBA16F);

		// --------------------------------------------------------
		// Uniforms
		// --------------------------------------------------------
		static float time = 0.0f;
		time += 0.16f;

		glUniform1f(
			glGetUniformLocation(program->GetObject(), "uTime"),
			time);

		glUniform1i(
			glGetUniformLocation(program->GetObject(), "u_redChannel"),
			redChannel ? 1 : 0);

		glUniform1f(
			glGetUniformLocation(program->GetObject(), "u_redNoiseScaleA"),
			redscaleA);

		glUniform1f(
			glGetUniformLocation(program->GetObject(), "u_redNoiseScaleB"),
			redscaleB);

		glUniform1f(
			glGetUniformLocation(program->GetObject(), "u_redNoiseScaleC"),
			redscaleC);

		glUniform1f(
			glGetUniformLocation(program->GetObject(), "u_redpersistence"),
			redpersistence);

		glUniform1i(
			glGetUniformLocation(program->GetObject(), "u_greenChannel"),
			greenChannel ? 1 : 0);

		glUniform1f(
			glGetUniformLocation(program->GetObject(), "u_greenNoiseScaleA"),
			greenscaleA);

		glUniform1f(
			glGetUniformLocation(program->GetObject(), "u_greenNoiseScaleB"),
			greenscaleB);

		glUniform1f(
			glGetUniformLocation(program->GetObject(), "u_greenNoiseScaleC"),
			greenscaleC);

		glUniform1f(
			glGetUniformLocation(program->GetObject(), "u_greenpersistence"),
			greenpersistence);

		glUniform1i(
			glGetUniformLocation(program->GetObject(), "u_blueChannel"),
			blueChannel ? 1 : 0);

		glUniform1f(
			glGetUniformLocation(program->GetObject(), "u_blueNoiseScaleA"),
			bluescaleA);

		glUniform1f(
			glGetUniformLocation(program->GetObject(), "u_blueNoiseScaleB"),
			bluescaleB);

		glUniform1f(
			glGetUniformLocation(program->GetObject(), "u_blueNoiseScaleC"),
			bluescaleC);

		glUniform1f(
			glGetUniformLocation(program->GetObject(), "u_bluepersistence"),
			bluepersistence);

		glUniform3f(
			glGetUniformLocation(program->GetObject(), "textureSize"),
			(float)TEXTURE_DIMENSION,
			(float)TEXTURE_DIMENSION,
			(float)TEXTURE_DIMENSION);

		// --------------------------------------------------------
		// Dispatch
		// local_size = 8
		// --------------------------------------------------------
		const GLuint LOCAL_SIZE = 8;

		GLuint groupsX =
			(TEXTURE_DIMENSION + LOCAL_SIZE - 1) / LOCAL_SIZE;

		GLuint groupsY =
			(TEXTURE_DIMENSION + LOCAL_SIZE - 1) / LOCAL_SIZE;

		GLuint groupsZ =
			(TEXTURE_DIMENSION + LOCAL_SIZE - 1) / LOCAL_SIZE;

		glDispatchCompute(groupsX, groupsY, groupsZ);

		// --------------------------------------------------------
		// Ensure writes complete
		// --------------------------------------------------------
		glMemoryBarrier(
			GL_SHADER_IMAGE_ACCESS_BARRIER_BIT |
			GL_TEXTURE_FETCH_BARRIER_BIT);

		glUseProgram(0);
	}

	void Uninitialize()
	{
		// Code
		if (shader)
		{
			// shader->Uninitialize();
			delete shader;
			shader = NULL;
		}

		if (program)
		{
			// shader->Uninitialize();
			delete program;
			program = NULL;
		}
	}

private:
	Shader *shader = nullptr;
	Program *program = nullptr;

	GLuint texture = 0;

	GLuint TEXTURE_DIMENSION = 128;
};

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

#endif