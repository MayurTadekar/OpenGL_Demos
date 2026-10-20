/***************************************************************************
 * S.G.M.P
 * @file: Plane.h
 * @brief: Implementation of a Plane class for OpenGL rendering
 * @author: Mayur S. Tadekar(mrtadekar@gmail.com)
 * @copyright ©2020-2025 MarshallingVoid
 * @date: Friday 2026-06-19 7:15:14 PM
 ***************************************************************************/
#pragma once

#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/vmath/vmath.h>
#include "macros.h"
#include <vector>

using namespace vmath;

class Plane
{
public:
	Plane();
	Plane(long points, float scale);
	~Plane();

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
	GLuint ebo; // Element buffer object for indices

	bool enableLight;

	float x_pos;
	float y_pos;
	bool enableGrayscale;

	long m_points;
	float m_scale;

	std::vector<float> planeVertices;
	std::vector<float> planeColor;
	std::vector<int> planeIndices;

	void GeneratePlane();
};

Plane::Plane()
	: vao(0), vbo_position(0), vbo_color(0), ebo(0), enableLight(true), enableGrayscale(false),
	  x_pos(0.0f), y_pos(0.0f), m_points(10), m_scale(5)
{
	Initialize();
}

Plane::Plane(long points, float scale)
	: vao(0), vbo_position(0), vbo_color(0), ebo(0), enableLight(true), enableGrayscale(false),
	  x_pos(0.0f), y_pos(0.0f), m_points(points), m_scale(scale)
{
	Initialize();
}

Plane::~Plane()
{
	Uninitialize();
}

void Plane::GeneratePlane()
{
	// Code
	planeVertices.clear();
	planeColor.clear();
	planeIndices.clear();

	float halfX = (m_points * m_scale) / 2.0f;
	float halfZ = (m_points * m_scale) / 2.0f;

	for (long ole = 0; ole < m_points; ++ole)
	{
		for (long ile = 0; ile < m_points; ++ile)
		{
			float x = ile * m_scale - halfX;
			float y = 0.0f;
			float z = ole * m_scale - halfZ;

			planeVertices.push_back(x);
			planeVertices.push_back(y);
			planeVertices.push_back(z);

			planeColor.push_back(1.0f);
			planeColor.push_back(1.0f);
			planeColor.push_back(1.0f);

			if (ole < m_points - 1 && ile < m_points - 1)
			{
				planeIndices.push_back(ole * m_points + ile);
				planeIndices.push_back(ole * m_points + ile + 1);
				planeIndices.push_back((ole + 1) * m_points + ile);

				planeIndices.push_back(ole * m_points + ile + 1);
				planeIndices.push_back((ole + 1) * m_points + ile + 1);
				planeIndices.push_back((ole + 1) * m_points + ile);
			}
		}
	}
}

void Plane::Initialize()
{
	// Code

	GeneratePlane();

	// Vertex data for the Plane
	// const GLfloat PlaneVertices[] = {
	// 	-1.0f, 0.0f, 1.0f, // Top-left
	// 	1.0f, 0.0f, 1.0f,  // Top-right
	// 	1.0f, 0.0f, -1.0f, // Bottom-right
	// 	-1.0f, 0.0f, -1.0f // Bottom-left
	// };

	// // Color data for the Plane
	// const GLfloat PlaneColors[] = {
	// 	1.0f, 0.0f, 0.0f, // Red (top-left)
	// 	0.0f, 1.0f, 0.0f, // Green (top-right)
	// 	0.0f, 0.0f, 1.0f, // Blue (bottom-right)
	// 	1.0f, 1.0f, 0.0f  // Yellow (bottom-left)
	// };

	// // Indices for the Plane (two triangles)
	// const GLuint PlaneIndices[] = {
	// 	0, 1, 2, // First triangle (top-left, top-right, bottom-right)
	// 	2, 3, 0	 // Second triangle (bottom-right, bottom-left, top-left)
	// };

	// Create VAO
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Create VBO for position
	glGenBuffers(1, &vbo_position);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_position);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * planeVertices.size(), planeVertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(MST_ATTRIBUTES_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(MST_ATTRIBUTES_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Create VBO for color
	glGenBuffers(1, &vbo_color);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_color);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * planeColor.size(), planeColor.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(MST_ATTRIBUTES_COLOR, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(MST_ATTRIBUTES_COLOR);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Create EBO for indices
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * planeIndices.size(), planeIndices.data(), GL_STATIC_DRAW);

	// Unbind
	glBindVertexArray(0);
}

void Plane::Display()
{

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

	// Bind VAO
	glBindVertexArray(vao);

	// Draw the Plane using indexed drawing
	glDrawElements(GL_TRIANGLES, planeIndices.size(), GL_UNSIGNED_INT, 0);

	// Unbind VAO and shader
	glBindVertexArray(0);

	glDisable(GL_CULL_FACE);
}

void Plane::Resize(int width, int height)
{
	// Nothing specific to do for a resize
}

void Plane::Uninitialize()
{
	// Code
	planeVertices.clear();
	planeColor.clear();
	planeIndices.clear();

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

void Plane::ToggleGrayscale()
{
	enableGrayscale = !enableGrayscale;
}

void Plane::SetGrayscale(bool enable)
{
	enableGrayscale = enable;
}