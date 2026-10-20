/***************************************************************************
 * S.G.M.P
 * @file: OceanProgram.h
 * @brief:
 * @author: Mayur S. Tadekar(mrtadekar@gmail.com)
 * @copyright ©2020-2025 MarshallingVoid
 * @date: Wednesday 2025-06-18 5:54:23 PM
 ***************************************************************************/

#pragma once

#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/vmath/vmath.h>
#include "Shader.h"
#include "Program.h"
#include "macros.h"
#include "common.h"

#include "imgui.h"
#include "backends/imgui_impl_win32.h"
#include "backends/imgui_impl_opengl3.h"
#include "TextureLoader.h"

struct Wave
{
	vec2 direction;
	float amplitude;
	float wavelength;
	float speed;
	float steepness;
};

struct WaveUniform
{
	GLint direction;
	GLint amplitude;
	GLint wavelength;
	GLint speed;
	GLint steepness;
};

class OceanProgram
{

private:
	Shader *vertexShader;
	Shader *fragmentShader;
	Program *shaderProgram;

	GLuint modelMatrixUniform;
	GLuint viewMatrixUniform;
	GLuint projectionMatrixUniform;
	GLuint timeU;
	GLuint cameraPosUniform;
	GLuint sunPosUniform;
	WaveUniform wavesU[16];
	GLuint wavesCountU;

	vmath::vec3 sunPos;
	float sunYaw;
	float sunPitch;

	GLuint waterNormalMapTexture01;
	GLuint waterNormalMap01SamplerUniform;

	GLuint waterNormalMapTexture02;
	GLuint waterNormalMap02SamplerUniform;

	GLuint cubemap;
	GLuint cubemapSamplerUniform;

	int wavesCount;
	OceanProgram() = delete; // Prevent default constructor

