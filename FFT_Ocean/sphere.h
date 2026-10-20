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
	void Display(mat4 &projectionMatrix, mat4 &modelMatrix, mat4 &viewMatrix);
	void Resize(int width, int height);
	void Uninitialize();
	void ToggleLight();
	void SetLight(bool enable);

private:
	GLuint vao;
	GLuint vbo_position;
	GLuint vbo_normal;
	GLuint ebo; // Element buffer object for indices

	// Shader uniforms
	GLuint modelMatrixUniform;
	GLuint viewMatrixUniform;
	GLuint projectionMatrixUniform;
	GLuint lightKeyPressedUniform;


	Shader *vertexShader;
	Shader *fragmentShader;
	Program *shaderProgram;


	bool enableLight;

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
	  lightKeyPressedUniform(0), enableLight(true),
	  radius(1.0f), stacks(30), slices(30), indexCount(0)
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

	// Create vertex shader with the lighting vertex shader
	vertexShader = new Shader("multi_light_vertex_shader.txt", GL_VERTEX_SHADER, "vertex_log.txt");

	LOG_ENTRY("log.txt", "Vertex shader created successfully");

	// Create fragment shader with the lighting fragment shader
	fragmentShader = new Shader("multi_light_fragment_shader.txt", GL_FRAGMENT_SHADER, "fragment_log.txt");

	LOG_ENTRY("log.txt", "Fragment shader created successfully");

	// Create and link shader program
	shaderProgram = new Program(2, vertexShader->GetObject(), fragmentShader->GetObject());

	glBindAttribLocation(shaderProgram->GetObject(), MST_ATTRIBUTES_POSITION, "vPosition");
	glBindAttribLocation(shaderProgram->GetObject(), MST_ATTRIBUTES_COLOR, "vColor");
	glBindAttribLocation(shaderProgram->GetObject(), MST_ATTRIBUTES_TEXCOORD, "vTexCoord");
	glBindAttribLocation(shaderProgram->GetObject(), MST_ATTRIBUTES_NORMAL, "vNormal");

	shaderProgram->LinkProgram("log.txt");

	LOG_ENTRY("log.txt", "Sphere shader program linked successfully");

	// Get uniform locations
	modelMatrixUniform = glGetUniformLocation(shaderProgram->GetObject(), "u_modelMatrix");
	viewMatrixUniform = glGetUniformLocation(shaderProgram->GetObject(), "u_viewMatrix");
	projectionMatrixUniform = glGetUniformLocation(shaderProgram->GetObject(), "u_ProjectionMatrix");
	lightKeyPressedUniform = glGetUniformLocation(shaderProgram->GetObject(), "u_lKeyPressed");

	

	InitializeMultiLight(shaderProgram);

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

void Sphere::Display(mat4 &projectionMatrix, mat4 &modelMatrix, mat4 &viewMatrix)
{
	// Use the shader program
	glUseProgram(shaderProgram->GetObject());

	// Set the matrix uniforms
	glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, projectionMatrix);
	glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, viewMatrix);
	glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, modelMatrix);

	static GLfloat angle = 0.0f;
	angle += 0.005f; // Increment angle for rotation

	// Set lighting uniforms
	if (true) // enableLight)
	{
		glUniform1i(lightKeyPressedUniform, 1);

		// Set light properties
		SetLights();

// Set Material Properties
SetMaterialProperties();

		
	}
	else
	{
		glUniform1i(lightKeyPressedUniform, 0);
	}

	// Bind VAO
	glBindVertexArray(vao);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	// Draw indexed triangles
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Unbind VAO and shader
	glBindVertexArray(0);
	glUseProgram(0);
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

void Sphere::ToggleLight()
{
	enableLight = !enableLight;
}

void Sphere::SetLight(bool enable)
{
	enableLight = enable;
}