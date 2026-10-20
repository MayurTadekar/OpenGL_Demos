/***************************************************************************
 * S.G.M.P
 * @file: sphere.h
 * @brief: Implementation of a sphere class for OpenGL rendering with lighting
 * @date: Wednesday 2025-06-18
 ***************************************************************************/

#pragma once

#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/vmath/vmath.h>
#include <vector>
#include <cmath>
#include "Shader.h"
#include "Program.h"
#include "macros.h"
#include "common.h"
#include "multilight.h"

using namespace vmath;

class Sphere
{
public:
	Sphere();
	~Sphere();

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
	GLuint ebo; // Element buffer object for indices

	// Sphere parameters
	GLfloat radius;
	GLuint stacks;
	GLuint slices;
	GLuint indexCount;

	std::vector<GLfloat> sphereVertices;
	std::vector<GLfloat> sphereNormals;
	std::vector<GLuint> sphereIndices;

	void CreateSphere();
};

Sphere::Sphere()
	: vao(0), vbo_position(0), vbo_normal(0), ebo(0),
	  radius(4.0f), stacks(30), slices(30), indexCount(0)
{
	// Initialize lighting parameters
}

Sphere::~Sphere()
{
	Uninitialize();
}

void Sphere::CreateSphere()
{
	// Clear previous data
	sphereVertices.clear();
	sphereNormals.clear();
	sphereIndices.clear();

	// float stackStep = ;
	// float sliceStep = ;

	// Generate vertices, normals and colors
	for (GLuint ole = 0; ole <= stacks; ++ole)
	{
		float phi = (float)ole * M_PI / (float)stacks; // angle from the top

		for (GLuint ile = 0; ile <= slices; ++ile)
		{
			float theta = (float)ile * 2.0f * M_PI / (float)slices; // angle around the sphere

			float x = sinf(phi) * cosf(theta);
			float y = cosf(phi);
			float z = sinf(phi) * sinf(theta);

			sphereVertices.push_back(radius * x);
			sphereVertices.push_back(radius * y);
			sphereVertices.push_back(radius * z);

			// Normal is the same as vertex for a sphere
			sphereNormals.push_back(x);
			sphereNormals.push_back(y);
			sphereNormals.push_back(z);
		}
	}

	// Generate indices
	for (GLuint i = 0; i < stacks; ++i)
	{
		GLuint k1 = i * (slices + 1);
		GLuint k2 = k1 + slices + 1;

		for (GLuint j = 0; j < slices; ++j, ++k1, ++k2)
		{
			// For triangle 1
			if (i != 0)
			{
				sphereIndices.push_back(k1);
				sphereIndices.push_back(k2);
				sphereIndices.push_back(k1 + 1);
			}

			// For triangle 2
			if (i != (stacks - 1))
			{
				sphereIndices.push_back(k1 + 1);
				sphereIndices.push_back(k2);
				sphereIndices.push_back(k2 + 1);
			}
		}
	}

	indexCount = sphereIndices.size();
}

void Sphere::Initialize()
{
	// Create the sphere data
	CreateSphere();

	LOG_ENTRY("log.txt", "Sphere data created successfully");

	// Create VAO
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	{
		// Create VBO for position
		glGenBuffers(1, &vbo_position);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_position);
		{
			glBufferData(GL_ARRAY_BUFFER, sphereVertices.size() * sizeof(GLfloat), sphereVertices.data(), GL_STATIC_DRAW);
			glVertexAttribPointer(MST_ATTRIBUTES_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
			glEnableVertexAttribArray(MST_ATTRIBUTES_POSITION);
		}
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Create VBO for normals
		glGenBuffers(1, &vbo_normal);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_normal);
		{
			glBufferData(GL_ARRAY_BUFFER, sphereNormals.size() * sizeof(GLfloat), sphereNormals.data(), GL_STATIC_DRAW);
			glVertexAttribPointer(MST_ATTRIBUTES_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
			glEnableVertexAttribArray(MST_ATTRIBUTES_NORMAL);
		}
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Create EBO
		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sphereIndices.size() * sizeof(GLuint), sphereIndices.data(), GL_STATIC_DRAW);
		// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	// Unbind VAO
	glBindVertexArray(0);

	// Enable depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	LOG_ENTRY("log.txt", "Sphere initialization complete with lighting shaders");
}

void Sphere::Display()
{
	// Bind VAO
	glBindVertexArray(vao);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	// Draw indexed triangles
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Unbind VAO and shader
	glBindVertexArray(0);
}

void Sphere::Resize(int width, int height)
{
	// No specific resize operations needed for the sphere
}

void Sphere::Uninitialize()
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