	Wave waves[16];

public:
	OceanProgram(const char *vertexShaderPath, const char *fragmentShaderPath, const char *logFilePath)
	{
		// Code
		wavesCount = 16;
		sunPos = vmath::vec3(0.0, 100.0, 0.0);

		sunYaw = -90.0;
		sunPitch = 45.0;

		// direction, amplitude, wavelength, speed, steepness

		waves[0] = {normalize(vec2(0.08f, -1.00f)), 1.20f, 120.0f, 1.10f, 0.80f};
		waves[1] = {normalize(vec2(0.20f, 0.98f)), 0.90f, 90.0f, 1.25f, 0.75f};
		waves[2] = {normalize(vec2(-0.12f, 0.95f)), 0.60f, 70.0f, 1.40f, 0.70f};
		waves[3] = {normalize(vec2(0.28f, 0.92f)), 0.45f, 50.0f, 1.80f, 0.65f};

		waves[4] = {normalize(vec2(-0.25f, 0.88f)), 0.35f, 40.0f, 2.10f, 0.60f};
		waves[5] = {normalize(vec2(0.35f, 0.85f)), 0.28f, 32.0f, 2.50f, 0.60f};
		waves[6] = {normalize(vec2(-0.40f, 0.80f)), 0.22f, 26.0f, 2.90f, 0.55f};
		waves[7] = {normalize(vec2(0.45f, 0.75f)), 0.18f, 20.0f, 3.40f, 0.50f};

		waves[8] = {normalize(vec2(-0.55f, 0.70f)), 0.14f, 16.0f, 3.90f, 0.50f};
		waves[9] = {normalize(vec2(0.60f, 0.65f)), 0.11f, 13.0f, 4.50f, 0.45f};
		waves[10] = {normalize(vec2(-0.75f, 0.55f)), 0.08f, 10.0f, 5.20f, 0.40f};
		waves[11] = {normalize(vec2(0.90f, 0.40f)), 0.06f, 8.0f, 5.80f, 0.35f};

		waves[12] = {normalize(vec2(-0.97f, 0.25f)), 0.045f, 6.5f, 6.40f, 0.35f};
		waves[13] = {normalize(vec2(0.98f, -0.20f)), 0.030f, 5.0f, 7.20f, 0.30f};
		waves[14] = {normalize(vec2(0.80f, -0.60f)), 0.020f, 4.0f, 8.00f, 0.25f};
		waves[15] = {normalize(vec2(0.40f, -0.85f)), 0.012f, 3.0f, 9.00f, 0.20f};

		vertexShader = new Shader(vertexShaderPath, GL_VERTEX_SHADER, logFilePath);
		fragmentShader = new Shader(fragmentShaderPath, GL_FRAGMENT_SHADER, logFilePath);

		shaderProgram = new Program(2, vertexShader->GetObject(), fragmentShader->GetObject());

		glBindAttribLocation(shaderProgram->GetObject(), MST_ATTRIBUTES_POSITION, "vPosition");
		glBindAttribLocation(shaderProgram->GetObject(), MST_ATTRIBUTES_COLOR, "vColor");
		glBindAttribLocation(shaderProgram->GetObject(), MST_ATTRIBUTES_TEXCOORD, "vTexcoord");
		glBindAttribLocation(shaderProgram->GetObject(), MST_ATTRIBUTES_NORMAL, "vNormal");

		shaderProgram->LinkProgram(logFilePath);

		modelMatrixUniform = glGetUniformLocation(shaderProgram->GetObject(), "u_mMatrix");
		viewMatrixUniform = glGetUniformLocation(shaderProgram->GetObject(), "u_vMatrix");
		projectionMatrixUniform = glGetUniformLocation(shaderProgram->GetObject(), "u_pMatrix");
		timeU = glGetUniformLocation(shaderProgram->GetObject(), "time");
		cameraPosUniform = glGetUniformLocation(shaderProgram->GetObject(), "cameraPos");
		sunPosUniform = glGetUniformLocation(shaderProgram->GetObject(), "sunPos");
		wavesCountU = glGetUniformLocation(shaderProgram->GetObject(), "wavesCount");
		waterNormalMap01SamplerUniform = glGetUniformLocation(shaderProgram->GetObject(), "waterNormalMap01Sampler");
		waterNormalMap02SamplerUniform = glGetUniformLocation(shaderProgram->GetObject(), "waterNormalMap02Sampler");
		cubemapSamplerUniform = glGetUniformLocation(shaderProgram->GetObject(), "skyboxSampler");

		for (int i = 0; i < 16; i++)
		{
			std::string idx = std::to_string(i);

			wavesU[i].direction =
				glGetUniformLocation(
					shaderProgram->GetObject(),
					("waves[" + idx + "].direction").c_str());

			wavesU[i].amplitude =
				glGetUniformLocation(
					shaderProgram->GetObject(),
					("waves[" + idx + "].amplitude").c_str());

			wavesU[i].wavelength =
				glGetUniformLocation(
					shaderProgram->GetObject(),
					("waves[" + idx + "].wavelength").c_str());

			wavesU[i].speed =
				glGetUniformLocation(
					shaderProgram->GetObject(),
					("waves[" + idx + "].speed").c_str());

			wavesU[i].steepness =
				glGetUniformLocation(
					shaderProgram->GetObject(),
					("waves[" + idx + "].steepness").c_str());
		}

		if (TextureLoader::LoadTextureFromFile("./waternormal1.jpg", &waterNormalMapTexture01))
		{
			LOG_ENTRY("log.txt", "./waternormal1.jpg Loaded Successfully");
		}
		else
		{
			LOG_ENTRY("log.txt", "./waternormal1.jpg Loaded NOT Successfully");
		}

		if (TextureLoader::LoadTextureFromFile(".\\waternormal2.png", &waterNormalMapTexture02))
		{
			LOG_ENTRY("log.txt", ".\\waternormal2.png Loaded Successfully");
		}
		else
		{
			LOG_ENTRY("log.txt", ".\\waternormal2.png Loaded NOT Successfully");
		}

		if (TextureLoader::LoadTextureFromFile(".\\cubemap.png", &cubemap))
		{
			LOG_ENTRY("log.txt", ".\\cubemap.png Loaded Successfully");
		}
		else
		{
			LOG_ENTRY("log.txt", ".\\cubemap.png Loaded NOT Successfully");
		}
	}

	~OceanProgram()
	{
		delete vertexShader;
		delete fragmentShader;
		delete shaderProgram;
	}

	vmath::vec3 GetSunPos() const { return (sunPos); }

	void StartProgram()
	{
		// Code
		glUseProgram(shaderProgram->GetObject());
	}

	void StopProgram()
	{
		glUseProgram(0);
	}

