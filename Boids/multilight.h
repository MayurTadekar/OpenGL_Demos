/***************************************************************************
 * S.G.M.P
 * @file: multilight.h
 * @brief:
 * @author: Mayur S. Tadekar(mrtadekar@gmail.com)
 * @copyright ©2020-2025 MarshallingVoid
 * @date: Wednesday 2025-06-18 2:19:17 PM
 ***************************************************************************/

#pragma once

#include <GL/glew.h>
#include <GL/GL.h>

#include "Shader.h"
#include "Program.h"
#include "macros.h"

class MultiLight
{
private:
	// In class declaration, add:
	// Red light
	GLuint lightPosition1Uniform;
	GLuint la1Uniform;
	GLuint ld1Uniform;
	GLuint ls1Uniform;

	// Green light
	GLuint lightPosition2Uniform;
	GLuint la2Uniform;
	GLuint ld2Uniform;
	GLuint ls2Uniform;

	// Blue light
	GLuint lightPosition3Uniform;
	GLuint la3Uniform;
	GLuint ld3Uniform;
	GLuint ls3Uniform;

	// Define light properties
	GLfloat light1_ambient[3]; // Red light
	GLfloat light1_diffuse[3];
	GLfloat light1_specular[3];
	GLfloat light1_position[4];

	GLfloat light2_ambient[3]; // Green light
	GLfloat light2_diffuse[3];
	GLfloat light2_specular[3];
	GLfloat light2_position[4];

	GLfloat light3_ambient[3]; // Blue light
	GLfloat light3_diffuse[3];
	GLfloat light3_specular[3];
	GLfloat light3_position[4];

	GLfloat material_ambient[3];
	GLfloat material_diffuse[3];
	GLfloat material_specular[3];
	GLfloat material_shininess;

	// Material uniforms
	GLuint kaUniform; // Material ambient
	GLuint kdUniform; // Material diffuse
	GLuint ksUniform; // Material specular
	GLuint materialShininessUniform;

public:
	MultiLight()
	{
		// Red light
		light1_ambient[0] = 0.1f;
		light1_ambient[1] = 0.0f;
		light1_ambient[2] = 0.0f;
		light1_diffuse[0] = 1.0f;
		light1_diffuse[1] = 0.0f;
		light1_diffuse[2] = 0.0f;
		light1_specular[0] = 1.0f;
		light1_specular[1] = 0.0f;
		light1_specular[2] = 0.0f;
		light1_position[0] = 5.0f;
		light1_position[1] = 10.0f;
		light1_position[2] = 5.0f;
		light1_position[3] = 1.0f;

		// Green light
		light2_ambient[0] = 0.0f;
		light2_ambient[1] = 0.1f;
		light2_ambient[2] = 0.0f;
		light2_diffuse[0] = 0.0f;
		light2_diffuse[1] = 1.0f;
		light2_diffuse[2] = 0.0f;
		light2_specular[0] = 0.0f;
		light2_specular[1] = 1.0f;
		light2_specular[2] = 0.0f;
		light2_position[0] = -5.0f;
		light2_position[1] = 5.0f;
		light2_position[2] = 5.0f;
		light2_position[3] = 1.0f;

		// Blue light
		light3_ambient[0] = 0.0f;
		light3_ambient[1] = 0.0f;
		light3_ambient[2] = 0.1f;
		light3_diffuse[0] = 0.0f;
		light3_diffuse[1] = 0.0f;
		light3_diffuse[2] = 1.0f;
		light3_specular[0] = 0.0f;
		light3_specular[1] = 0.0f;
		light3_specular[2] = 1.0f;
		light3_position[0] = 0.0f;
		light3_position[1] = -5.0f;
		light3_position[2] = 5.0f;
		light3_position[3] = 1.0f;

		// Material properties
		material_ambient[0] = 0.2f;
		material_ambient[1] = 0.2f;
		material_ambient[2] = 0.2f;

		material_diffuse[0] = 1.0f;
		material_diffuse[1] = 1.0f;
		material_diffuse[2] = 1.0f;

		material_specular[0] = 1.0f;
		material_specular[1] = 1.0f;
		material_specular[2] = 1.0f;
		material_shininess = 120.0f;
	}

