/***************************************************************************
 * S.G.M.P
 * @file: CloudsProgram.h
 * @brief:
 * @author: Mayur S. Tadekar(mrtadekar@gmail.com)
 * @copyright ©2020-2025 MarshallingVoid
 * @date: Wednesday 2025-06-18 2:19:17 PM
 ***************************************************************************/

#pragma once

#include <GL/glew.h>
#include <GL/GL.h>
#include "./../../../include/vmath.h"
#include "../Common/Shader.h"
#include "../Common/Program.h"
#include "../Common/macros.h"

class CloudsProgram
{
private:
	Shader *vertexShader;
	Shader *fragmentShader;
	Program *shaderProgram;

	// Shader uniforms
	GLuint modelMatrixUniform;
	GLuint viewMatrixUniform;
	GLuint projectionMatrixUniform;

	GLuint mainTextureUniform;
	GLuint depthTextureUniform;
	GLuint basicCloudUniform;
	GLuint detailCloudUniform;
	GLuint densityMultiplierUniform;
	GLuint densityOffsetUniform;
	GLuint cloudScaleUniform;

	GLuint detailOffsetU;
	GLuint detailNoiseScaleU;
	GLuint detailNoiseWeightU;
	GLuint detailNoiseWeightsU;

	GLuint camposU;
	GLuint viewVecU;
	GLuint invProU;
	GLuint invViewU;
	GLuint fTimeU;
	GLuint timeScaleU;
	GLuint boundsMinU;
	GLuint boundsMaxU;

	GLuint shapeNoiseWeightsU;

	GLuint numStepsLightU;
	GLuint lightAbsorptionThroughCloudU;
	GLuint lightAbsorptionTowardSunU;
	GLuint darknessThresholdU;
	GLuint phaseParamsU;

	GLuint bottomFadeStartU;
	GLuint bottomFadeEndU;

	GLuint topFadeStartU;
	GLuint topFadeEndU;

	GLuint lightPosU;
	GLuint lightColU;

	GLuint cloudOffsetU;

public:
	CloudsProgram()
		: vertexShader(nullptr), fragmentShader(nullptr), shaderProgram(nullptr),
		  modelMatrixUniform(0), viewMatrixUniform(0), projectionMatrixUniform(0)
	{
	}

	~CloudsProgram() = default;

	void Initialize()
	{
		// Create vertex shader
		vertexShader = new Shader("./effects/MayursEffects/VolumetricClouds/clouds_vs.glsl", GL_VERTEX_SHADER, "log.txt");

		// Create fragment shader
		fragmentShader = new Shader("./effects/MayursEffects/VolumetricClouds/clouds_fs.glsl", GL_FRAGMENT_SHADER, "log.txt");

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

		camposU = glGetUniformLocation(shaderProgram->GetObject(), "cameraPos");
		// viewVecU = glGetUniformLocation(shaderProgram->GetObject(), "viewVec");
		// invProU = glGetUniformLocation(shaderProgram->GetObject(), "invProjection");
		// invViewU = glGetUniformLocation(shaderProgram->GetObject(), "invView");
		fTimeU = glGetUniformLocation(shaderProgram->GetObject(), "fTime");
		timeScaleU = glGetUniformLocation(shaderProgram->GetObject(), "timeScale");

		boundsMinU = glGetUniformLocation(shaderProgram->GetObject(), "boundsMin");
		boundsMaxU = glGetUniformLocation(shaderProgram->GetObject(), "boundsMax");

		mainTextureUniform = glGetUniformLocation(shaderProgram->GetObject(), "mainTexture");
		depthTextureUniform = glGetUniformLocation(shaderProgram->GetObject(), "depthTexture");
		basicCloudUniform = glGetUniformLocation(shaderProgram->GetObject(), "basicCloud");
		detailCloudUniform = glGetUniformLocation(shaderProgram->GetObject(), "detailCloud");
		densityMultiplierUniform = glGetUniformLocation(shaderProgram->GetObject(), "densityMultiplier");
		densityOffsetUniform = glGetUniformLocation(shaderProgram->GetObject(), "densityOffset");

		cloudScaleUniform = glGetUniformLocation(shaderProgram->GetObject(), "cloudScale");

		shapeNoiseWeightsU = glGetUniformLocation(shaderProgram->GetObject(), "shapeNoiseWeights");

		detailOffsetU = glGetUniformLocation(shaderProgram->GetObject(), "detailOffset");
		detailNoiseScaleU = glGetUniformLocation(shaderProgram->GetObject(), "detailNoiseScale");
		detailNoiseWeightU = glGetUniformLocation(shaderProgram->GetObject(), "detailNoiseWeight");
		detailNoiseWeightsU = glGetUniformLocation(shaderProgram->GetObject(), "detailNoiseWeights");

		numStepsLightU = glGetUniformLocation(shaderProgram->GetObject(), "numStepsLight");
		lightAbsorptionThroughCloudU = glGetUniformLocation(shaderProgram->GetObject(), "lightAbsorptionThroughCloud");
		lightAbsorptionTowardSunU = glGetUniformLocation(shaderProgram->GetObject(), "lightAbsorptionTowardSun");

		darknessThresholdU = glGetUniformLocation(shaderProgram->GetObject(), "darknessThreshold");

		topFadeStartU = glGetUniformLocation(shaderProgram->GetObject(), "topFadeStart");
		topFadeEndU = glGetUniformLocation(shaderProgram->GetObject(), "topFadeEnd");

		bottomFadeStartU = glGetUniformLocation(shaderProgram->GetObject(), "bottomFadeStart");
		bottomFadeEndU = glGetUniformLocation(shaderProgram->GetObject(), "bottomFadeEnd");

		lightPosU = glGetUniformLocation(shaderProgram->GetObject(), "lightPos");
		lightColU = glGetUniformLocation(shaderProgram->GetObject(), "lightColor");

		cloudOffsetU = glGetUniformLocation(shaderProgram->GetObject(), "cloudOffset");

		phaseParamsU = glGetUniformLocation(shaderProgram->GetObject(), "phaseParams");
	}

