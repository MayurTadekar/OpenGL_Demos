/***************************************************************************
 * S.G.M.P
 * @file: triangle.h
 * @brief: Implementation of a triangle class for OpenGL rendering
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

class Triangle
{
public:
	Triangle();
	~Triangle();

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
	GLuint vbo_normal;
	GLuint vbo_texcoord;

	bool enableLight;

	float x_pos;
	float y_pos;
	bool enableGrayscale;
};
