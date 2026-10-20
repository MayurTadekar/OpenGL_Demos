/***************************************************************************
 * S.G.M.P
 * @file: square.h
 * @brief: Implementation of a square class for OpenGL rendering
 * @author: Mayur S. Tadekar(mrtadekar@gmail.com)
 * @copyright ©2020-2025 MarshallingVoid
 * @date: Monday 2025-06-16 0:29:23 AM
 ***************************************************************************/

#pragma once

#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/vmath/vmath.h>
#include "macros.h"

using namespace vmath;

class Square
{
public:
	Square();
	~Square();

	void Initialize();
	void Display();
	void Resize(int width, int height);
	void Uninitialize();
	void ToggleGrayscale();
	void SetGrayscale(bool enable);

private:
	GLuint vao;
	GLuint vbo_position;
	GLuint vbo_color;
	GLuint vbo_texCoord;
	GLuint ebo; // Element buffer object for indices

	bool enableLight;

	float x_pos;
	float y_pos;
	bool enableGrayscale;
};

Square::Square()
	: vao(0), vbo_position(0), vbo_color(0), ebo(0), enableLight(true), enableGrayscale(false),
	  x_pos(0.0f), y_pos(0.0f)
{
}

Square::~Square()
{
	Uninitialize();
}

void Square::Initialize()
{
	// Vertex data for the square
	const GLfloat squareVertices[] = {
		-1.0f,
		1.0f,
		0.0f, // Top-left
		-1.0f,
		-1.0f,
		0.0f, // Bottom-left
		1.0f,
		-1.0f,
		0.0f, // Bottom-right

		-1.0f,
		1.0f,
		0.0f, // Top-left
		1.0f,
		-1.0f,
		0.0f, // Bottom-right
		1.0f,
		1.0f,
		0.0f, // top-right

	};

	// Color data for the square
	const GLfloat squareColors[] = {
		1.0f,
		0.0f,
		0.0f, // Red (top-left)
		0.0f,
		1.0f,
		0.0f, // Green (top-right)
		0.0f,
		0.0f,
		1.0f, // Blue (bottom-right)

		1.0f,
		0.0f,
		0.0f, // Red (top-left)
		0.0f,
		0.0f,
		1.0f, // Blue (bottom-right)
		0.0f,
		1.0f,
		0.0f, // Green (top-right)
	};

	// Texture coordinates for the square
	const GLfloat squareTexCoords[] = {
		0.0f,
		1.0f, // Top-left
		0.0f,
		0.0f, // Bottom-left
		1.0f,
		0.0f, // Bottom-right

		0.0f,
		1.0f, // Top-left
		1.0f,
		0.0f, // Bottom-right
		1.0f,
		1.0f, // Bottom-left
	};

	// Indices for the square (two triangles)
	// const GLuint squareIndices[] = {
	// 	0, 1, 2, // First triangle (top-left, top-right, bottom-right)
	// 	2, 3, 0	 // Second triangle (bottom-right, bottom-left, top-left)
	// };

	// Create VAO
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Create VBO for position
	glGenBuffers(1, &vbo_position);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_position);
	glBufferData(GL_ARRAY_BUFFER, sizeof(squareVertices), squareVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(MST_ATTRIBUTES_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(MST_ATTRIBUTES_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Create VBO for color
	glGenBuffers(1, &vbo_color);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_color);
	glBufferData(GL_ARRAY_BUFFER, sizeof(squareColors), squareColors, GL_STATIC_DRAW);
	glVertexAttribPointer(MST_ATTRIBUTES_COLOR, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(MST_ATTRIBUTES_COLOR);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Create VBO for texture coordinates
	glGenBuffers(1, &vbo_texCoord);
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo_texCoord);
		glBufferData(GL_ARRAY_BUFFER, sizeof(squareTexCoords), squareTexCoords, GL_STATIC_DRAW);
		glVertexAttribPointer(MST_ATTRIBUTES_TEXCOORD, 2, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(MST_ATTRIBUTES_TEXCOORD);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// // Create EBO for indices
	// glGenBuffers(1, &ebo);
	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	// glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(squareIndices), squareIndices, GL_STATIC_DRAW);

	// Unbind
	glBindVertexArray(0);
}

void Square::Display()
{

	// Bind VAO
	glBindVertexArray(vao);

	// Draw the square using indexed drawing
	glDrawArrays(GL_TRIANGLES, 0, 6);

	// Unbind VAO and shader
	glBindVertexArray(0);
}

void Square::Resize(int width, int height)
{
	// Nothing specific to do for a resize
}

void Square::Uninitialize()
{
	if (vbo_position)
	{
		glDeleteBuffers(1, &vbo_position);
		vbo_position = 0;
	}

	if (vbo_color)
	{
		glDeleteBuffers(1, &vbo_color);
		vbo_color = 0;
	}

	if (ebo)
	{
		glDeleteBuffers(1, &ebo);
		ebo = 0;
	}

	if (vao)
	{
		glDeleteVertexArrays(1, &vao);
		vao = 0;
	}
}

void Square::ToggleGrayscale()
{
	enableGrayscale = !enableGrayscale;
}

void Square::SetGrayscale(bool enable)
{
	enableGrayscale = enable;
}