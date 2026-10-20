/***************************************************************************
 * S.G.M.P
 * @file: Fire.h
 * @brief: Implementation of a Fire class for OpenGL rendering
 * @author: Mayur S. Tadekar(mrtadekar@gmail.com)
 * @copyright ©2020-2025 MarshallingVoid
 * @date: Monday 2025-06-16 0:29:23 AM
 ***************************************************************************/

#pragma once

#include <GL/glew.h>
#include <GL/GL.h>
#include "./../../../include/vmath.h"
#include "../Common/Shader.h"
#include "../Common/Program.h"
#include "../Common/macros.h"

using namespace vmath;

// External elapsed time variable (set by main program)
extern float ELAPSED_TIME;

class Fire
{
public:
	Fire();
	~Fire();

	void Initialize();
	void Display(mat4 &projectionMatrix, mat4 &modelMatrix, mat4 &viewMatrix);
	void Resize(int width, int height);
	void Uninitialize();
	void ToggleGrayscale();
	void SetGrayscale(bool enable);

	void IncreaseFireSize() { fireSize += 0.1f; }
	void DecreaseFireSize() { fireSize -= 0.1f; }

	void SetWindowsSize(int width, int height)
	{
		winWidth = width;
		winHeight = height;
	}

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

	float fireSize;
	GLuint uFireSize;

	GLuint resUniform;
	GLuint timeUniform;

	Shader *vertexShader;
	Shader *fragmentShader;
	Program *shaderProgram;

	bool enableLight;

	float x_pos;
	float y_pos;
	bool enableGrayscale;

	int winWidth;
	int winHeight;
};

Fire::Fire()
	: vao(0), vbo_position(0), vbo_color(0),
	  vbo_normal(0), vbo_texcoord(0),
	  modelMatrixUniform(0), viewMatrixUniform(0), projectionMatrixUniform(0),
	  lightKeyPressedUniform(0), enableLight(true), enableGrayscale(false),
	  vertexShader(nullptr), fragmentShader(nullptr), shaderProgram(nullptr),
	  x_pos(0.0f), y_pos(0.0f)
{
}

Fire::~Fire()
{
	Uninitialize();
}