	void DisplayIMGUIForWaves()
	{
		ImGui::Begin("Values");

		if (ImGui::CollapsingHeader("Ocean Waves", ImGuiTreeNodeFlags_DefaultOpen))
		{
			if (ImGui::Button("Reset To Default"))
			{
				waves[0] = {normalize(vec2(0.08f, -1.00f)), 2.00f, 120.0f, 1.10f, 0.80f};
				waves[1] = {normalize(vec2(0.20f, 0.98f)), 1.60f, 90.0f, 1.25f, 0.75f};
				waves[2] = {normalize(vec2(-0.12f, 0.95f)), 1.00f, 70.0f, 1.40f, 0.70f};
				waves[3] = {normalize(vec2(0.28f, 0.92f)), 0.80f, 50.0f, 1.80f, 0.65f};

				waves[4] = {normalize(vec2(-0.25f, 0.88f)), 0.70f, 40.0f, 2.10f, 0.60f};
				waves[5] = {normalize(vec2(0.35f, 0.85f)), 0.60f, 32.0f, 2.50f, 0.60f};
				waves[6] = {normalize(vec2(-0.40f, 0.80f)), 0.50f, 26.0f, 2.90f, 0.55f};
				waves[7] = {normalize(vec2(0.45f, 0.75f)), 0.40f, 20.0f, 3.40f, 0.50f};

				waves[8] = {normalize(vec2(-0.55f, 0.70f)), 0.35f, 16.0f, 3.90f, 0.50f};
				waves[9] = {normalize(vec2(0.60f, 0.65f)), 0.30f, 13.0f, 4.50f, 0.45f};
				waves[10] = {normalize(vec2(-0.75f, 0.55f)), 0.22f, 10.0f, 5.20f, 0.40f};
				waves[11] = {normalize(vec2(0.90f, 0.40f)), 0.18f, 8.0f, 5.80f, 0.35f};

				waves[12] = {normalize(vec2(-0.97f, 0.25f)), 0.15f, 6.5f, 6.40f, 0.35f};
				waves[13] = {normalize(vec2(0.98f, -0.20f)), 0.10f, 5.0f, 7.20f, 0.30f};
				waves[14] = {normalize(vec2(0.80f, -0.60f)), 0.08f, 4.0f, 8.00f, 0.25f};
				waves[15] = {normalize(vec2(0.40f, -0.85f)), 0.05f, 3.0f, 9.00f, 0.20f};
			}

			ImGui::Separator();

			ImGui::DragFloat(
				"Sun Yaw",
				&sunYaw,
				0.5f,
				-180.0f,
				180.0f);

			ImGui::DragFloat(
				"Sun Pitch",
				&sunPitch,
				0.5f,
				-180.0f,
				180.0f);

			sunPos[0] = 1000 * cosf(vmath::radians(sunYaw)) * cosf(vmath::radians(sunPitch));
			sunPos[1] = 1000 * sinf(vmath::radians(sunPitch));
			sunPos[2] = 1000 * sinf(vmath::radians(sunYaw)) * cosf(vmath::radians(sunPitch));

			ImGui::Separator();

			ImGui::DragInt(
				"WaveCount",
				&wavesCount,
				1.0,
				0,
				16);

			for (int i = 0; i < wavesCount; i++)
			{
				char label[32];
				sprintf(label, "Wave %d", i);

				if (ImGui::CollapsingHeader(label))
				{

					float dir[2] =
						{
							waves[i].direction[0],
							waves[i].direction[1]};

					sprintf(label, "Direction %d", i);
					ImGui::DragFloat2(
						label,
						dir,
						0.01f,
						-1.0f,
						1.0f);

					waves[i].direction =
						normalize(vec2(dir[0], dir[1]));

					sprintf(label, "Amplitude %d", i);
					ImGui::DragFloat(
						label,
						&waves[i].amplitude,
						0.01f,
						0.0f,
						10.0f);

					sprintf(label, "Wavelength %d", i);
					ImGui::DragFloat(
						label,
						&waves[i].wavelength,
						0.1f,
						0.1f,
						500.0f);

					sprintf(label, "Speed %d", i);
					ImGui::DragFloat(
						label,
						&waves[i].speed,
						0.01f,
						0.0f,
						20.0f);

					sprintf(label, "Steepness %d", i);
					ImGui::SliderFloat(
						label,
						&waves[i].steepness,
						0.0f,
						1.0f);
				}
			}
		}
		ImGui::End();
	}

	void SetUniforms(vmath::mat4 &projectionMatrix,
					 vmath::mat4 &viewMatrix,
					 vmath::mat4 &modelMatrix,
					 float time,
					 vmath::vec3 camPos)
	{
		// Set the matrix uniforms
		glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, projectionMatrix);
		glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, viewMatrix);
		glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, modelMatrix);

		glUniform3fv(cameraPosUniform, 1, camPos);

		glUniform3fv(sunPosUniform, 1, sunPos);

		glUniform1f(timeU, time);
		glUniform1i(wavesCountU, wavesCount);

		for (int i = 0; i < 16; i++)
		{
			glUniform2f(
				wavesU[i].direction,
				waves[i].direction[0],
				waves[i].direction[1]);

			glUniform1f(
				wavesU[i].amplitude,
				waves[i].amplitude);

			glUniform1f(
				wavesU[i].wavelength,
				waves[i].wavelength);

			glUniform1f(
				wavesU[i].speed,
				waves[i].speed);

			glUniform1f(
				wavesU[i].steepness,
				waves[i].steepness);
		}

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, waterNormalMapTexture01);
		glUniform1i(waterNormalMap01SamplerUniform, 0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, waterNormalMapTexture02);
		glUniform1i(waterNormalMap02SamplerUniform, 1);

		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, cubemap);
		glUniform1i(cubemapSamplerUniform, 3);
	}
};