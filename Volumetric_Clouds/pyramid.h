/***************************************************************************
 * S.G.M.P
 * @file: pyramid.h
 * @brief: Implementation of a pyramid class for OpenGL rendering
 * @date: Wednesday 2025-06-18
 ***************************************************************************/

#pragma once

#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/vmath/vmath.h>
#include <vector>
#include "Shader.h"
#include "Program.h"
#include "macros.h"
#include "common.h"
#include "multilight.h"

using namespace vmath;

class Pyramid
{
public:
	Pyramid();
	~Pyramid();

	void Initialize();
	void Display();
	void Resize(int width, int height);
	void Uninitialize();
	void ToggleLight();
	void SetLight(bool enable);

private:
	GLuint vao;
	GLuint vbo_position;
	GLuint vbo_normal;
	GLuint vbo_texcoord;

	// Pyramid data
	std::vector<GLfloat> pyramidVertices;
	std::vector<GLfloat> pyramidNormals;
	std::vector<GLfloat> pyramidTexCoords;

	void CreatePyramid();
};

Pyramid::Pyramid()
	: vao(0), vbo_position(0), vbo_normal(0), vbo_texcoord(0)
{
	// Initialize lighting parameters
}

Pyramid::~Pyramid()
{
	Uninitialize();
}

void Pyramid::CreatePyramid()
{
	// Clear any existing data
	pyramidVertices.clear();
	pyramidNormals.clear();
	pyramidTexCoords.clear();

	// Pyramid apex and base vertices
	// Apex at (0, 1, 0)
	// Base vertices at (-1, -1, ±1) and (1, -1, ±1)

	// FRONT FACE (Z+)
	// Triangle with apex (0,1,0), (-1,-1,1), (1,-1,1)
	// Vertex 1 - Apex
	pyramidVertices.push_back(0.0f);
	pyramidVertices.push_back(1.0f);
	pyramidVertices.push_back(0.0f);
	// Calculate normal for front face
	pyramidNormals.push_back(0.0f);
	pyramidNormals.push_back(0.577f); // Approximately normalized
	pyramidNormals.push_back(0.816f);
	pyramidTexCoords.push_back(0.5f);
	pyramidTexCoords.push_back(1.0f);

	// Vertex 2 - Base left
	pyramidVertices.push_back(-1.0f);
	pyramidVertices.push_back(-1.0f);
	pyramidVertices.push_back(1.0f);
	pyramidNormals.push_back(0.0f);
	pyramidNormals.push_back(0.577f);
	pyramidNormals.push_back(0.816f);
	pyramidTexCoords.push_back(0.0f);
	pyramidTexCoords.push_back(0.0f);

	// Vertex 3 - Base right
	pyramidVertices.push_back(1.0f);
	pyramidVertices.push_back(-1.0f);
	pyramidVertices.push_back(1.0f);
	pyramidNormals.push_back(0.0f);
	pyramidNormals.push_back(0.577f);
	pyramidNormals.push_back(0.816f);
	pyramidTexCoords.push_back(1.0f);
	pyramidTexCoords.push_back(0.0f);

	// RIGHT FACE (X+)
	// Triangle with apex (0,1,0), (1,-1,1), (1,-1,-1)
	// Vertex 4 - Apex
	pyramidVertices.push_back(0.0f);
	pyramidVertices.push_back(1.0f);
	pyramidVertices.push_back(0.0f);
	pyramidNormals.push_back(0.816f);
	pyramidNormals.push_back(0.577f);
	pyramidNormals.push_back(0.0f);
	pyramidTexCoords.push_back(0.5f);
	pyramidTexCoords.push_back(1.0f);

	// Vertex 5 - Base front
	pyramidVertices.push_back(1.0f);
	pyramidVertices.push_back(-1.0f);
	pyramidVertices.push_back(1.0f);
	pyramidNormals.push_back(0.816f);
	pyramidNormals.push_back(0.577f);
	pyramidNormals.push_back(0.0f);
	pyramidTexCoords.push_back(0.0f);
	pyramidTexCoords.push_back(0.0f);

	// Vertex 6 - Base back
	pyramidVertices.push_back(1.0f);
	pyramidVertices.push_back(-1.0f);
	pyramidVertices.push_back(-1.0f);
	pyramidNormals.push_back(0.816f);
	pyramidNormals.push_back(0.577f);
	pyramidNormals.push_back(0.0f);
	pyramidTexCoords.push_back(1.0f);
	pyramidTexCoords.push_back(0.0f);

	// BACK FACE (Z-)
	// Triangle with apex (0,1,0), (-1,-1,-1), (1,-1,-1)
	// Vertex 7 - Apex
	pyramidVertices.push_back(0.0f);
	pyramidVertices.push_back(1.0f);
	pyramidVertices.push_back(0.0f);
	pyramidNormals.push_back(0.0f);
	pyramidNormals.push_back(0.577f);
	pyramidNormals.push_back(-0.816f);
	pyramidTexCoords.push_back(0.5f);
	pyramidTexCoords.push_back(1.0f);

	// Vertex 8 - Base right (from behind)
	pyramidVertices.push_back(-1.0f);
	pyramidVertices.push_back(-1.0f);
	pyramidVertices.push_back(-1.0f);
	pyramidNormals.push_back(0.0f);
	pyramidNormals.push_back(0.577f);
	pyramidNormals.push_back(-0.816f);
	pyramidTexCoords.push_back(1.0f);
	pyramidTexCoords.push_back(0.0f);

	// Vertex 9 - Base left (from behind)
	pyramidVertices.push_back(1.0f);
	pyramidVertices.push_back(-1.0f);
	pyramidVertices.push_back(-1.0f);
	pyramidNormals.push_back(0.0f);
	pyramidNormals.push_back(0.577f);
	pyramidNormals.push_back(-0.816f);
	pyramidTexCoords.push_back(0.0f);
	pyramidTexCoords.push_back(0.0f);

	// LEFT FACE (X-)
	// Triangle with apex (0,1,0), (-1,-1,1), (-1,-1,-1)
	// Vertex 10 - Apex
	pyramidVertices.push_back(0.0f);
	pyramidVertices.push_back(1.0f);
	pyramidVertices.push_back(0.0f);
	pyramidNormals.push_back(-0.816f);
	pyramidNormals.push_back(0.577f);
	pyramidNormals.push_back(0.0f);
	pyramidTexCoords.push_back(0.5f);
	pyramidTexCoords.push_back(1.0f);

	// Vertex 11 - Base front
	pyramidVertices.push_back(-1.0f);
	pyramidVertices.push_back(-1.0f);
	pyramidVertices.push_back(1.0f);
	pyramidNormals.push_back(-0.816f);
	pyramidNormals.push_back(0.577f);
	pyramidNormals.push_back(0.0f);
	pyramidTexCoords.push_back(0.0f);
	pyramidTexCoords.push_back(0.0f);

	// Vertex 12 - Base back
	pyramidVertices.push_back(-1.0f);
	pyramidVertices.push_back(-1.0f);
	pyramidVertices.push_back(-1.0f);
	pyramidNormals.push_back(-0.816f);
	pyramidNormals.push_back(0.577f);
	pyramidNormals.push_back(0.0f);
	pyramidTexCoords.push_back(1.0f);
	pyramidTexCoords.push_back(0.0f);
}

