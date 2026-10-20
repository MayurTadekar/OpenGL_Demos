/***************************************************************************
 * S.G.M.P
 * @file: ModelRenderingProgram.h
 * @brief:
 * @author: Mayur S. Tadekar(mrtadekar@gmail.com)
 * @date: Saturday 2026-08-15 10:03:01 PM
 ***************************************************************************/

#pragma once

#include <GL/glew.h>
#include <GL/GL.h>
#include <glm/glm.hpp>
#include "Shader.h"
#include "Program.h"
#include "macros.h"
#include "common.h"

class ModelRenderingProgram
{
private:
	Shader *vertexShader;
	Shader *fragmentShader;
	Program *shaderProgram;

	// Shader uniforms
	GLuint modelMatrixUniform;
	GLuint viewMatrixUniform;
	GLuint projectionMatrixUniform;

	GLuint viewPosUniform;
	GLuint lightPosUniform;
	GLuint lightColorUniform;

	GLuint shaderStorageBufferObject;

	typedef struct ModelInstance
	{
		glm::mat4 mMatrix;			   // Model matrix for this instance
		glm::mat4 mMatrixInvTranspose; // Inverse transpose of model matrix for normals
	} ModelInstance;

public:
	ModelRenderingProgram()
		: vertexShader(nullptr), fragmentShader(nullptr), shaderProgram(nullptr),
		  modelMatrixUniform(0), viewMatrixUniform(0), projectionMatrixUniform(0)
	{
	}

	~ModelRenderingProgram() = default;

	ModelRenderingProgram(const char *vertexShaderPath, const char *fragmentShaderPath, const char *logFilePath)
	{
		// Create vertex shader
		vertexShader = new Shader(vertexShaderPath, GL_VERTEX_SHADER, logFilePath);

		LOG_ENTRY("log.txt", "Vertex Shader Created");

		// Create fragment shader
		fragmentShader = new Shader(fragmentShaderPath, GL_FRAGMENT_SHADER, logFilePath);

		LOG_ENTRY("log.txt", "Fragment Shader Created");

		// Create and link shader program
		shaderProgram = new Program(2, vertexShader->GetObject(), fragmentShader->GetObject());
		glBindAttribLocation(shaderProgram->GetObject(), MST_ATTRIBUTES_POSITION, "vPosition");
		// glBindAttribLocation(shaderProgram->GetObject(), MST_ATTRIBUTES_COLOR, "vColor");
		// glBindAttribLocation(shaderProgram->GetObject(), MST_ATTRIBUTES_TEXCOORD, "vTexCoord");
		// glBindAttribLocation(shaderProgram->GetObject(), MST_ATTRIBUTES_NORMAL, "vNormal");
		shaderProgram->LinkProgram(logFilePath);

		// Get uniform locations
		// modelMatrixUniform = glGetUniformLocation(shaderProgram->GetObject(), "u_mMatrix");
		viewMatrixUniform = glGetUniformLocation(shaderProgram->GetObject(), "u_vMatrix");
		projectionMatrixUniform = glGetUniformLocation(shaderProgram->GetObject(), "u_pMatrix");

		viewPosUniform = glGetUniformLocation(shaderProgram->GetObject(), "u_viewPos");
		lightPosUniform = glGetUniformLocation(shaderProgram->GetObject(), "u_lightPos");
		lightColorUniform = glGetUniformLocation(shaderProgram->GetObject(), "u_lightColor");

		LOG_ENTRY("log.txt", "ModelRenderingProgram Initialized");

		glGenBuffers(1, &shaderStorageBufferObject);
	}

	void SetLights()
	{
	}

	void SetMaterialProperties()
	{
	}

	void SetModelMatricesForInstances(std::vector<glm::mat4> &modelMatrices)
	{
		std::vector<ModelInstance> modelInstanceMatrices(modelMatrices.size());

		for (size_t i = 0; i < modelMatrices.size(); ++i)
		{
			modelInstanceMatrices[i].mMatrix = modelMatrices[i];
			modelInstanceMatrices[i].mMatrixInvTranspose = glm::transpose(glm::inverse(modelMatrices[i]));
		}

		// Bind the shader storage buffer object
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, shaderStorageBufferObject);
		glBufferData(GL_SHADER_STORAGE_BUFFER, modelInstanceMatrices.size() * sizeof(ModelInstance), modelInstanceMatrices.data(), GL_DYNAMIC_DRAW);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, shaderStorageBufferObject);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
	}

	void SetUniforms(glm::mat4 &projectionMatrix, glm::mat4 &viewMatrix,
					 const glm::vec3 &viewPos = glm::vec3(0.0f, 2.0f, 5.0f),
					 const glm::vec3 &lightPos = glm::vec3(5.0f, 5.0f, 5.0f),
					 const glm::vec3 &lightColor = glm::vec3(1.0f, 1.0f, 1.0f))
	{
		// Set the matrix uniforms
		glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, &projectionMatrix[0][0]);
		glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, &viewMatrix[0][0]);
		// glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, &modelMatrix[0][0]);

		// Set lighting uniforms
		glUniform3f(viewPosUniform, viewPos[0], viewPos[1], viewPos[2]);
		glUniform3f(lightPosUniform, lightPos[0], lightPos[1], lightPos[2]);
		glUniform3f(lightColorUniform, lightColor[0], lightColor[1], lightColor[2]);
	}

	void StartProgram()
	{
		glUseProgram(shaderProgram->GetObject());
	}

	void StopProgram()
	{
		glUseProgram(0);
	}

	GLuint GetProgramID() const
	{
		return shaderProgram->GetObject();
	}

	void Uninitialize()
	{
		// Code
		if (fragmentShader)
		{
			delete fragmentShader;
			fragmentShader = nullptr;
		}

		if (vertexShader)
		{
			delete vertexShader;
			vertexShader = nullptr;
		}

		if (shaderProgram)
		{
			delete shaderProgram;
			shaderProgram = nullptr;
		}
	}
};
