/***************************************************************************
 * S.G.M.P
 * @file: ShadowProgram.h
 * @brief:
 * @author: Mayur S. Tadekar(mrtadekar@gmail.com)
 * @copyright ©2020-2025 MarshallingVoid
 * @date: Wednesday 2025-06-18 5:54:23 PM
 ***************************************************************************/

#pragma once

#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/vmath/vmath.h>
#include "../Common/Shader.h"
#include "../Common/Program.h"
// #include "macros.h"
#include "../../../include/common.h"

class ShadowProgram
{

private:
	Shader *vertexShader;
	Shader *fragmentShader;
	Program *shaderProgram;

	GLuint lightPosition1Uniform;
	GLuint laUniform;
	GLuint ldUniform;
	GLuint lsUniform;

	GLuint modelMatrixUniform;
	GLuint viewMatrixUniform;
	GLuint projectionMatrixUniform;
	GLuint lightKeyPressedUniform;

	ShadowProgram() = delete; // Prevent default constructor

public:
	ShadowProgram(const char *vertexShaderPath, const char *fragmentShaderPath, const char *logFilePath)
	{
		vertexShader = new Shader(vertexShaderPath, GL_VERTEX_SHADER, logFilePath);
		fragmentShader = new Shader(fragmentShaderPath, GL_FRAGMENT_SHADER, logFilePath);

		shaderProgram = new Program(2, vertexShader->GetObject(), fragmentShader->GetObject());

		glBindAttribLocation(shaderProgram->GetObject(), AMC_ATTRIBUTE_POSITION, "vPosition");
		// glBindAttribLocation(shaderProgram->GetObject(), MST_ATTRIBUTES_COLOR, "vColor");
		glBindAttribLocation(shaderProgram->GetObject(), AMC_ATTRIBUTE_TEXCOORD, "vTexcoord");
		glBindAttribLocation(shaderProgram->GetObject(), AMC_ATTRIBUTE_NORMAL, "vNormal");

		shaderProgram->LinkProgram(logFilePath);

		modelMatrixUniform = glGetUniformLocation(shaderProgram->GetObject(), "u_mMatrix");
		viewMatrixUniform = glGetUniformLocation(shaderProgram->GetObject(), "u_vMatrix");
		projectionMatrixUniform = glGetUniformLocation(shaderProgram->GetObject(), "u_pMatrix");
	}

	~ShadowProgram()
	{
		delete vertexShader;
		delete fragmentShader;
		delete shaderProgram;
	}

	void StartProgram()
	{
		// Code
		glUseProgram(shaderProgram->GetObject());
	}

	void StopProgram()
	{
		glUseProgram(0);
	}

	void SetUniforms(vmath::mat4 &projectionMatrix,
					 vmath::mat4 &viewMatrix,
					 vmath::mat4 &modelMatrix)
	{
		// Set the matrix uniforms
		glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, projectionMatrix);
		glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, viewMatrix);
		glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, modelMatrix);
	}
};