	~MultiLight() = default;

	void InitializeMultiLight(Program *shaderProgram)
	{
		// Get uniform locations for the lights
		// Red light
		lightPosition1Uniform = glGetUniformLocation(shaderProgram->GetObject(), "u_LightPosition1");
		la1Uniform = glGetUniformLocation(shaderProgram->GetObject(), "u_la1");
		ld1Uniform = glGetUniformLocation(shaderProgram->GetObject(), "u_ld1");
		ls1Uniform = glGetUniformLocation(shaderProgram->GetObject(), "u_ls1");

		// Green light
		lightPosition2Uniform = glGetUniformLocation(shaderProgram->GetObject(), "u_LightPosition2");
		la2Uniform = glGetUniformLocation(shaderProgram->GetObject(), "u_la2");
		ld2Uniform = glGetUniformLocation(shaderProgram->GetObject(), "u_ld2");
		ls2Uniform = glGetUniformLocation(shaderProgram->GetObject(), "u_ls2");

		// Blue light
		lightPosition3Uniform = glGetUniformLocation(shaderProgram->GetObject(), "u_LightPosition3");
		la3Uniform = glGetUniformLocation(shaderProgram->GetObject(), "u_la3");
		ld3Uniform = glGetUniformLocation(shaderProgram->GetObject(), "u_ld3");
		ls3Uniform = glGetUniformLocation(shaderProgram->GetObject(), "u_ls3");

		kaUniform = glGetUniformLocation(shaderProgram->GetObject(), "u_ka");
		kdUniform = glGetUniformLocation(shaderProgram->GetObject(), "u_kd");
		ksUniform = glGetUniformLocation(shaderProgram->GetObject(), "u_ks");
		materialShininessUniform = glGetUniformLocation(shaderProgram->GetObject(), "u_kshiny");
	}

	void SetLights()
	{

		static float angle = 0.0f;
		// angle += 0.005f; // Increment angle for rotation

		// Rotate the Light 01 around the Y-axis
		light1_position[0] = 5.0f * cos(angle);
		light1_position[1] = 0.0f; // Keep the height constant
		light1_position[2] = 5.0f * sin(angle);
		light1_position[3] = 1.0f; // Homogeneous coordinate

		// Rotate the Light 02 around the Z-axis
		light2_position[0] = -5.0f * sin(angle);
		light2_position[1] = 5.0f * cos(angle);
		light2_position[2] = 0.0f;
		light2_position[3] = 1.0f; // Homogeneous coordinate

		// Rotate the Light 03 around the X-axis
		light3_position[0] = 0.0f;
		light3_position[1] = -5.0f * sin(angle);
		light3_position[2] = 5.0f * cos(angle);
		light3_position[3] = 1.0f; // Homogeneous coordinate
		

		// Set Red light properties
		glUniform4fv(lightPosition1Uniform, 1, light1_position);
		glUniform3fv(la1Uniform, 1, light1_ambient);
		glUniform3fv(ld1Uniform, 1, light1_diffuse);
		glUniform3fv(ls1Uniform, 1, light1_specular);

		// Set Green light properties
		glUniform4fv(lightPosition2Uniform, 1, light2_position);
		glUniform3fv(la2Uniform, 1, light2_ambient);
		glUniform3fv(ld2Uniform, 1, light2_diffuse);
		glUniform3fv(ls2Uniform, 1, light2_specular);

		// Set Blue light properties
		glUniform4fv(lightPosition3Uniform, 1, light3_position);
		glUniform3fv(la3Uniform, 1, light3_ambient);
		glUniform3fv(ld3Uniform, 1, light3_diffuse);
		glUniform3fv(ls3Uniform, 1, light3_specular);
	}

	void SetMaterialProperties()
	{
		glUniform3fv(kaUniform, 1, material_ambient);
		glUniform3fv(kdUniform, 1, material_diffuse);
		glUniform3fv(ksUniform, 1, material_specular);
		glUniform1f(materialShininessUniform, material_shininess);
	}
};
