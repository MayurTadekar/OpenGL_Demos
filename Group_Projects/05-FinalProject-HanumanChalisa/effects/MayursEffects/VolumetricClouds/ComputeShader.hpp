#ifndef _COMPUTE_SHADER_H
#define _COMPUTE_SHADER_H

#include <GL/glew.h>
#include <GL/GL.h>

#include "../Common/Shader.h"
#include "../Common/Program.h"
#include "../Common/macros.h"
#include "../Common/common.h"

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
		glUseProgram(program->GetProgramObject());

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
			glGetUniformLocation(program->GetProgramObject(), "uTime"),
			time);

		glUniform1i(
			glGetUniformLocation(program->GetProgramObject(), "u_redChannel"),
			redChannel ? 1 : 0);

		glUniform1f(
			glGetUniformLocation(program->GetProgramObject(), "u_redNoiseScaleA"),
			redscaleA);

		glUniform1f(
			glGetUniformLocation(program->GetProgramObject(), "u_redNoiseScaleB"),
			redscaleB);

		glUniform1f(
			glGetUniformLocation(program->GetProgramObject(), "u_redNoiseScaleC"),
			redscaleC);

		glUniform1f(
			glGetUniformLocation(program->GetProgramObject(), "u_redpersistence"),
			redpersistence);

		glUniform1i(
			glGetUniformLocation(program->GetProgramObject(), "u_greenChannel"),
			greenChannel ? 1 : 0);

		glUniform1f(
			glGetUniformLocation(program->GetProgramObject(), "u_greenNoiseScaleA"),
			greenscaleA);

		glUniform1f(
			glGetUniformLocation(program->GetProgramObject(), "u_greenNoiseScaleB"),
			greenscaleB);

		glUniform1f(
			glGetUniformLocation(program->GetProgramObject(), "u_greenNoiseScaleC"),
			greenscaleC);

		glUniform1f(
			glGetUniformLocation(program->GetProgramObject(), "u_greenpersistence"),
			greenpersistence);

		glUniform1i(
			glGetUniformLocation(program->GetProgramObject(), "u_blueChannel"),
			blueChannel ? 1 : 0);

		glUniform1f(
			glGetUniformLocation(program->GetProgramObject(), "u_blueNoiseScaleA"),
			bluescaleA);

		glUniform1f(
			glGetUniformLocation(program->GetProgramObject(), "u_blueNoiseScaleB"),
			bluescaleB);

		glUniform1f(
			glGetUniformLocation(program->GetProgramObject(), "u_blueNoiseScaleC"),
			bluescaleC);

		glUniform1f(
			glGetUniformLocation(program->GetProgramObject(), "u_bluepersistence"),
			bluepersistence);

		glUniform3f(
			glGetUniformLocation(program->GetProgramObject(), "textureSize"),
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

#endif