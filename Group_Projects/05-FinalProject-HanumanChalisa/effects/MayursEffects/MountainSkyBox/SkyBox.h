/***************************************************************************
 * S.G.M.P
 * @file: SkyBox.h
 * @brief: Implementation of a SkyBox class for OpenGL rendering
 * @date: Wednesday 2025-06-18
 ***************************************************************************/

#pragma once

#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/vmath/vmath.h>
#include <vector>
#include "../Common/Shader.h"
#include "../Common/Program.h"
#include "../Common/macros.h"
#include "../../../include/common.h"

using namespace vmath;

class SkyBox
{
public:
	SkyBox();
	~SkyBox();

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
	GLuint vbo_color;
	GLuint vbo_texcoord;
	GLuint ebo;

	bool enableLight;

	// SkyBox data
	std::vector<GLfloat> SkyBoxVertices;
	std::vector<GLfloat> SkyBoxColor;
	std::vector<GLfloat> SkyBoxNormals;
	std::vector<GLfloat> SkyBoxTexCoords;

	void CreateSkyBox();
};

SkyBox::SkyBox()
	: vao(0), vbo_position(0), vbo_normal(0), vbo_texcoord(0), enableLight(true)
{
	// Initialize lighting parameters
}

SkyBox::~SkyBox()
{
	Uninitialize();
}

void SkyBox::CreateSkyBox()
{
	// Clear any existing data
	SkyBoxVertices.clear();
	SkyBoxNormals.clear();
	SkyBoxTexCoords.clear();
}

void SkyBox::Initialize()
{
	// Create the SkyBox data
	// CreateSkyBox();

	// SkyBox half-size (from center)
	float size = 1.0f;

	float deltaX = 1.0f / 3.0f;
	float deltaY = 1.0f / 2.0f;

	GLfloat skyboxVertices[] =
		{
			// Front
			-size, -size, size,
			size, -size, size,
			size, size, size,

			size, size, size,
			-size, size, size,
			-size, -size, size,

			// Back
			size, -size, -size,
			-size, -size, -size,
			-size, size, -size,

			-size, size, -size,
			size, size, -size,
			size, -size, -size,

			// Left
			-size, -size, -size,
			-size, -size, size,
			-size, size, size,

			-size, size, size,
			-size, size, -size,
			-size, -size, -size,

			// Right
			size, -size, size,
			size, -size, -size,
			size, size, -size,

			size, size, -size,
			size, size, size,
			size, -size, size,

			// Top
			-size, size, size,
			size, size, size,
			size, size, -size,

			size, size, -size,
			-size, size, -size,
			-size, size, size,

			// Bottom
			-size, -size, -size,
			size, -size, -size,
			size, -size, size,

			size, -size, size,
			-size, -size, size,
			-size, -size, -size};

	GLfloat skyboxTexCoords[] =
		{
			// FRONT
			0.98, 0.5f,
			deltaX * 2.0f, 0.5f,
			deltaX * 2.0f, 0.98f,

			deltaX * 2.0f, 0.98f,
			0.98, 0.98f,
			0.98, 0.5f,

			// BACK
			deltaX * 2.0f, 0.0f,
			deltaX * 1.0f, 0.0f,
			deltaX * 1.0f, 0.5f,

			deltaX * 1.0f, 0.5f,
			deltaX * 2.0f, 0.5f,
			deltaX * 2.0f, 0.0f,

			// LEFT
			deltaX * 1.0f, 0.0f,
			0.01f, 0.0f,
			0.01f, 0.48f,

			0.01f, 0.48f,
			deltaX * 1.0f, 0.48f,
			deltaX * 1.0f, 0.0f,

			// RIGHT
			deltaX * 3.0f, 0.0f,
			deltaX * 2.0f, 0.0f,
			deltaX * 2.0f, 0.49f,

			deltaX * 2.0f, 0.49f,
			deltaX * 3.0f, 0.49f,
			deltaX * 3.0f, 0.0f,

			// TOP
			deltaX * 1.0f + 0.01f, 0.49f,
			deltaX * 2.0f - 0.01f, 0.49f,
			deltaX * 2.0f - 0.01f, 0.99f,

			deltaX * 2.0f - 0.01f, 0.99f,
			deltaX * 1.0f + 0.01f, 0.99f,
			deltaX * 1.0f + 0.01f, 0.49f,

			// BOTTOM
			0.0f, 1.0f,
			deltaX * 1.0f, 1.0f,
			deltaX * 1.0f, 0.5f,

			deltaX * 1.0f, 0.5f,
			0.0f, 0.5f,
			0.0f, 1.0f};

	// Create VAO
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Create VBO for position
	glGenBuffers(1, &vbo_position);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_position);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(MST_ATTRIBUTES_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(MST_ATTRIBUTES_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// // Create VBO for normals
	// glGenBuffers(1, &vbo_normal);
	// glBindBuffer(GL_ARRAY_BUFFER, vbo_normal);
	// glBufferData(GL_ARRAY_BUFFER, SkyBoxNormals.size() * sizeof(GLfloat), SkyBoxNormals.data(), GL_STATIC_DRAW);
	// glVertexAttribPointer(MST_ATTRIBUTES_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	// glEnableVertexAttribArray(MST_ATTRIBUTES_NORMAL);
	// glBindBuffer(GL_ARRAY_BUFFER, 0);

	// // Create VBO for color
	// glGenBuffers(1, &vbo_color);
	// glBindBuffer(GL_ARRAY_BUFFER, vbo_color);
	// glBufferData(GL_ARRAY_BUFFER, SkyBoxColor.size() * sizeof(GLfloat), SkyBoxColor.data(), GL_STATIC_DRAW);
	// glVertexAttribPointer(MST_ATTRIBUTES_COLOR, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	// glEnableVertexAttribArray(MST_ATTRIBUTES_COLOR);
	// glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Create VBO for texture coordinates
	glGenBuffers(1, &vbo_texcoord);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_texcoord);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxTexCoords), skyboxTexCoords, GL_STATIC_DRAW);
	glVertexAttribPointer(MST_ATTRIBUTES_TEXCOORD, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(MST_ATTRIBUTES_TEXCOORD);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// glGenBuffers(1, &ebo);
	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	// glBufferData(
	// 	GL_ELEMENT_ARRAY_BUFFER,
	// 	sizeof(cubeIndices),
	// 	cubeIndices,
	// 	GL_STATIC_DRAW);
	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	// Unbind VAO
	glBindVertexArray(0);

	// Enable depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

void SkyBox::Display()
{
	// Bind VAO
	glBindVertexArray(vao);

	// Draw SkyBox (36 vertices for a complete SkyBox without indices)
	glDrawArrays(GL_TRIANGLES, 0, 6 * 5);
	// glDrawElements(
	// 	GL_TRIANGLES,
	// 	12, // static_cast<GLsizei>(SkyBoxIndices.size()),
	// 	GL_UNSIGNED_INT,
	// 	nullptr);

	// Unbind VAO and shader
	glBindVertexArray(0);
}

void SkyBox::Resize(int width, int height)
{
	// No specific resize operations needed for the SkyBox
}

void SkyBox::Uninitialize()
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

void SkyBox::ToggleLight()
{
	enableLight = !enableLight;
}

void SkyBox::SetLight(bool enable)
{
	enableLight = enable;
}