void Pyramid::Initialize()
{
	// Create the pyramid data
	CreatePyramid();

	// Create VAO
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Create VBO for position
	glGenBuffers(1, &vbo_position);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_position);
	glBufferData(GL_ARRAY_BUFFER, pyramidVertices.size() * sizeof(GLfloat), pyramidVertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(MST_ATTRIBUTES_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(MST_ATTRIBUTES_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Create VBO for normals
	glGenBuffers(1, &vbo_normal);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_normal);
	glBufferData(GL_ARRAY_BUFFER, pyramidNormals.size() * sizeof(GLfloat), pyramidNormals.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(MST_ATTRIBUTES_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(MST_ATTRIBUTES_NORMAL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Create VBO for texture coordinates
	glGenBuffers(1, &vbo_texcoord);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_texcoord);
	glBufferData(GL_ARRAY_BUFFER, pyramidTexCoords.size() * sizeof(GLfloat), pyramidTexCoords.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(MST_ATTRIBUTES_TEXCOORD, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(MST_ATTRIBUTES_TEXCOORD);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Unbind VAO
	glBindVertexArray(0);
}

void Pyramid::Display()
{
	// Bind VAO
	glBindVertexArray(vao);

	// Draw pyramid (12 vertices for 4 triangular faces)
	glDrawArrays(GL_TRIANGLES, 0, 12);

	// Unbind VAO and shader
	glBindVertexArray(0);
}

void Pyramid::Resize(int width, int height)
{
	// No specific resize operations needed for the pyramid
}

void Pyramid::Uninitialize()
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
}
