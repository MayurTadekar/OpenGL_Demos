/***************************************************************************
 * S.G.M.P
 * @file: SingleLightProgram.h
 * @brief:
 * @author: Mayur S. Tadekar(mrtadekar@gmail.com)
 * @copyright ©2020-2025 MarshallingVoid
 * @date: Saturday 2026-06-06 10:26:28 AM
 ***************************************************************************/

#pragma once

#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/vmath/vmath.h>
#include "../Common/Shader.h"
#include "../Common/Program.h"
// #include "macros.h"

#include "../../../include/common.h"
#include "../../../modules/Texture/Texture.h"

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
	GLuint baseImageTextureU;
	GLuint normalMapU;

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
	GLuint normalMap;

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
		baseImageTextureU = glGetUniformLocation(shaderProgram->GetObject(), "baseImageTexture");
		normalMapU = glGetUniformLocation(shaderProgram->GetObject(), "normalMap");
	}

	SingleLightProgram() = delete; // Prevent default constructor

public:
	SingleLightProgram(const char *vertexShaderPath, const char *fragmentShaderPath, const char *logFilePath, const char *normalMapPath)
	{
		// Code
		normalMap = 0;

		vertexShader = new Shader(vertexShaderPath, GL_VERTEX_SHADER, logFilePath);
		fragmentShader = new Shader(fragmentShaderPath, GL_FRAGMENT_SHADER, logFilePath);

		shaderProgram = new Program(2, vertexShader->GetObject(), fragmentShader->GetObject());

		glBindAttribLocation(shaderProgram->GetObject(), AMC_ATTRIBUTE_POSITION, "vPosition");
		// glBindAttribLocation(shaderProgram->GetObject(), MST_ATTRIBUTES_COLOR, "vColor");
		glBindAttribLocation(shaderProgram->GetObject(), AMC_ATTRIBUTE_TEXCOORD, "vTexCoord");
		glBindAttribLocation(shaderProgram->GetObject(), AMC_ATTRIBUTE_NORMAL, "vNormal");
		glBindAttribLocation(shaderProgram->GetObject(), AMC_ATTRIBUTE_TANGENT, "vTangent");

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

		light_position[0] = -5000.0f;
		light_position[1] = 0.0f;
		light_position[2] = 5000.0f;
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

		if (!LoadTextureFromFile(normalMapPath, &normalMap))
		{
			LOG_ENTRY_WITH_PARAM("log.txt", "%s: Successfully Loaded", normalMapPath);
		}
		else
		{
			LOG_ENTRY_WITH_PARAM("log.txt", "%s: Loading Failed", normalMapPath);
		}
	}

	~SingleLightProgram()
	{
		delete vertexShader;
		delete fragmentShader;
		delete shaderProgram;
	}

	void SetLightPosition(vec3 lightPos)
	{
		// Code
		light_position[0] = lightPos[0];
		light_position[1] = lightPos[1];
		light_position[2] = lightPos[2];
		light_position[3] = 1.0;
	}

	void SetLights()
	{

		// static float angle = 0.0f;
		// angle += 0.02f; // Increment angle for rotation

		// // Rotate the Light 01 around the Y-axis
		// light_position[0] = 1000.0f * cos(angle);
		// light_position[1] = 2000.0f; // Keep the height constant
		// light_position[2] = 1000.0f * sin(angle);
		// light_position[3] = 1.0f; // Homogeneous coordinate

		// Set light properties
		glUniform4fv(lightPosition1Uniform, 1, light_position);
		glUniform3fv(laUniform, 1, light_ambient);
		glUniform3fv(ldUniform, 1, light_diffuse);
		glUniform3fv(lsUniform, 1, light_specular);
	}

	void SetMaterialProperties()
	{
		glUniform3fv(kaUniform, 1, material_ambient);
		glUniform3fv(kdUniform, 1, material_diffuse);
		glUniform3fv(ksUniform, 1, material_specular);
		glUniform1f(materialShininessUniform, material_shininess);
	}

	void SetUniforms(vmath::mat4 &projectionMatrix, vmath::mat4 &modelMatrix, vmath::mat4 &viewMatrix, GLuint baseImageTexture)
	{
		// Code

		// Set light properties
		SetLights();

		SetMaterialProperties();

		// Set the matrix uniforms
		glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, projectionMatrix);
		glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, viewMatrix);
		glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, modelMatrix);
		glUniform1i(baseImageTextureU, baseImageTexture);
		glUniform1i(normalMapU, 1);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, normalMap);
	}

	void StartProgram()
	{
		// Code
		glUseProgram(shaderProgram->GetObject());
	}

	void StopProgram()
	{
		// Code

		glBindTexture(GL_TEXTURE_2D, 0);

		glUseProgram(0);
	}
};