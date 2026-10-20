/***************************************************************************
 * S.G.M.P
 * @file: LineProgram.h
 * @brief:
 * @author: Mayur S. Tadekar(mrtadekar@gmail.com)
 * @copyright ©2020-2025 MarshallingVoid
 * @date: Wednesday 2025-06-18 5:54:23 PM
 ***************************************************************************/

#pragma once

#include <GL/glew.h>
#include <GL/GL.h>

#include "Shader.h"
#include "macros.h"
#include "Program.h"

#include <glm/glm.hpp>

class LineProgram
{

private:
	Shader *vertexShader;
	Shader *fragmentShader;
	Program *shaderProgram;

	GLuint modelMatrixUniform;
	GLuint viewMatrixUniform;
	GLuint projectionMatrixUniform;

	void InitializeUniforms(Program *shaderProgram)
	{
		// Get uniform locations for the lights
		modelMatrixUniform = glGetUniformLocation(shaderProgram->GetObject(), "u_mMatrix");
		viewMatrixUniform = glGetUniformLocation(shaderProgram->GetObject(), "u_vMatrix");
		projectionMatrixUniform = glGetUniformLocation(shaderProgram->GetObject(), "u_pMatrix");
	}

	LineProgram() = delete; // Prevent default constructor

public:
	LineProgram(const char *vertexShaderPath, const char *fragmentShaderPath, const char *logFilePath)
	{
		vertexShader = new Shader(vertexShaderPath, GL_VERTEX_SHADER, logFilePath);
		fragmentShader = new Shader(fragmentShaderPath, GL_FRAGMENT_SHADER, logFilePath);

		shaderProgram = new Program(2, vertexShader->GetObject(), fragmentShader->GetObject());

		glBindAttribLocation(shaderProgram->GetObject(), MST_ATTRIBUTES_POSITION, "vPosition");
		glBindAttribLocation(shaderProgram->GetObject(), MST_ATTRIBUTES_COLOR, "vColor");
		glBindAttribLocation(shaderProgram->GetObject(), MST_ATTRIBUTES_TEXCOORD, "vTexCoord");
		glBindAttribLocation(shaderProgram->GetObject(), MST_ATTRIBUTES_NORMAL, "vNormal");

		shaderProgram->LinkProgram(logFilePath);

		InitializeUniforms(shaderProgram);
	}

	~LineProgram()
	{
		delete vertexShader;
		delete fragmentShader;
		delete shaderProgram;
	}

	void StartProgram()
	{
		glUseProgram(shaderProgram->GetObject());
	}

	void StopProgram()
	{
		glUseProgram(0);
	}

	void SetUniforms(glm::mat4 &projectionMatrix, glm::mat4 &viewMatrix, glm::mat4 modelMatrix)
	{
		// Code
		glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, &projectionMatrix[0][0]);
		glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, &viewMatrix[0][0]);
		glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, &modelMatrix[0][0]);

		glUniform1i(glGetUniformLocation(shaderProgram->GetObject(), "u_birdIndex"), 0);
	}
};