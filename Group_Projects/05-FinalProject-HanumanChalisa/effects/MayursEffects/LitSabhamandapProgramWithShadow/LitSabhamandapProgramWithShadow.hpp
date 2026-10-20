/***************************************************************************
 * S.G.M.P
 * @file: LitSabhamandapProgramWithShadow.h
 * @brief:
 * @author: Mayur S. Tadekar(mrtadekar@gmail.com)
 * @copyright ©2020-2025 MarshallingVoid
 * @date: Friday 2026-06-05 7:28:38 PM
 ***************************************************************************/

#pragma once

#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/vmath/vmath.h>
#include "../Common/Shader.h"
#include "../Common/Program.h"
// #include "macros.h"

#include "../../../include/common.h"

#include "../../SceneLighting/SceneLighting.h"

// typedef struct LightSource
// {
// 	BOOL bEnable; // on / off per light

// 	vmath::vec3 position; // world-space light position
// 	vmath::vec3 ambient;  // ambient  contribution (keep low, 0.05-0.1)
// 	vmath::vec3 diffuse;  // diffuse  color
// 	vmath::vec3 specular; // specular color
// 	GLfloat shininess;	  // specular exponent  (8-128)
// 	GLfloat intensity;	  // overall multiplier (0.0-3.0)
// 	GLfloat constant;	  // attenuation constant   (default 1.0)
// 	GLfloat linear;		  // attenuation linear     (default 0.09)
// 	GLfloat quadratic;	  // attenuation quadratic  (default 0.032)

// } LightSource;

// typedef struct SceneLightParams
// {
// 	BOOL bEnableLighting;
// 	vmath::vec3 cameraPos;

// 	// 3-points
// 	LightSource keyLight;  // primary directional — strongest, warm
// 	LightSource fillLight; // secondary opposite  — soft, cool
// 	LightSource backLight; // rim / hair light    — behind subject

// } SceneLightParams;

class LitSabhamandapProgramWithShadow
{

private:
	Shader *vertexShader;
	Shader *fragmentShader;
	Program *shaderProgram;

	GLuint uLightEnable[3] = {};
	GLuint uLightPos[3] = {};
	GLuint uAmbient[3] = {};
	GLuint uDiffuse[3] = {};
	GLuint uSpecular[3] = {};
	GLuint uShininess[3] = {};
	GLuint uIntensity[3] = {};
	GLuint uConstant[3] = {};
	GLuint uLinear[3] = {};
	GLuint uQuadratic[3] = {};

	GLuint gLitModelMatrixUniform = 0;
	GLuint gLitViewMatrixUniform = 0;
	GLuint gLitProjectionMatrixUniform = 0;
	GLuint gLitTextureSamplerUniform = 0;
	GLuint gLitClippingPlaneUniform = 0;
	GLuint gLitCameraPosUniform = 0;
	GLuint gLitEnableLightingUniform = 0;

	GLuint hanumanPLVMMatrixU = 0;
	GLuint hanumanShadowTextureU = 0;
	GLuint hanumanShadowPowerU = 0;
	GLuint showHanumanShadowU = 0;

	GLuint vibhishanPLVMMatrixU = 0;
	GLuint vibhishanShadowTextureU = 0;
	GLuint vibhishanShadowPowerU = 0;
	GLuint showVibhishanShadowU = 0;

	GLuint sabhamandapPLVMMatrixU = 0;
	GLuint sabhamandapShadowTextureU = 0;
	GLuint sabhamandapShadowPowerU = 0;
	GLuint showFirePotShadowU = 0;

	GLuint ministerChairPLVMMatrixU = 0;
	GLuint ministerChairShadowTextureU = 0;
	GLuint ministerChairShadowPowerU = 0;
	GLuint showMinisterChairShadowU = 0;

	GLuint pillarPLVMMatrixU = 0;
	GLuint pillarDepthTextureU = 0;
	GLuint pillarShadowPowerU = 0;
	GLuint showPillarChairShadowU = 0;

