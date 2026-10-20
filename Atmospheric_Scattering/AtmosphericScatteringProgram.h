/***************************************************************************
 * S.G.M.P
 * @file: AtmosphericScatteringProgram.h
 * @brief:
 * @author: Mayur S. Tadekar(mrtadekar@gmail.com)
 * @copyright ©2020-2025 MarshallingVoid
 * @date: Wednesday 2025-06-18 2:19:17 PM
 ***************************************************************************/

#pragma once

#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/vmath/vmath.h>
#include "Shader.h"
#include "Program.h"
#include "macros.h"

#include "imgui.h"
#include "backends/imgui_impl_win32.h"
#include "backends/imgui_impl_opengl3.h"

class AtmosphericScatteringProgram
{
private:
	Shader *vertexShader;
	Shader *fragmentShader;
	Program *shaderProgram;

	// Shader uniforms
	GLuint modelMatrixUniform;
	GLuint viewMatrixUniform;
	GLuint _viewMatrixUniform;
	GLuint projectionMatrixUniform;

	GLuint mainTextureUniform;
	GLuint depthTextureUniform;

	float innerRadius;
	float outerRadius;
	float rayleighScaleHeight;
	float mieScaleHeight;

	float sunSpeed;
	float sunYaw;
	float sunPitch;
	vmath::vec3 sunPos;

	bool seeSaw;
	bool bAnimate;

public:
	AtmosphericScatteringProgram()
		: vertexShader(nullptr), fragmentShader(nullptr), shaderProgram(nullptr),
		  modelMatrixUniform(0), viewMatrixUniform(0), projectionMatrixUniform(0)
	{
		seeSaw = false;
		bAnimate = false;
	}

	~AtmosphericScatteringProgram() = default;

	void Initialize()
	{
		sunYaw = -90.0;
		sunPitch = -40.0;
		sunSpeed = 0.005f;

		innerRadius = 50000.0f;
		outerRadius = 60000.0f;
		rayleighScaleHeight = 200.0f;
		mieScaleHeight = 300.0f;

		// Create vertex shader
		vertexShader = new Shader("AtmosphericScattering_vs.glsl", GL_VERTEX_SHADER, "log.txt");

		// Create fragment shader
		fragmentShader = new Shader("AtmosphericScattering_fs.glsl", GL_FRAGMENT_SHADER, "log.txt");

		// Create and link shader program
		shaderProgram = new Program(2, vertexShader->GetObject(), fragmentShader->GetObject());
		glBindAttribLocation(shaderProgram->GetObject(), MST_ATTRIBUTES_POSITION, "vPosition");
		glBindAttribLocation(shaderProgram->GetObject(), MST_ATTRIBUTES_COLOR, "vColor");
		glBindAttribLocation(shaderProgram->GetObject(), MST_ATTRIBUTES_TEXCOORD, "vTexCoord");
		glBindAttribLocation(shaderProgram->GetObject(), MST_ATTRIBUTES_NORMAL, "vNormal");
		shaderProgram->LinkProgram("log.txt");

		// Get uniform locations
		modelMatrixUniform = glGetUniformLocation(shaderProgram->GetObject(), "u_mMatrix");
		viewMatrixUniform = glGetUniformLocation(shaderProgram->GetObject(), "u_vMatrix");
		_viewMatrixUniform = glGetUniformLocation(shaderProgram->GetObject(), "u_vvMatrix");
		projectionMatrixUniform = glGetUniformLocation(shaderProgram->GetObject(), "u_pMatrix");
	}

	void DisplayIMGUI()
	{
		if (ImGui::CollapsingHeader("Scattering Parameters", ImGuiTreeNodeFlags_DefaultOpen))
		{

			ImGui::DragFloat(
				"Sun Yaw",
				&sunYaw,
				0.1f);

			ImGui::DragFloat(
				"Sun Pitch",
				&sunPitch,
				0.1f);

			sunPos[0] = 1000 * cosf(vmath::radians(sunYaw)) * cosf(vmath::radians(sunPitch));
			sunPos[1] = 1000 * sinf(vmath::radians(sunPitch));
			sunPos[2] = 1000 * sinf(vmath::radians(sunYaw)) * cosf(vmath::radians(sunPitch));

			ImGui::Separator();

			ImGui::DragFloat(
				"Rayleigh ScaleHeight",
				&rayleighScaleHeight,
				0.1f);

			ImGui::DragFloat(
				"Mie ScaleHeight",
				&mieScaleHeight,
				0.1f);

			ImGui::DragFloat(
				"Sun Speed",
				&sunSpeed,
				0.001f);

			if (ImGui::Button("sunrise", ImVec2(50, 20)))
			{
				seeSaw = true;
			}

			ImGui::SameLine();

			if (ImGui::Button("sunset", ImVec2(50, 20)))
			{
				seeSaw = false;
			}

			ImGui::SameLine();

			if (ImGui::Button("Animate", ImVec2(50, 20)))
			{
				bAnimate = !bAnimate;
			}
		}
	}

	void SetUniforms(vmath::mat4 &projectionMatrix,
					 vmath::mat4 &modelMatrix,
					 vmath::mat4 &viewMatrix,
					 vmath::mat4 &_viewMatrix,
					 vmath::vec3 cameraPos,
					 GLuint mainTexture,
					 GLuint depthTexture,
					 vmath::vec3 boundBoxPos,
					 float boundsScale)
	{
		// Set the matrix uniforms
		glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, projectionMatrix);
		glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, viewMatrix);
		glUniformMatrix4fv(_viewMatrixUniform, 1, GL_FALSE, _viewMatrix);
		glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, modelMatrix);

		vmath::vec3 sunDir = vmath::normalize(sunPos);
		glUniform3fv(glGetUniformLocation(shaderProgram->GetObject(), "sunDir"), 1, sunDir);
		glUniform3fv(glGetUniformLocation(shaderProgram->GetObject(), "cameraPos"), 1, cameraPos);

		glUniform1f(glGetUniformLocation(shaderProgram->GetObject(), "innerRadius"), innerRadius);
		glUniform1f(glGetUniformLocation(shaderProgram->GetObject(), "outerRadius"), outerRadius);

		glUniform1f(glGetUniformLocation(shaderProgram->GetObject(), "rayleighScaleHeight"), rayleighScaleHeight);
		glUniform1f(glGetUniformLocation(shaderProgram->GetObject(), "mieScaleHeight"), mieScaleHeight);

		float scatteringStrength = 20.0f;

		vmath::vec3 invWavelength(
			pow(400.0f / 700.0f, 4.0f) * scatteringStrength,
			pow(400.0f / 530.0f, 4.0f) * scatteringStrength,
			pow(400.0f / 440.0f, 4.0f) * scatteringStrength);

		glUniform3fv(glGetUniformLocation(shaderProgram->GetObject(), "invWavelength"), 1, invWavelength);

		glUniform1f(glGetUniformLocation(shaderProgram->GetObject(), "Kr"), 0.0025f);
		glUniform1f(glGetUniformLocation(shaderProgram->GetObject(), "Km"), 0.0010f);
		glUniform1f(glGetUniformLocation(shaderProgram->GetObject(), "ESun"), 15.0f);
	}

	void Update()
	{
		// Code
		if (!bAnimate)
			return;

		if (seeSaw)
		{
			sunPitch += sunSpeed;
		}
		else
		{
			sunPitch -= sunSpeed;
		}
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