	void SetUniforms(vmath::mat4 &projectionMatrix,
					 vmath::mat4 &modelMatrix,
					 vmath::mat4 &viewMatrix,
					 GLfloat fTime,
					 float timeScale,
					 vmath::vec3 cameraPos,
					 GLuint mainTexture,
					 GLuint depthTexture,
					 GLuint cloudTexture,
					 GLuint detailCloud,
					 vmath::vec3 boundBoxPos,
					 vmath::vec3 boundsScale,
					 float densityMultiplier,
					 float densityOffset,
					 float cloudScale,
					 vmath::vec4 shapeNoiseWeights,
					 float detailOffset,
					 float detailNoiseScale,
					 float detailNoiseWeight,
					 vmath::vec4 detailNoiseWeights,
					 int numStepsLight,
					 float lightAbsorptionThroughCloud,
					 float lightAbsorptionTowardSun,
					 float darknessThreshold,
					 float topFadeStart,
					 float topFadeEnd,
					 float bottomFadeStart,
					 float bottomFadeEnd,
					 vmath::vec4 lightPos,
					 vmath::vec3 lightCol,
					 vmath::vec3 cloudOffset,
					 vmath::vec4 phaseParams)
	{
		vmath::vec3 boundsMin = boundBoxPos - boundsScale;
		vmath::vec3 boundsMax = boundBoxPos + boundsScale;

		// Set the matrix uniforms
		glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, projectionMatrix);
		glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, viewMatrix);
		glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, modelMatrix);

		glUniform1f(fTimeU, fTime);
		glUniform1f(timeScaleU, timeScale);
		glUniform3fv(camposU, 1, cameraPos);
		// glUniform3fv(viewVecU, 1, viewVec);

		glUniform1i(mainTextureUniform, mainTexture);

		glUniform1i(depthTextureUniform, depthTexture);

		glUniform1i(basicCloudUniform, cloudTexture);

		glUniform1i(detailCloudUniform, detailCloud);
		glUniform1i(numStepsLightU, numStepsLight);

		glUniform1f(densityMultiplierUniform, densityMultiplier);
		glUniform1f(densityOffsetUniform, densityOffset);
		glUniform1f(darknessThresholdU, darknessThreshold);

		glUniform1f(cloudScaleUniform, cloudScale);

		glUniform1f(lightAbsorptionThroughCloudU, lightAbsorptionThroughCloud);
		glUniform1f(lightAbsorptionTowardSunU, lightAbsorptionTowardSun);

		glUniform1f(topFadeStartU, topFadeStart);
		glUniform1f(topFadeEndU, topFadeEnd);
		glUniform1f(bottomFadeStartU, bottomFadeStart);
		glUniform1f(bottomFadeEndU, bottomFadeEnd);

		glUniform3fv(boundsMinU, 1, boundsMin);
		glUniform3fv(boundsMaxU, 1, boundsMax);

		glUniform4fv(shapeNoiseWeightsU, 1, shapeNoiseWeights);

		glUniform1f(detailOffsetU, detailOffset);
		glUniform1f(detailNoiseScaleU, detailNoiseScale);
		glUniform1f(detailNoiseWeightU, detailNoiseWeight);
		glUniform4fv(detailNoiseWeightsU, 1, detailNoiseWeights);

		glUniform4fv(lightPosU, 1, lightPos);
		glUniform3fv(lightColU, 1, lightCol);
		glUniform3fv(cloudOffsetU, 1, cloudOffset);

		glUniform4fv(phaseParamsU, 1, phaseParams);

		static GLfloat angle = 0.0f;
		angle += 0.005f; // Increment angle for rotation
	}

	void StartProgram()
	{
		glUseProgram(shaderProgram->GetObject());
	}

	void StopProgram()
	{
		glUseProgram(0);
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