	LitSabhamandapProgramWithShadow() = delete; // Prevent default constructor

public:
	LitSabhamandapProgramWithShadow(const char *vertexShaderPath, const char *fragmentShaderPath, const char *logFilePath)
	{
		// LOG_ENTRY("log.txt", "MST: Create LitSabhamandapProgramWithShadow VS");
		vertexShader = new Shader(vertexShaderPath, GL_VERTEX_SHADER, logFilePath);
		// LOG_ENTRY("log.txt", "MST: Created Successfully LitSabhamandapProgramWithShadow VS");

		// LOG_ENTRY("log.txt", "MST: Create LitSabhamandapProgramWithShadow FS");
		fragmentShader = new Shader(fragmentShaderPath, GL_FRAGMENT_SHADER, logFilePath);
		// LOG_ENTRY("log.txt", "MST: Created Successfully LitSabhamandapProgramWithShadow FS");

		// LOG_ENTRY("log.txt", "MST: Create LitSabhamandapProgramWithShadow Program");
		shaderProgram = new Program(2, vertexShader->GetObject(), fragmentShader->GetObject());
		// LOG_ENTRY("log.txt", "MST: Created Successfully LitSabhamandapProgramWithShadow Program");

		// LOG_ENTRY("log.txt", "MST: Create LitSabhamandapProgramWithShadow Attribs");
		glBindAttribLocation(shaderProgram->GetObject(), AMC_ATTRIBUTE_POSITION, "aPosition");
		// glBindAttribLocation(shaderProgram->GetObject(), MST_ATTRIBUTES_COLOR, "vColor");
		glBindAttribLocation(shaderProgram->GetObject(), AMC_ATTRIBUTE_TEXCOORD, "aTexCoord");
		glBindAttribLocation(shaderProgram->GetObject(), AMC_ATTRIBUTE_NORMAL, "aNormal");
		// LOG_ENTRY("log.txt", "MST: Created Successfully LitSabhamandapProgramWithShadow Attribs");

		// LOG_ENTRY("log.txt", "MST: Linking LitSabhamandapProgramWithShadow Program");
		shaderProgram->LinkProgram(logFilePath);
		// LOG_ENTRY("log.txt", "MST: Linking Successfully LitSabhamandapProgramWithShadow Program");

		gLitModelMatrixUniform = glGetUniformLocation(shaderProgram->GetObject(), "uModelMatrix");
		gLitViewMatrixUniform = glGetUniformLocation(shaderProgram->GetObject(), "uViewMatrix");
		gLitProjectionMatrixUniform = glGetUniformLocation(shaderProgram->GetObject(), "uProjectionMatrix");

		gLitTextureSamplerUniform = glGetUniformLocation(shaderProgram->GetObject(), "uTextureSampler");
		gLitClippingPlaneUniform = glGetUniformLocation(shaderProgram->GetObject(), "uClippingPlane");
		gLitCameraPosUniform = glGetUniformLocation(shaderProgram->GetObject(), "uCameraPos");
		gLitEnableLightingUniform = glGetUniformLocation(shaderProgram->GetObject(), "uEnableLighting");

		hanumanShadowTextureU = glGetUniformLocation(shaderProgram->GetObject(), "hanumanShadowTexture");
		hanumanShadowPowerU = glGetUniformLocation(shaderProgram->GetObject(), "hanumanShadowPower");
		showHanumanShadowU = glGetUniformLocation(shaderProgram->GetObject(), "showHanumanShadow");
		hanumanPLVMMatrixU = glGetUniformLocation(shaderProgram->GetObject(), "u_hanumanPLVMMatrix");

		vibhishanShadowTextureU = glGetUniformLocation(shaderProgram->GetObject(), "vibhishanShadowTexture");
		vibhishanShadowPowerU = glGetUniformLocation(shaderProgram->GetObject(), "vibhishanShadowPower");
		showVibhishanShadowU = glGetUniformLocation(shaderProgram->GetObject(), "showVibhishanShadow");
		vibhishanPLVMMatrixU = glGetUniformLocation(shaderProgram->GetObject(), "u_vibhishanPLVMMatrix");

		sabhamandapShadowTextureU = glGetUniformLocation(shaderProgram->GetObject(), "sabhamandapShadowTexture");
		sabhamandapShadowPowerU = glGetUniformLocation(shaderProgram->GetObject(), "sabhamandapShadowPower");
		showFirePotShadowU = glGetUniformLocation(shaderProgram->GetObject(), "showFirePotShadow");
		sabhamandapPLVMMatrixU = glGetUniformLocation(shaderProgram->GetObject(), "u_sabhamandapPLVMMatrix");

		ministerChairShadowTextureU = glGetUniformLocation(shaderProgram->GetObject(), "ministerChairShadowTexture");
		ministerChairShadowPowerU = glGetUniformLocation(shaderProgram->GetObject(), "ministerChairShadowPower");
		showMinisterChairShadowU = glGetUniformLocation(shaderProgram->GetObject(), "showMinisterChairShadow");
		ministerChairPLVMMatrixU = glGetUniformLocation(shaderProgram->GetObject(), "ministerChairPLVMMatrix");

		pillarDepthTextureU = glGetUniformLocation(shaderProgram->GetObject(), "pillarShadowTexture");
		pillarShadowPowerU = glGetUniformLocation(shaderProgram->GetObject(), "pillarShadowPower");
		showPillarChairShadowU = glGetUniformLocation(shaderProgram->GetObject(), "showPillarShadow");
		pillarPLVMMatrixU = glGetUniformLocation(shaderProgram->GetObject(), "pillarPLVMMatrix");

		const char *names[3] = {"uLights[0]", "uLights[1]", "uLights[2]"};
		char buf[64];
		for (int i = 0; i < 3; i++)
		{
			sprintf(buf, "%s.bEnable", names[i]);
			uLightEnable[i] = glGetUniformLocation(shaderProgram->GetObject(), buf);
			sprintf(buf, "%s.position", names[i]);
			uLightPos[i] = glGetUniformLocation(shaderProgram->GetObject(), buf);
			sprintf(buf, "%s.ambient", names[i]);
			uAmbient[i] = glGetUniformLocation(shaderProgram->GetObject(), buf);
			sprintf(buf, "%s.diffuse", names[i]);
			uDiffuse[i] = glGetUniformLocation(shaderProgram->GetObject(), buf);
			sprintf(buf, "%s.specular", names[i]);
			uSpecular[i] = glGetUniformLocation(shaderProgram->GetObject(), buf);
			sprintf(buf, "%s.shininess", names[i]);
			uShininess[i] = glGetUniformLocation(shaderProgram->GetObject(), buf);
			sprintf(buf, "%s.intensity", names[i]);
			uIntensity[i] = glGetUniformLocation(shaderProgram->GetObject(), buf);
			sprintf(buf, "%s.constant", names[i]);
			uConstant[i] = glGetUniformLocation(shaderProgram->GetObject(), buf);
			sprintf(buf, "%s.linear", names[i]);
			uLinear[i] = glGetUniformLocation(shaderProgram->GetObject(), buf);
			sprintf(buf, "%s.quadratic", names[i]);
			uQuadratic[i] = glGetUniformLocation(shaderProgram->GetObject(), buf);
		}
	}

