/***************************************************************************
 * S.G.M.P
 * @file: Point.h
 * @brief: Implementation of a Point class for OpenGL rendering
 * @date: Wednesday 2025-06-18
 ***************************************************************************/

#pragma once

#include <GL/glew.h>
#include <GL/GL.h>

#include <vector>
#include "Shader.h"
#include "Program.h"
#include "macros.h"
#include "common.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Point
{
public:
	Point();
	~Point();

	void Initialize();
	glm::mat4 GetModelMatrix() const;
	void Resize(int width, int height);
	void Uninitialize();
	void ToggleLight();
	void SetLight(bool enable);
	void Draw(int);

	void SetPosition(glm::vec3 position);
	void SetColor(glm::vec3 color);

private:
	GLuint vao;
	GLuint vbo_position;
	GLuint vbo_color;
	GLuint vbo_normal;
	GLuint vbo_texcoord;

	// Shader uniforms
	GLuint modelMatrixUniform;
	GLuint viewMatrixUniform;
	GLuint projectionMatrixUniform;
	GLuint lightKeyPressedUniform;

	Shader *vertexShader;
	Shader *fragmentShader;
	Program *shaderProgram;

	bool enableLight;

	// Point data
	std::vector<GLfloat> PointVertices;
	std::vector<GLfloat> PointNormals;
	std::vector<GLfloat> PointTexCoords;
	std::vector<GLfloat> PointColors;

	glm::mat4 modelMatrix;

	void CreatePoint();
};

Point::Point()
	: vao(0), vbo_position(0), vbo_normal(0), vbo_texcoord(0),
	  modelMatrixUniform(0), viewMatrixUniform(0), projectionMatrixUniform(0),
	  lightKeyPressedUniform(0), enableLight(true), modelMatrix(glm::mat4(1.0f))
{
	// Initialize lighting parameters

	Initialize();
}

Point::~Point()
{
	Uninitialize();
}

void Point::CreatePoint()
{
	// Clear any existing data
	PointVertices.clear();
	PointNormals.clear();
	PointTexCoords.clear();

	PointVertices.push_back(0.0f);
	PointVertices.push_back(0.0f);
	PointVertices.push_back(0.0f);
	PointNormals.push_back(0.0f);
	PointNormals.push_back(1.0f);
	PointNormals.push_back(0.0f);
	PointTexCoords.push_back(0.0f);
	PointTexCoords.push_back(0.0f);
	PointColors.push_back(1.0f);
	PointColors.push_back(1.0f);
	PointColors.push_back(0.0f);
}

void Point::Initialize()
{
	// Create the Point data
	CreatePoint();

	// Create VAO
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Create VBO for position
	glGenBuffers(1, &vbo_position);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_position);
	glBufferData(GL_ARRAY_BUFFER, PointVertices.size() * sizeof(GLfloat), PointVertices.data(), GL_DYNAMIC_DRAW);
	glVertexAttribPointer(MST_ATTRIBUTES_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(MST_ATTRIBUTES_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Create VBO for colors
	glGenBuffers(1, &vbo_color);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_color);
	glBufferData(GL_ARRAY_BUFFER, PointColors.size() * sizeof(GLfloat), PointColors.data(), GL_DYNAMIC_DRAW);
	glVertexAttribPointer(MST_ATTRIBUTES_COLOR, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(MST_ATTRIBUTES_COLOR);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Create VBO for normals
	glGenBuffers(1, &vbo_normal);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_normal);
	glBufferData(GL_ARRAY_BUFFER, PointNormals.size() * sizeof(GLfloat), PointNormals.data(), GL_DYNAMIC_DRAW);
	glVertexAttribPointer(MST_ATTRIBUTES_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(MST_ATTRIBUTES_NORMAL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Create VBO for texture coordinates
	glGenBuffers(1, &vbo_texcoord);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_texcoord);
	glBufferData(GL_ARRAY_BUFFER, PointTexCoords.size() * sizeof(GLfloat), PointTexCoords.data(), GL_DYNAMIC_DRAW);
	glVertexAttribPointer(MST_ATTRIBUTES_TEXCOORD, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(MST_ATTRIBUTES_TEXCOORD);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Unbind VAO
	glBindVertexArray(0);
}

void Point::SetPosition(glm::vec3 position)
{
	// modelMatrix = glm::translate(glm::mat4(1.0f), position);

	PointVertices[0] = position[0];
	PointVertices[1] = position[1];
	PointVertices[2] = position[2];
	
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_position);
	glBufferData(GL_ARRAY_BUFFER, PointVertices.size() * sizeof(GLfloat), PointVertices.data(), GL_DYNAMIC_DRAW);
	glVertexAttribPointer(MST_ATTRIBUTES_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(MST_ATTRIBUTES_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void Point::SetColor(glm::vec3 color)
{
	PointColors[0] = color[0];
	PointColors[1] = color[1];
	PointColors[2] = color[2];
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo_color);
	glBufferData(GL_ARRAY_BUFFER, PointColors.size() * sizeof(GLfloat), PointColors.data(), GL_DYNAMIC_DRAW);
	glVertexAttribPointer(MST_ATTRIBUTES_COLOR, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(MST_ATTRIBUTES_COLOR);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

glm::mat4 Point::GetModelMatrix() const
{
	return modelMatrix;
}

void Point::Draw(int birdCount)
{

	// Bind VAO
	glBindVertexArray(vao);

	// glDrawArrays(GL_POINTS, 0, PointVertices.size() / 3);
	glDrawArraysInstanced(GL_POINTS, 0, PointVertices.size() / 3, birdCount);

	// glBindVertexArray(vao);
	// glDrawArraysInstanced(GL_TRIANGLES, 0, 12, birdCount);
	// glBindVertexArray(0);
	
	// Unbind VAO and shader
	glBindVertexArray(0);
}

void Point::Resize(int width, int height)
{
	// No specific resize operations needed for the Point
}

void Point::Uninitialize()
{
	if (vbo_position)
	{
		glDeleteBuffers(1, &vbo_position);
		vbo_position = 0;
	}

	if (vbo_normal)
	{
		glDeleteBuffers(1, &vbo_normal);
		vbo_normal = 0;
	}

	if (vbo_texcoord)
	{
		glDeleteBuffers(1, &vbo_texcoord);
		vbo_texcoord = 0;
	}

	if (vao)
	{
		glDeleteVertexArrays(1, &vao);
		vao = 0;
	}

	// Delete shader objects
	if (shaderProgram)
	{
		delete shaderProgram;
		shaderProgram = NULL;
	}

	if (vertexShader)
	{
		delete vertexShader;
		vertexShader = NULL;
	}

	if (fragmentShader)
	{
		delete fragmentShader;
		fragmentShader = NULL;
	}
}

void Point::ToggleLight()
{
	enableLight = !enableLight;
}

void Point::SetLight(bool enable)
{
	enableLight = enable;
}