void Fire::Initialize()
{

	fireSize = 3.0;

	// Vertex data for the Fire
	const GLfloat FireVertices[] = {
		-10.0f, 10.0f, 0.0f,  // Top
		-10.0f, -10.0f, 0.0f, // Left
		10.0f, -10.0f, 0.0f,  // Right

		-10.0f, 10.0f, 0.0f, // Top
		10.0f, 10.0f, 0.0f,	 // Left
		10.0f, -10.0f, 0.0f	 // Right
	};

	// Color data for the Fire
	const GLfloat FireColors[] = {
		1.0f,
		1.0f,
		1.0f, // Red (for top vertex)
		1.0f,
		1.0f,
		1.0f, // Green (for left vertex)
		1.0f,
		1.0f,
		1.0f, // Blue (for right vertex)

		1.0f,
		1.0f,
		1.0f, // Red (for top vertex)
		1.0f,
		1.0f,
		1.0f, // Green (for left vertex)
		1.0f,
		1.0f,
		1.0f // Blue (for right vertex)
	};

	const GLfloat FireTexCoords[] = {
		0.5f, 1.0f, // Top vertex texture coordinate
		0.0f, 0.0f, // Left vertex texture coordinate
		1.0f, 0.0f, // Right vertex texture coordinate
		0.5f, 1.0f, // Top vertex texture coordinate
		0.0f, 0.0f, // Left vertex texture coordinate
		1.0f, 0.0f	// Right vertex texture coordinate
	};

	const GLfloat FireNormals[] = {
		0.0f, 0.0f, 1.0f, // Normal for all vertices (pointing out of the screen)
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, // Normal for all vertices (pointing out of the screen)
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f};

	// Create vertex shader
	vertexShader = new Shader("./effects/MayursEffects/Fire/fire_vertex_shader.glsl", GL_VERTEX_SHADER, "log.txt");

	// Create fragment shader
	fragmentShader = new Shader("./effects/MayursEffects/Fire/fire_fragment_shader.glsl", GL_FRAGMENT_SHADER, "log.txt");

	// LOG_ENTRY_WITH_PARAM("log.txt", "Vertex Shader Object: %u", vertexShader->GetObject());
	// LOG_ENTRY_WITH_PARAM("log.txt", "Fragment Shader Object: %u", fragmentShader->GetObject());

	// Create shader program
	shaderProgram = new Program(2, vertexShader->GetObject(), fragmentShader->GetObject());
	glBindAttribLocation(shaderProgram->GetObject(), MST_ATTRIBUTES_POSITION, "vPosition");
	glBindAttribLocation(shaderProgram->GetObject(), MST_ATTRIBUTES_COLOR, "vColor");
	glBindAttribLocation(shaderProgram->GetObject(), MST_ATTRIBUTES_TEXCOORD, "vTexCoord");
	glBindAttribLocation(shaderProgram->GetObject(), MST_ATTRIBUTES_NORMAL, "vNormal");
	shaderProgram->LinkProgram("log.txt");

	// Get uniform locations
	modelMatrixUniform = glGetUniformLocation(shaderProgram->GetObject(), "u_mMatrix");
	viewMatrixUniform = glGetUniformLocation(shaderProgram->GetObject(), "u_vMatrix");
	projectionMatrixUniform = glGetUniformLocation(shaderProgram->GetObject(), "u_pMatrix");
	lightKeyPressedUniform = glGetUniformLocation(shaderProgram->GetObject(), "u_lKeyPressed");
	resUniform = glGetUniformLocation(shaderProgram->GetObject(), "iResolution");
	timeUniform = glGetUniformLocation(shaderProgram->GetObject(), "iTime");
	uFireSize = glGetUniformLocation(shaderProgram->GetObject(), "fireSize");

	// Create VAO
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	{
		// Create VBO for position
		glGenBuffers(1, &vbo_position);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_position);
		glBufferData(GL_ARRAY_BUFFER, sizeof(FireVertices), FireVertices, GL_STATIC_DRAW);
		glVertexAttribPointer(MST_ATTRIBUTES_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(MST_ATTRIBUTES_POSITION);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Create VBO for texture coordinates
		glGenBuffers(1, &vbo_texcoord);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_texcoord);
		glBufferData(GL_ARRAY_BUFFER, sizeof(FireTexCoords), FireTexCoords, GL_STATIC_DRAW);
		glVertexAttribPointer(MST_ATTRIBUTES_TEXCOORD, 2, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(MST_ATTRIBUTES_TEXCOORD);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Create VBO for normals (not used in this Fire, but included for completeness)
		glGenBuffers(1, &vbo_normal);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_normal);
		glBufferData(GL_ARRAY_BUFFER, sizeof(FireNormals), FireNormals, GL_STATIC_DRAW);
		glVertexAttribPointer(MST_ATTRIBUTES_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(MST_ATTRIBUTES_NORMAL);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Create VBO for color
		glGenBuffers(1, &vbo_color);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_color);
		glBufferData(GL_ARRAY_BUFFER, sizeof(FireColors), FireColors, GL_STATIC_DRAW);
		glVertexAttribPointer(MST_ATTRIBUTES_COLOR, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(MST_ATTRIBUTES_COLOR);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	// Unbind VAO
	glBindVertexArray(0);

	// Set clear color
	// glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Fire::Display(mat4 &projectionMatrix, mat4 &modelMatrix, mat4 &viewMatrix)
{
	// Use the shader program

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glUseProgram(shaderProgram->GetObject());

	// Set the matrix uniforms for transformation
	glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, projectionMatrix);
	glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, viewMatrix);
	glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, modelMatrix);

	glUniform2f(resUniform, (GLfloat)winWidth, (GLfloat)winHeight);
	glUniform1f(timeUniform, ELAPSED_TIME); // Use actual elapsed time from program start

	glUniform1f(uFireSize, fireSize);

	static GLfloat angle = 0.0f;
	angle += 0.005f; // Increment angle for rotation

	// Bind VAO
	glBindVertexArray(vao);

	// Draw the Fire
	glDrawArrays(GL_TRIANGLES, 0, 6);

	// Unbind VAO
	glBindVertexArray(0);

	// Unuse the shader program
	glUseProgram(0);

	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
}

void Fire::Resize(int width, int height)
{
	// Adjust the viewport and projection matrix based on the new window size.
	if (height < 1)
		height = 1;

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	// perspectiveProjectionMatrix = perspective(45.0f, (float)width / (float)height, 0.1f, 100.0f);
}

void Fire::Uninitialize()
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

	// The shader program is managed by the Program class, which handles cleanup in its destructor

	glUseProgram(0);
}

void Fire::ToggleGrayscale()
{
	enableGrayscale = !enableGrayscale;
}

void Fire::SetGrayscale(bool enable)
{
	enableGrayscale = enable;
}