	~LitSabhamandapProgramWithShadow()
	{
		delete vertexShader;
		delete fragmentShader;
		delete shaderProgram;
	}

	void StartProgram()
	{
		// Code
		glUseProgram(shaderProgram->GetObject());
	}

	void StopProgram()
	{
		glUseProgram(0);
	}

	void SetUniforms(vmath::mat4 &projectionMatrix,
					 vmath::mat4 &viewMatrix,
					 vmath::mat4 &modelMatrix,
					 vmath::mat4 &hanumanplvmMatrix,
					 vmath::mat4 &vibhishanplvmMatrix,
					 vmath::mat4 &sabhamandapplvmMatrix,
					 vmath::mat4 &ministerChairplvmMatrix,
					 vmath::mat4 &pillarplvmMatrix,
					 vmath::vec4 clippingPlane,
					 SceneLightParams &params,
					 GLuint hanumanDepthTexture,
					 GLuint hanumanShadowPower,
					 int showHanumanShadow,
					 GLuint vibhishanDepthTexture,
					 GLuint vibhishanShadowPower,
					 int showVibhishanShadow,
					 GLuint sabhamandapDepthTexture,
					 GLuint sabhamandapShadowPower,
					 int showFirePotShadow,
					 GLuint ministerChairDepthTexture,
					 GLuint ministerChairShadowPower,
					 int showMinisterChairShadow,
					 GLuint pillarDepthTexture,
					 GLuint pillarShadowPower,
					 int showPillarShadow)
	{
		// Set the matrix uniforms
		glUniform1i(gLitEnableLightingUniform, params.bEnableLighting ? 1 : 0);
		glUniform3fv(gLitCameraPosUniform, 1, params.cameraPos);
		LightSource *lights[3] = {&params.keyLight, &params.fillLight, &params.backLight};

		glUniformMatrix4fv(gLitModelMatrixUniform, 1, GL_FALSE, modelMatrix);
		glUniformMatrix4fv(gLitViewMatrixUniform, 1, GL_FALSE, viewMatrix);
		glUniformMatrix4fv(gLitProjectionMatrixUniform, 1, GL_FALSE, projectionMatrix);
		glUniformMatrix4fv(hanumanPLVMMatrixU, 1, GL_FALSE, hanumanplvmMatrix);
		glUniformMatrix4fv(vibhishanPLVMMatrixU, 1, GL_FALSE, vibhishanplvmMatrix);
		glUniformMatrix4fv(sabhamandapPLVMMatrixU, 1, GL_FALSE, sabhamandapplvmMatrix);
		glUniformMatrix4fv(ministerChairPLVMMatrixU, 1, GL_FALSE, ministerChairplvmMatrix);
		glUniformMatrix4fv(pillarPLVMMatrixU, 1, GL_FALSE, pillarplvmMatrix);

		glUniform4fv(gLitClippingPlaneUniform, 1, clippingPlane);
		glUniform1i(gLitTextureSamplerUniform, 0);

		glUniform1i(hanumanShadowTextureU, hanumanDepthTexture);
		glUniform1i(hanumanShadowPowerU, hanumanShadowPower);
		glUniform1i(showHanumanShadowU, showHanumanShadow);

		glUniform1i(vibhishanShadowTextureU, vibhishanDepthTexture);
		glUniform1i(vibhishanShadowPowerU, vibhishanShadowPower);
		glUniform1i(showVibhishanShadowU, showVibhishanShadow);

		glUniform1i(sabhamandapShadowTextureU, sabhamandapDepthTexture);
		glUniform1i(sabhamandapShadowPowerU, sabhamandapShadowPower);
		glUniform1i(showFirePotShadowU, showFirePotShadow);

		glUniform1i(ministerChairShadowTextureU, ministerChairDepthTexture);
		glUniform1i(ministerChairShadowPowerU, ministerChairShadowPower);
		glUniform1i(showMinisterChairShadowU, showMinisterChairShadow);

		glUniform1i(pillarDepthTextureU, pillarDepthTexture);
		glUniform1i(pillarShadowPowerU, pillarShadowPower);
		glUniform1i(showPillarChairShadowU, showPillarShadow);

		for (int i = 0; i < 3; i++)
		{
			LightSource &L = *lights[i];
			glUniform1i(uLightEnable[i], L.bEnable ? 1 : 0);
			glUniform3fv(uLightPos[i], 1, L.position);
			glUniform3fv(uAmbient[i], 1, L.ambient);
			glUniform3fv(uDiffuse[i], 1, L.diffuse);
			glUniform3fv(uSpecular[i], 1, L.specular);
			glUniform1f(uShininess[i], L.shininess);
			glUniform1f(uIntensity[i], L.intensity);
			glUniform1f(uConstant[i], L.constant);
			glUniform1f(uLinear[i], L.linear);
			glUniform1f(uQuadratic[i], L.quadratic);
		}
	}

	GLuint GetProgram() const
	{
		return (shaderProgram->GetObject());
	}
};
