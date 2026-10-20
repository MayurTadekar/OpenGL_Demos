/***************************************************************************
 * S.G.M.P
 * @file: SimpleProgram.h
 * @brief:
 * @author: Mayur S. Tadekar(mrtadekar@gmail.com)
 * @copyright ©2020-2025 MarshallingVoid
 * @date: Wednesday 2025-06-18 2:19:17 PM
 ***************************************************************************/

#pragma once

#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/vmath/vmath.h>
#include "Shader.h"
#include "Program.h"
#include "macros.h"

class SimpleProgram
{
private:
	Shader *vertexShader;
	Shader *fragmentShader;
	Program *shaderProgram;

	// Shader uniforms
	GLuint modelMatrixUniform;
	GLuint viewMatrixUniform;
	GLuint projectionMatrixUniform;

public:
	SimpleProgram(const char *vertexShaderPath, const char *fragmentShaderPath, const char *logFilePath)
		: vertexShader(nullptr), fragmentShader(nullptr), shaderProgram(nullptr),
		  modelMatrixUniform(0), viewMatrixUniform(0), projectionMatrixUniform(0)
	{

		// Create vertex shader
		vertexShader = new Shader(vertexShaderPath, GL_VERTEX_SHADER, logFilePath);

		// Create fragment shader
		fragmentShader = new Shader(fragmentShaderPath, GL_FRAGMENT_SHADER, logFilePath);

		// Create and link shader program
		shaderProgram = new Program(2, vertexShader->GetObject(), fragmentShader->GetObject());
		glBindAttribLocation(shaderProgram->GetObject(), MST_ATTRIBUTES_POSITION, "vPosition");
		glBindAttribLocation(shaderProgram->GetObject(), MST_ATTRIBUTES_COLOR, "vColor");
		glBindAttribLocation(shaderProgram->GetObject(), MST_ATTRIBUTES_TEXCOORD, "vTexCoord");
		glBindAttribLocation(shaderProgram->GetObject(), MST_ATTRIBUTES_NORMAL, "vNormal");
		shaderProgram->LinkProgram(logFilePath);

		// Get uniform locations
		modelMatrixUniform = glGetUniformLocation(shaderProgram->GetObject(), "u_mMatrix");
		viewMatrixUniform = glGetUniformLocation(shaderProgram->GetObject(), "u_vMatrix");
		projectionMatrixUniform = glGetUniformLocation(shaderProgram->GetObject(), "u_pMatrix");
	}

	~SimpleProgram() = default;

	void SetUniforms(vmath::mat4 &projectionMatrix, vmath::mat4 &viewMatrix, vmath::mat4 &modelMatrix)
	{
		// Set the matrix uniforms
		glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, projectionMatrix);
		glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, viewMatrix);
		glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, modelMatrix);
	}

	void StartProgram()
	{
		glUseProgram(shaderProgram->GetObject());
	}

	void StopProgram()
	{
		glUseProgram(0);
	}

	void Uninitialize()
	{
		// Code
		if (fragmentShader)
		{
			delete fragmentShader;
			fragmentShader = nullptr;
		}

		if (vertexShader)
		{
			delete vertexShader;
			vertexShader = nullptr;
		}

		if (shaderProgram)
		{
			delete shaderProgram;
			shaderProgram = nullptr;
		}
	}
};
