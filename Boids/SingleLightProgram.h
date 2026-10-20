/***************************************************************************
 * S.G.M.P
 * @file: SingleLightProgram.h
 * @brief:
 * @author: Mayur S. Tadekar(mrtadekar@gmail.com)
 * @copyright ©2020-2025 MarshallingVoid
 * @date: Wednesday 2025-06-18 5:54:23 PM
 ***************************************************************************/

#pragma once

#include <GL/glew.h>
#include <GL/GL.h>

#include "Shader.h"
#include "macros.h"
#include "Program.h"

class SingleLightProgram
{

private:
	Shader *vertexShader;
	Shader *fragmentShader;
	Program *shaderProgram;

	GLuint lightPosition1Uniform;
	GLuint laUniform;
	GLuint ldUniform;
	GLuint lsUniform;

	GLuint modelMatrixUniform;
	GLuint viewMatrixUniform;
	GLuint projectionMatrixUniform;
	GLuint lightKeyPressedUniform;

	// Define light properties
	GLfloat light_ambient[3]; // Red light
	GLfloat light_diffuse[3];
	GLfloat light_specular[3];
	GLfloat light_position[4];

	GLfloat material_ambient[3];
	GLfloat material_diffuse[3];
	GLfloat material_specular[3];
	GLfloat material_shininess;

	// Material uniforms
	GLuint kaUniform; // Material ambient
	GLuint kdUniform; // Material diffuse
	GLuint ksUniform; // Material specular
	GLuint materialShininessUniform;

	void InitializeSingleLight(Program *shaderProgram)
	{
		// Get uniform locations for the lights
		// Red light
		lightPosition1Uniform = glGetUniformLocation(shaderProgram->GetObject(), "u_LightPosition");
		laUniform = glGetUniformLocation(shaderProgram->GetObject(), "u_la");
		ldUniform = glGetUniformLocation(shaderProgram->GetObject(), "u_ld");
		lsUniform = glGetUniformLocation(shaderProgram->GetObject(), "u_ls");

		kaUniform = glGetUniformLocation(shaderProgram->GetObject(), "u_ka");
		kdUniform = glGetUniformLocation(shaderProgram->GetObject(), "u_kd");
		ksUniform = glGetUniformLocation(shaderProgram->GetObject(), "u_ks");
		materialShininessUniform = glGetUniformLocation(shaderProgram->GetObject(), "u_kshiny");

		modelMatrixUniform = glGetUniformLocation(shaderProgram->GetObject(), "u_modelMatrix");
		viewMatrixUniform = glGetUniformLocation(shaderProgram->GetObject(), "u_viewMatrix");
		projectionMatrixUniform = glGetUniformLocation(shaderProgram->GetObject(), "u_ProjectionMatrix");
		lightKeyPressedUniform = glGetUniformLocation(shaderProgram->GetObject(), "u_lKeyPressed");
	}

	SingleLightProgram() = delete; // Prevent default constructor

public:
	SingleLightProgram(const char *vertexShaderPath, const char *fragmentShaderPath, const char *logFilePath)
	{
		vertexShader = new Shader(vertexShaderPath, GL_VERTEX_SHADER, logFilePath);
		fragmentShader = new Shader(fragmentShaderPath, GL_FRAGMENT_SHADER, logFilePath);

		shaderProgram = new Program(2, vertexShader->GetObject(), fragmentShader->GetObject());

		glBindAttribLocation(shaderProgram->GetObject(), MST_ATTRIBUTES_POSITION, "vPosition");
		glBindAttribLocation(shaderProgram->GetObject(), MST_ATTRIBUTES_COLOR, "vColor");
		glBindAttribLocation(shaderProgram->GetObject(), MST_ATTRIBUTES_TEXCOORD, "vTexCoord");
		glBindAttribLocation(shaderProgram->GetObject(), MST_ATTRIBUTES_NORMAL, "vNormal");

		shaderProgram->LinkProgram(logFilePath);

		InitializeSingleLight(shaderProgram);

		// Red light
		light_ambient[0] = 0.1f;
		light_ambient[1] = 0.1f;
		light_ambient[2] = 0.1f;

		light_diffuse[0] = 1.0f;
		light_diffuse[1] = 1.0f;
		light_diffuse[2] = 1.0f;

		light_specular[0] = 1.0f;
		light_specular[1] = 1.0f;
		light_specular[2] = 1.0f;

		light_position[0] = 5.0f;
		light_position[1] = 10.0f;
		light_position[2] = 5.0f;
		light_position[3] = 1.0f;

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

	~SingleLightProgram()
	{
		delete vertexShader;
		delete fragmentShader;
		delete shaderProgram;
	}

	void SetLights()
	{

		static float angle = 0.0f;
		angle += 0.002f; // Increment angle for rotation

		// Rotate the Light 01 around the Y-axis
		light_position[0] = 5.0f * cos(angle);
		light_position[1] = 0.0f; // Keep the height constant
		light_position[2] = 5.0f * sin(angle);
		light_position[3] = 1.0f; // Homogeneous coordinate

		// Set light properties
		glUniform4fv(lightPosition1Uniform, 1, light_position);
		glUniform3fv(laUniform, 1, light_ambient);
		glUniform3fv(ldUniform, 1, light_diffuse);
		glUniform3fv(lsUniform, 1, light_specular);

		glUniform1i(lightKeyPressedUniform, 1);
	}

	void SetMaterialProperties()
	{
		glUniform3fv(kaUniform, 1, material_ambient);
		glUniform3fv(kdUniform, 1, material_diffuse);
		glUniform3fv(ksUniform, 1, material_specular);
		glUniform1f(materialShininessUniform, material_shininess);
	}
};