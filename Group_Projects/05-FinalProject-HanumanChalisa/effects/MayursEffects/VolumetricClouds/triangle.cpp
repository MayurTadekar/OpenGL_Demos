

#include <GL/glew.h>
#include <GL/GL.h>
#include "./../../../include/vmath.h"
#include "../Common/Shader.h"
#include "../Common/Program.h"
#include "../Common/macros.h"

#include "triangle.h"

Triangle::Triangle()
	: vao(0), vbo_position(0), vbo_color(0),
	  vbo_normal(0), vbo_texcoord(0),
	  enableLight(true), enableGrayscale(false),
	  x_pos(0.0f), y_pos(0.0f)
{
}

Triangle::~Triangle()
{
	Uninitialize();
}

void Triangle::Initialize()
{
	// Vertex data for the triangle
	const GLfloat triangleVertices[] = {
		0.0f, 1.0f, 0.0f,	// Top
		-1.0f, -1.0f, 0.0f, // Left
		1.0f, -1.0f, 0.0f	// Right
	};

	// Color data for the triangle
	const GLfloat triangleColors[] = {
		1.0f,
		0.0f,
		0.0f, // Red (for top vertex)
		0.0f,
		1.0f,
		0.0f, // Green (for left vertex)
		0.0f,
		0.0f,
		1.0f, // Blue (for right vertex)
	};

	const GLfloat triangleTexCoords[] = {
		0.5f, 1.0f, // Top vertex texture coordinate
		0.0f, 0.0f, // Left vertex texture coordinate
		1.0f, 0.0f	// Right vertex texture coordinate
	};

	const GLfloat triangleNormals[] = {
		0.0f, 0.0f, 1.0f, // Normal for all vertices (pointing out of the screen)
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f};

	// Create VAO
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	{
		// Create VBO for position
		glGenBuffers(1, &vbo_position);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_position);
		glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);
		glVertexAttribPointer(MST_ATTRIBUTES_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(MST_ATTRIBUTES_POSITION);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Create VBO for texture coordinates
		glGenBuffers(1, &vbo_texcoord);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_texcoord);
		glBufferData(GL_ARRAY_BUFFER, sizeof(triangleTexCoords), triangleTexCoords, GL_STATIC_DRAW);
		glVertexAttribPointer(MST_ATTRIBUTES_TEXCOORD, 2, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(MST_ATTRIBUTES_TEXCOORD);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Create VBO for normals (not used in this triangle, but included for completeness)
		glGenBuffers(1, &vbo_normal);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_normal);
		glBufferData(GL_ARRAY_BUFFER, sizeof(triangleNormals), triangleNormals, GL_STATIC_DRAW);
		glVertexAttribPointer(MST_ATTRIBUTES_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(MST_ATTRIBUTES_NORMAL);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Create VBO for color
		glGenBuffers(1, &vbo_color);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_color);
		glBufferData(GL_ARRAY_BUFFER, sizeof(triangleColors), triangleColors, GL_STATIC_DRAW);
		glVertexAttribPointer(MST_ATTRIBUTES_COLOR, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(MST_ATTRIBUTES_COLOR);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	// Unbind VAO
	glBindVertexArray(0);
}

void Triangle::Display()
{
	// Bind VAO
	glBindVertexArray(vao);

	// Draw the triangle
	glDrawArrays(GL_TRIANGLES, 0, 3);

	// Unbind VAO
	glBindVertexArray(0);
}

void Triangle::Resize(int width, int height)
{
	// Adjust the viewport and projection matrix based on the new window size.
	if (height < 1)
		height = 1;

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	// perspectiveProjectionMatrix = perspective(45.0f, (float)width / (float)height, 0.1f, 100.0f);
}

void Triangle::Uninitialize()
{
	// Clean up OpenGL resources, such as VAOs, VBOs, and shaders.
	if (vao)
	{
		glDeleteVertexArrays(1, &vao);
		vao = 0;
	}

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
}

void Triangle::ToggleGrayscale()
{
	enableGrayscale = !enableGrayscale;
}

void Triangle::SetGrayscale(bool enable)
{
	enableGrayscale = enable;
}
