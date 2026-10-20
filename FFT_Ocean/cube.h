/***************************************************************************
 * S.G.M.P
 * @file: cube.h
 * @brief: Implementation of a cube class for OpenGL rendering
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

class Cube
{
public:
	Cube();
	~Cube();

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

	// Cube data
	std::vector<GLfloat> cubeVertices;
	std::vector<GLfloat> cubeNormals;
	std::vector<GLfloat> cubeTexCoords;

	void CreateCube();
};

Cube::Cube()
	: vao(0), vbo_position(0), vbo_normal(0), vbo_texcoord(0),
	  lightKeyPressedUniform(0), enableLight(true)
{
	// Initialize lighting parameters
}

Cube::~Cube()
{
	Uninitialize();
}

void Cube::CreateCube()
{
	// Clear any existing data
	cubeVertices.clear();
	cubeNormals.clear();
	cubeTexCoords.clear();

	// Cube half-size (from center)
	float size = 0.5f;

	// FRONT FACE (Z+)
	// Triangle 1
	// Vertex 1
	cubeVertices.push_back(-size);
	cubeVertices.push_back(-size);
	cubeVertices.push_back(size); // Position
	cubeNormals.push_back(0.0f);
	cubeNormals.push_back(0.0f);
	cubeNormals.push_back(1.0f); // Normal
	cubeTexCoords.push_back(0.0f);
	cubeTexCoords.push_back(0.0f); // TexCoord

	// Vertex 2
	cubeVertices.push_back(size);
	cubeVertices.push_back(-size);
	cubeVertices.push_back(size); // Position
	cubeNormals.push_back(0.0f);
	cubeNormals.push_back(0.0f);
	cubeNormals.push_back(1.0f); // Normal
	cubeTexCoords.push_back(1.0f);
	cubeTexCoords.push_back(0.0f); // TexCoord

	// Vertex 3
	cubeVertices.push_back(size);
	cubeVertices.push_back(size);
	cubeVertices.push_back(size); // Position
	cubeNormals.push_back(0.0f);
	cubeNormals.push_back(0.0f);
	cubeNormals.push_back(1.0f); // Normal
	cubeTexCoords.push_back(1.0f);
	cubeTexCoords.push_back(1.0f); // TexCoord

	// Triangle 2
	// Vertex 4
	cubeVertices.push_back(size);
	cubeVertices.push_back(size);
	cubeVertices.push_back(size); // Position
	cubeNormals.push_back(0.0f);
	cubeNormals.push_back(0.0f);
	cubeNormals.push_back(1.0f); // Normal
	cubeTexCoords.push_back(1.0f);
	cubeTexCoords.push_back(1.0f); // TexCoord

	// Vertex 5
	cubeVertices.push_back(-size);
	cubeVertices.push_back(size);
	cubeVertices.push_back(size); // Position
	cubeNormals.push_back(0.0f);
	cubeNormals.push_back(0.0f);
	cubeNormals.push_back(1.0f); // Normal
	cubeTexCoords.push_back(0.0f);
	cubeTexCoords.push_back(1.0f); // TexCoord

	// Vertex 6
	cubeVertices.push_back(-size);
	cubeVertices.push_back(-size);
	cubeVertices.push_back(size); // Position
	cubeNormals.push_back(0.0f);
	cubeNormals.push_back(0.0f);
	cubeNormals.push_back(1.0f); // Normal
	cubeTexCoords.push_back(0.0f);
	cubeTexCoords.push_back(0.0f); // TexCoord

	// BACK FACE (Z-)
	// Triangle 1
	cubeVertices.push_back(size);
	cubeVertices.push_back(-size);
	cubeVertices.push_back(-size);
	cubeNormals.push_back(0.0f);
	cubeNormals.push_back(0.0f);
	cubeNormals.push_back(-1.0f);
	cubeTexCoords.push_back(0.0f);
	cubeTexCoords.push_back(0.0f);

	cubeVertices.push_back(-size);
	cubeVertices.push_back(-size);
	cubeVertices.push_back(-size);
	cubeNormals.push_back(0.0f);
	cubeNormals.push_back(0.0f);
	cubeNormals.push_back(-1.0f);
	cubeTexCoords.push_back(1.0f);
	cubeTexCoords.push_back(0.0f);

	cubeVertices.push_back(-size);
	cubeVertices.push_back(size);
	cubeVertices.push_back(-size);
	cubeNormals.push_back(0.0f);
	cubeNormals.push_back(0.0f);
	cubeNormals.push_back(-1.0f);
	cubeTexCoords.push_back(1.0f);
	cubeTexCoords.push_back(1.0f);

	// Triangle 2
	cubeVertices.push_back(-size);
	cubeVertices.push_back(size);
	cubeVertices.push_back(-size);
	cubeNormals.push_back(0.0f);
	cubeNormals.push_back(0.0f);
	cubeNormals.push_back(-1.0f);
	cubeTexCoords.push_back(1.0f);
	cubeTexCoords.push_back(1.0f);

	cubeVertices.push_back(size);
	cubeVertices.push_back(size);
	cubeVertices.push_back(-size);
	cubeNormals.push_back(0.0f);
	cubeNormals.push_back(0.0f);
	cubeNormals.push_back(-1.0f);
	cubeTexCoords.push_back(0.0f);
	cubeTexCoords.push_back(1.0f);

	cubeVertices.push_back(size);
	cubeVertices.push_back(-size);
	cubeVertices.push_back(-size);
	cubeNormals.push_back(0.0f);
	cubeNormals.push_back(0.0f);
	cubeNormals.push_back(-1.0f);
	cubeTexCoords.push_back(0.0f);
	cubeTexCoords.push_back(0.0f);

	// RIGHT FACE (X+)
	// Triangle 1
	cubeVertices.push_back(size);
	cubeVertices.push_back(-size);
	cubeVertices.push_back(size);
	cubeNormals.push_back(1.0f);
	cubeNormals.push_back(0.0f);
	cubeNormals.push_back(0.0f);
	cubeTexCoords.push_back(0.0f);
	cubeTexCoords.push_back(0.0f);

	cubeVertices.push_back(size);
	cubeVertices.push_back(-size);
	cubeVertices.push_back(-size);
	cubeNormals.push_back(1.0f);
	cubeNormals.push_back(0.0f);
	cubeNormals.push_back(0.0f);
	cubeTexCoords.push_back(1.0f);
	cubeTexCoords.push_back(0.0f);

	cubeVertices.push_back(size);
	cubeVertices.push_back(size);
	cubeVertices.push_back(-size);
	cubeNormals.push_back(1.0f);
	cubeNormals.push_back(0.0f);
	cubeNormals.push_back(0.0f);
	cubeTexCoords.push_back(1.0f);
	cubeTexCoords.push_back(1.0f);

	// Triangle 2
	cubeVertices.push_back(size);
	cubeVertices.push_back(size);
	cubeVertices.push_back(-size);
	cubeNormals.push_back(1.0f);
	cubeNormals.push_back(0.0f);
	cubeNormals.push_back(0.0f);
	cubeTexCoords.push_back(1.0f);
	cubeTexCoords.push_back(1.0f);

	cubeVertices.push_back(size);
	cubeVertices.push_back(size);
	cubeVertices.push_back(size);
	cubeNormals.push_back(1.0f);
	cubeNormals.push_back(0.0f);
	cubeNormals.push_back(0.0f);
	cubeTexCoords.push_back(0.0f);
	cubeTexCoords.push_back(1.0f);

	cubeVertices.push_back(size);
	cubeVertices.push_back(-size);
	cubeVertices.push_back(size);
	cubeNormals.push_back(1.0f);
	cubeNormals.push_back(0.0f);
	cubeNormals.push_back(0.0f);
	cubeTexCoords.push_back(0.0f);
	cubeTexCoords.push_back(0.0f);

	// LEFT FACE (X-)
	// Triangle 1
	cubeVertices.push_back(-size);
	cubeVertices.push_back(-size);
	cubeVertices.push_back(-size);
	cubeNormals.push_back(-1.0f);
	cubeNormals.push_back(0.0f);
	cubeNormals.push_back(0.0f);
	cubeTexCoords.push_back(0.0f);
	cubeTexCoords.push_back(0.0f);

	cubeVertices.push_back(-size);
	cubeVertices.push_back(-size);
	cubeVertices.push_back(size);
	cubeNormals.push_back(-1.0f);
	cubeNormals.push_back(0.0f);
	cubeNormals.push_back(0.0f);
	cubeTexCoords.push_back(1.0f);
	cubeTexCoords.push_back(0.0f);

	cubeVertices.push_back(-size);
	cubeVertices.push_back(size);
	cubeVertices.push_back(size);
	cubeNormals.push_back(-1.0f);
	cubeNormals.push_back(0.0f);
	cubeNormals.push_back(0.0f);
	cubeTexCoords.push_back(1.0f);
	cubeTexCoords.push_back(1.0f);

	// Triangle 2
	cubeVertices.push_back(-size);
	cubeVertices.push_back(size);
	cubeVertices.push_back(size);
	cubeNormals.push_back(-1.0f);
	cubeNormals.push_back(0.0f);
	cubeNormals.push_back(0.0f);
	cubeTexCoords.push_back(1.0f);
	cubeTexCoords.push_back(1.0f);

	cubeVertices.push_back(-size);
	cubeVertices.push_back(size);
	cubeVertices.push_back(-size);
	cubeNormals.push_back(-1.0f);
	cubeNormals.push_back(0.0f);
	cubeNormals.push_back(0.0f);
	cubeTexCoords.push_back(0.0f);
	cubeTexCoords.push_back(1.0f);

	cubeVertices.push_back(-size);
	cubeVertices.push_back(-size);
	cubeVertices.push_back(-size);
	cubeNormals.push_back(-1.0f);
	cubeNormals.push_back(0.0f);
	cubeNormals.push_back(0.0f);
	cubeTexCoords.push_back(0.0f);
	cubeTexCoords.push_back(0.0f);

	// TOP FACE (Y+)
	// Triangle 1
	cubeVertices.push_back(-size);
	cubeVertices.push_back(size);
	cubeVertices.push_back(size);
	cubeNormals.push_back(0.0f);
	cubeNormals.push_back(1.0f);
	cubeNormals.push_back(0.0f);
	cubeTexCoords.push_back(0.0f);
	cubeTexCoords.push_back(0.0f);

	cubeVertices.push_back(size);
	cubeVertices.push_back(size);
	cubeVertices.push_back(size);
	cubeNormals.push_back(0.0f);
	cubeNormals.push_back(1.0f);
	cubeNormals.push_back(0.0f);
	cubeTexCoords.push_back(1.0f);
	cubeTexCoords.push_back(0.0f);

	cubeVertices.push_back(size);
	cubeVertices.push_back(size);
	cubeVertices.push_back(-size);
	cubeNormals.push_back(0.0f);
	cubeNormals.push_back(1.0f);
	cubeNormals.push_back(0.0f);
	cubeTexCoords.push_back(1.0f);
	cubeTexCoords.push_back(1.0f);

	// Triangle 2
	cubeVertices.push_back(size);
	cubeVertices.push_back(size);
	cubeVertices.push_back(-size);
	cubeNormals.push_back(0.0f);
	cubeNormals.push_back(1.0f);
	cubeNormals.push_back(0.0f);
	cubeTexCoords.push_back(1.0f);
	cubeTexCoords.push_back(1.0f);

	cubeVertices.push_back(-size);
	cubeVertices.push_back(size);
	cubeVertices.push_back(-size);
	cubeNormals.push_back(0.0f);
	cubeNormals.push_back(1.0f);
	cubeNormals.push_back(0.0f);
	cubeTexCoords.push_back(0.0f);
	cubeTexCoords.push_back(1.0f);

	cubeVertices.push_back(-size);
	cubeVertices.push_back(size);
	cubeVertices.push_back(size);
	cubeNormals.push_back(0.0f);
	cubeNormals.push_back(1.0f);
	cubeNormals.push_back(0.0f);
	cubeTexCoords.push_back(0.0f);
	cubeTexCoords.push_back(0.0f);

	// BOTTOM FACE (Y-)
	// Triangle 1
	cubeVertices.push_back(-size);
	cubeVertices.push_back(-size);
	cubeVertices.push_back(-size);
	cubeNormals.push_back(0.0f);
	cubeNormals.push_back(-1.0f);
	cubeNormals.push_back(0.0f);
	cubeTexCoords.push_back(0.0f);
	cubeTexCoords.push_back(0.0f);

	cubeVertices.push_back(size);
	cubeVertices.push_back(-size);
	cubeVertices.push_back(-size);
	cubeNormals.push_back(0.0f);
	cubeNormals.push_back(-1.0f);
	cubeNormals.push_back(0.0f);
	cubeTexCoords.push_back(1.0f);
	cubeTexCoords.push_back(0.0f);

	cubeVertices.push_back(size);
	cubeVertices.push_back(-size);
	cubeVertices.push_back(size);
	cubeNormals.push_back(0.0f);
	cubeNormals.push_back(-1.0f);
	cubeNormals.push_back(0.0f);
	cubeTexCoords.push_back(1.0f);
	cubeTexCoords.push_back(1.0f);

	// Triangle 2
	cubeVertices.push_back(size);
	cubeVertices.push_back(-size);
	cubeVertices.push_back(size);
	cubeNormals.push_back(0.0f);
	cubeNormals.push_back(-1.0f);
	cubeNormals.push_back(0.0f);
	cubeTexCoords.push_back(1.0f);
	cubeTexCoords.push_back(1.0f);

	cubeVertices.push_back(-size);
	cubeVertices.push_back(-size);
	cubeVertices.push_back(size);
	cubeNormals.push_back(0.0f);
	cubeNormals.push_back(-1.0f);
	cubeNormals.push_back(0.0f);
	cubeTexCoords.push_back(0.0f);
	cubeTexCoords.push_back(1.0f);

	cubeVertices.push_back(-size);
	cubeVertices.push_back(-size);
	cubeVertices.push_back(-size);
	cubeNormals.push_back(0.0f);
	cubeNormals.push_back(-1.0f);
	cubeNormals.push_back(0.0f);
	cubeTexCoords.push_back(0.0f);
	cubeTexCoords.push_back(0.0f);
}

void Cube::Initialize()
{
	// Create the cube data
	CreateCube();

	// Create vertex shader
	vertexShader = new Shader("multi_light_vertex_shader.txt", GL_VERTEX_SHADER, "log.txt");

	// Create fragment shader
	fragmentShader = new Shader("multi_light_fragment_shader.txt", GL_FRAGMENT_SHADER, "log.txt");

	// Create and link shader program
	shaderProgram = new Program(2, vertexShader->GetObject(), fragmentShader->GetObject());

	glBindAttribLocation(shaderProgram->GetObject(), MST_ATTRIBUTES_POSITION, "vPosition");
	glBindAttribLocation(shaderProgram->GetObject(), MST_ATTRIBUTES_COLOR, "vColor");
	glBindAttribLocation(shaderProgram->GetObject(), MST_ATTRIBUTES_TEXCOORD, "vTexCoord");
	glBindAttribLocation(shaderProgram->GetObject(), MST_ATTRIBUTES_NORMAL, "vNormal");

	shaderProgram->LinkProgram("log.txt");

	// Get uniform locations
	modelMatrixUniform = glGetUniformLocation(shaderProgram->GetObject(), "u_modelMatrix");
	viewMatrixUniform = glGetUniformLocation(shaderProgram->GetObject(), "u_viewMatrix");
	projectionMatrixUniform = glGetUniformLocation(shaderProgram->GetObject(), "u_ProjectionMatrix");
	lightKeyPressedUniform = glGetUniformLocation(shaderProgram->GetObject(), "u_lKeyPressed");

	

	InitializeMultiLight(shaderProgram);

	// Create VAO
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Create VBO for position
	glGenBuffers(1, &vbo_position);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_position);
	glBufferData(GL_ARRAY_BUFFER, cubeVertices.size() * sizeof(GLfloat), cubeVertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(MST_ATTRIBUTES_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(MST_ATTRIBUTES_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Create VBO for normals
	glGenBuffers(1, &vbo_normal);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_normal);
	glBufferData(GL_ARRAY_BUFFER, cubeNormals.size() * sizeof(GLfloat), cubeNormals.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(MST_ATTRIBUTES_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(MST_ATTRIBUTES_NORMAL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Create VBO for texture coordinates
	glGenBuffers(1, &vbo_texcoord);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_texcoord);
	glBufferData(GL_ARRAY_BUFFER, cubeTexCoords.size() * sizeof(GLfloat), cubeTexCoords.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(MST_ATTRIBUTES_TEXCOORD, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(MST_ATTRIBUTES_TEXCOORD);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Unbind VAO
	glBindVertexArray(0);

	// Enable depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

void Cube::Display(mat4 &projectionMatrix, mat4 &modelMatrix, mat4 &viewMatrix)
{
	// Use the shader program
	glUseProgram(shaderProgram->GetObject());

	// Set the matrix uniforms
	glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, projectionMatrix);
	glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, viewMatrix);
	glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, modelMatrix);

	// Set lighting uniforms
	if (enableLight)
	{
		glUniform1i(lightKeyPressedUniform, 1);

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

	// Draw cube (36 vertices for a complete cube without indices)
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Unbind VAO and shader
	glBindVertexArray(0);
	glUseProgram(0);
}

void Cube::Resize(int width, int height)
{
	// No specific resize operations needed for the cube
}

void Cube::Uninitialize()
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

void Cube::ToggleLight()
{
	enableLight = !enableLight;
}

void Cube::SetLight(bool enable)
{
	enableLight = enable;
}