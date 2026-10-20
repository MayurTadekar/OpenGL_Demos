/***************************************************************************
 * S.G.M.P
 * @file: PointProgram.h
 * @brief:
 * @author: Mayur S. Tadekar(mrtadekar@gmail.com)
 * @copyright ©2020-2025 MarshallingVoid
 * @date: Saturday 2026-06-06 10:26:28 AM
 ***************************************************************************/

#pragma once

#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/vmath/vmath.h>
#include "../Common/Shader.h"
#include "../Common/Program.h"
// #include "macros.h"

#include "../../../include/common.h"
#include "../../../modules/Texture/Texture.h"

class PointProgram
{

private:
	Shader *vertexShader;
	Shader *fragmentShader;
	Program *shaderProgram;

	GLuint modelMatrixUniform;
	GLuint viewMatrixUniform;
	GLuint projectionMatrixUniform;

	GLuint vao;
	GLuint vbo_position;

	GLuint colorU;

	void InitializeSingleLight(Program *shaderProgram)
	{

		modelMatrixUniform = glGetUniformLocation(shaderProgram->GetProgramObject(), "u_modelMatrix");
		viewMatrixUniform = glGetUniformLocation(shaderProgram->GetProgramObject(), "u_viewMatrix");
		projectionMatrixUniform = glGetUniformLocation(shaderProgram->GetProgramObject(), "u_ProjectionMatrix");
		colorU = glGetUniformLocation(shaderProgram->GetProgramObject(), "color");
	}

	PointProgram() = delete; // Prevent default constructor

public:
	PointProgram(const char *vertexShaderPath, const char *fragmentShaderPath, const char *logFilePath)
	{
		// Code
		vertexShader = new Shader(vertexShaderPath, GL_VERTEX_SHADER, logFilePath);
		fragmentShader = new Shader(fragmentShaderPath, GL_FRAGMENT_SHADER, logFilePath);

		shaderProgram = new Program(2, vertexShader->GetShaderObject(), fragmentShader->GetShaderObject());

		glBindAttribLocation(shaderProgram->GetProgramObject(), AMC_ATTRIBUTE_POSITION, "vPosition");
		// glBindAttribLocation(shaderProgram->GetProgramObject(), MST_ATTRIBUTES_COLOR, "vColor");
		glBindAttribLocation(shaderProgram->GetProgramObject(), AMC_ATTRIBUTE_TEXCOORD, "vTexCoord");
		glBindAttribLocation(shaderProgram->GetProgramObject(), AMC_ATTRIBUTE_NORMAL, "vNormal");
		glBindAttribLocation(shaderProgram->GetProgramObject(), AMC_ATTRIBUTE_TANGENT, "vTangent");

		shaderProgram->LinkProgram(logFilePath);

		InitializeSingleLight(shaderProgram);

		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo_position);
	}

	~PointProgram()
	{
		delete vertexShader;
		delete fragmentShader;
		delete shaderProgram;
	}

	void SetUniforms(vmath::mat4 &projectionMatrix, vmath::mat4 &modelMatrix, vmath::mat4 &viewMatrix, vmath::vec3 color)
	{

		// Set the matrix uniforms
		glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, projectionMatrix);
		glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, viewMatrix);
		glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, modelMatrix);

		glUniform3fv(colorU, 1, color);
	}

	void DrawPoints(std::vector<float> vertices)
	{
		// Create VAO
		glBindVertexArray(vao);
		{
			// Create VBO for position
			glBindBuffer(GL_ARRAY_BUFFER, vbo_position);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
			glVertexAttribPointer(AMC_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
			glEnableVertexAttribArray(AMC_ATTRIBUTE_POSITION);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		// Bind VAO
		glBindVertexArray(vao);

		// Draw the triangle
		glDrawArrays(GL_POINTS, 0, vertices.size() / 3);

		// Unbind VAO
		glBindVertexArray(0);
	}

	void StartProgram()
	{
		// Code
		glUseProgram(shaderProgram->GetProgramObject());
	}

	void StopProgram()
	{
		// Code

		glBindTexture(GL_TEXTURE_2D, 0);

		glUseProgram(0);
	}
};