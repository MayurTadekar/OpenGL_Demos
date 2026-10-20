
#include <fstream>
#include <string>
#include <unordered_map>

#include "CloudProgram.h"

#include "FrameBufferObjectWithDepth.h"
#include "ComputeShader.hpp"

#include "triangle.h"

#include "../Common/common.h"

#include "./../../../modules/imgui/imgui.h"
#include "./../../../modules/imgui/imgui_impl_win32.h"
#include "./../../../modules/imgui/imgui_impl_opengl3.h"
#include "VolumetricClouds.hpp"

VolumetricClouds::VolumetricClouds()
{
	// Code
	cprogram = new CloudsProgram();
	cprogram->Initialize();

	basicFbo = new FrameBufferObjectWithDepth(WIN_WIDTH / 2, WIN_HEIGHT / 2, GL_RGBA16F, GL_DEPTH_COMPONENT32F);
	basicFbo->Initialize();

	basicCloud = new ComputeShader("./effects/MayursEffects/VolumetricClouds/computeshader.glsl", WIN_WIDTH, WIN_HEIGHT);
	detailCloud = new ComputeShader("./effects/MayursEffects/VolumetricClouds/computeshader.glsl", WIN_WIDTH, WIN_HEIGHT);

	triangle = new Triangle();
	triangle->Initialize();
}

VolumetricClouds::VolumetricClouds(const char *filename)
{
	// Code
	cprogram = new CloudsProgram();
	cprogram->Initialize();

	basicFbo = new FrameBufferObjectWithDepth(WIN_WIDTH / 2, WIN_HEIGHT / 2, GL_RGBA16F, GL_DEPTH_COMPONENT32F);
	basicFbo->Initialize();

	basicCloud = new ComputeShader("./effects/MayursEffects/VolumetricClouds/computeshader.glsl", WIN_WIDTH, WIN_HEIGHT);
	detailCloud = new ComputeShader("./effects/MayursEffects/VolumetricClouds/computeshader.glsl", WIN_WIDTH, WIN_HEIGHT);

	triangle = new Triangle();
	triangle->Initialize();

	auto settings = LoadSettings(filename);

	xpos = GetFloat(settings, "xpos");
	ypos = GetFloat(settings, "ypos");
	zpos = GetFloat(settings, "zpos");

	boundsScaleX = GetFloat(settings, "boundsScaleX");
	boundsScaleY = GetFloat(settings, "boundsScaleY");
	boundsScaleZ = GetFloat(settings, "boundsScaleZ");

	zSlice = GetFloat(settings, "zSlice");

	redChannel = GetBool(settings, "redChannel");
	redScaleA = GetInt(settings, "redScaleA");
	redScaleB = GetInt(settings, "redScaleB");
	redScaleC = GetInt(settings, "redScaleC");
	redpersistence = GetFloat(settings, "redPersistence");

	greenChannel = GetBool(settings, "greenChannel");
	greenScaleA = GetInt(settings, "greenScaleA");
	greenScaleB = GetInt(settings, "greenScaleB");
	greenScaleC = GetInt(settings, "greenScaleC");
	greenpersistence = GetFloat(settings, "greenPersistence");

	blueChannel = GetBool(settings, "blueChannel");
	blueScaleA = GetInt(settings, "blueScaleA");
	blueScaleB = GetInt(settings, "blueScaleB");
	blueScaleC = GetInt(settings, "blueScaleC");
	bluepersistence = GetFloat(settings, "bluePersistence");

	redWeight = GetFloat(settings, "redWeight");
	greenWeight = GetFloat(settings, "greenWeight");
	blueWeight = GetFloat(settings, "blueWeight");
	alphaWeight = GetFloat(settings, "alphaWeight");

	densityMultiplier = GetFloat(settings, "densityMultiplier");
	densityOffset = GetFloat(settings, "densityOffset");
	cloudScale = GetFloat(settings, "cloudScale");

	redDetailChannel = GetBool(settings, "redDetailChannel");
	redDetailScaleA = GetInt(settings, "redDetailScaleA");
	redDetailScaleB = GetInt(settings, "redDetailScaleB");
	redDetailScaleC = GetInt(settings, "redDetailScaleC");
	redDetailpersistence = GetFloat(settings, "redDetailPersistence");

	greenDetailChannel = GetBool(settings, "greenDetailChannel");
	greenDetailScaleA = GetInt(settings, "greenDetailScaleA");
	greenDetailScaleB = GetInt(settings, "greenDetailScaleB");
	greenDetailScaleC = GetInt(settings, "greenDetailScaleC");
	greenDetailpersistence = GetFloat(settings, "greenDetailPersistence");

	blueDetailChannel = GetBool(settings, "blueDetailChannel");
	blueDetailScaleA = GetInt(settings, "blueDetailScaleA");
	blueDetailScaleB = GetInt(settings, "blueDetailScaleB");
	blueDetailScaleC = GetInt(settings, "blueDetailScaleC");
	blueDetailpersistence = GetFloat(settings, "blueDetailPersistence");

	detailOffset = GetFloat(settings, "detailOffset");
	detailNoiseScale = GetFloat(settings, "detailNoiseScale");
	detailNoiseWeight = GetFloat(settings, "detailNoiseWeight");

	redDetailWeight = GetFloat(settings, "redDetailWeight");
	greenDetailWeight = GetFloat(settings, "greenDetailWeight");
	blueDetailWeight = GetFloat(settings, "blueDetailWeight");
	alphaDetailWeight = GetFloat(settings, "alphaDetailWeight");

	bottomFadeStart = GetFloat(settings, "bottomFadeStart");
	bottomFadeEnd = GetFloat(settings, "bottomFadeEnd");
	topFadeStart = GetFloat(settings, "topFadeStart");
	topFadeEnd = GetFloat(settings, "topFadeEnd");

	numStepsLight = GetInt(settings, "numStepsLight");

	timeScale = GetFloat(settings, "timeScale");

	lightAbsorptionThroughCloud = GetFloat(settings, "lightAbsorptionThroughCloud");
	lightAbsorptionTowardSun = GetFloat(settings, "lightAbsorptionTowardSun");
	darknessThreshold = GetFloat(settings, "darknessThreshold");

	lightX = GetFloat(settings, "lightX");
	lightY = GetFloat(settings, "lightY");
	lightZ = GetFloat(settings, "lightZ");

	lightR = GetFloat(settings, "lightR");
	lightG = GetFloat(settings, "lightG");
	lightB = GetFloat(settings, "lightB");

	forwardScatter = GetFloat(settings, "forwardScatter");
	backwardScatter = GetFloat(settings, "backwardScatter");
	baseBrightness = GetFloat(settings, "baseBrightness");
	strength = GetFloat(settings, "strength");

	cloudOffsetX = GetFloat(settings, "cloudOffsetX");
	cloudOffsetY = GetFloat(settings, "cloudOffsetY");
	cloudOffsetZ = GetFloat(settings, "cloudOffsetZ");
}

std::unordered_map<std::string, std::string> VolumetricClouds::LoadSettings(const char *filename)
{
	std::unordered_map<std::string, std::string> settings;

	std::ifstream file(filename);

	std::string line;
	while (std::getline(file, line))
	{
		size_t pos = line.find('=');

		if (pos == std::string::npos)
			continue;

		std::string key = line.substr(0, pos);
		std::string value = line.substr(pos + 1);

		settings[key] = value;
	}

	LOG_ENTRY("log.txt", "Cloud Settings Loaded Successfully");

	return settings;
}

float VolumetricClouds::GetFloat(const std::unordered_map<std::string, std::string> &settings,
								 const std::string &key,
								 float defaultValue)
{
	auto it = settings.find(key);
	if (it == settings.end())
		return defaultValue;

	return std::stof(it->second);
}

int VolumetricClouds::GetInt(const std::unordered_map<std::string, std::string> &settings,
							 const std::string &key,
							 int defaultValue)
{
	auto it = settings.find(key);
	if (it == settings.end())
		return defaultValue;

	return std::stoi(it->second);
}

bool VolumetricClouds::GetBool(const std::unordered_map<std::string, std::string> &settings,
							   const std::string &key,
							   bool defaultValue)
{
	auto it = settings.find(key);
	if (it == settings.end())
		return defaultValue;

	return std::stoi(it->second) != 0;
}

void VolumetricClouds::Resize(int width, int height)
{
	// Code

	if (basicFbo)
		basicFbo->Resize(width, height);

	if (basicCloud)
	{
		basicCloud->Resize(width, height);
	}

	if (detailCloud)
	{
		detailCloud->Resize(width, height);
	}
}

void VolumetricClouds::RenderCloudTextures()
{
	// Code
	basicCloud->Render(redChannel, redScaleA, redScaleB, redScaleC, redpersistence,
					   greenChannel, greenScaleA, greenScaleB, greenScaleC, greenpersistence,
					   blueChannel, blueScaleA, blueScaleB, blueScaleC, bluepersistence);

	detailCloud->Render(redDetailChannel, redDetailScaleA, redDetailScaleB, redDetailScaleC, redDetailpersistence,
						greenDetailChannel, greenDetailScaleA, greenDetailScaleB, greenDetailScaleC, greenDetailpersistence,
						blueDetailChannel, blueDetailScaleA, blueDetailScaleB, blueDetailScaleC, blueDetailpersistence);
}

void VolumetricClouds::StartRenderingToFBO()
{
	// Code
	if (basicFbo)
	{
		basicFbo->Clear(0.0f, 0.0f, 0.0f, 0.0f);
		basicFbo->Bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
	}
}

void VolumetricClouds::StopRenderingToFBO()
{
	// Code

	if (basicFbo)
	{
		basicFbo->Unbind();
	}
}

void VolumetricClouds::Display(vmath::mat4 &projectionMatrix,
							   vmath::mat4 &modelMatrix,
							   vmath::mat4 &viewMatrix,
							   vmath::vec3 cameraPosition,
							   float time)
{
	// Code
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (cprogram)
	{
		// glEnable(GL_BLEND);
		glDisable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDepthMask(GL_FALSE);
		cprogram->StartProgram();

		// viewMatrix = camera.GetViewMatrix();

		basicFbo->BindColorTexture(0);

		basicFbo->BindDepthTexture(1);

		basicCloud->BindTexture(2);

		detailCloud->BindTexture(3);

		cprogram->SetUniforms(projectionMatrix,
							  modelMatrix,
							  viewMatrix,
							  time,
							  timeScale,
							  cameraPosition,
							  0,
							  1,
							  2,
							  3,
							  vmath::vec3(xpos, ypos, zpos),
							  vmath::vec3(boundsScaleX, boundsScaleY, boundsScaleZ),
							  densityMultiplier,
							  densityOffset,
							  cloudScale,
							  vmath::vec4(redWeight, greenWeight, blueWeight, alphaWeight),
							  detailOffset,
							  detailNoiseScale,
							  detailNoiseWeight,
							  vmath::vec4(redDetailWeight, greenDetailWeight, blueDetailWeight, alphaDetailWeight),
							  numStepsLight,
							  lightAbsorptionThroughCloud,
							  lightAbsorptionTowardSun,
							  darknessThreshold,
							  topFadeStart,
							  topFadeEnd,
							  bottomFadeStart,
							  bottomFadeEnd,
							  vmath::vec4(lightX, lightY, lightZ, 1.0),
							  vmath::vec3(lightR, lightG, lightB),
							  vmath::vec3(cloudOffsetX, cloudOffsetY, cloudOffsetZ),
							  vmath::vec4(forwardScatter, backwardScatter, baseBrightness, strength));

		triangle->Display();

		cprogram->StopProgram();
		glDisable(GL_BLEND);
		glDepthMask(GL_TRUE);
	}
}

void VolumetricClouds::RenderIMGUI()
{
	// Code
	// ImGui::Begin("Values");

	ImGui::BeginGroup();
	{
		ImGui::Checkbox("Red Channel", &redChannel);
		ImGui::SliderInt("redScaleA", &redScaleA, 0, 100);
		ImGui::SliderInt("redScaleB", &redScaleB, 0, 100);
		ImGui::SliderInt("redScaleC", &redScaleC, 0, 100);
		ImGui::SliderFloat("redPersistence", &redpersistence, 0, 1);

		ImGui::Checkbox("Green Channel", &greenChannel);
		ImGui::SliderInt("greenScaleA", &greenScaleA, 0, 100);
		ImGui::SliderInt("greenScaleB", &greenScaleB, 0, 100);
		ImGui::SliderInt("greenScaleC", &greenScaleC, 0, 100);
		ImGui::SliderFloat("greenPersistence", &greenpersistence, 0, 1);

		ImGui::Checkbox("Blue Channel", &blueChannel);
		ImGui::SliderInt("blueScaleA", &blueScaleA, 0, 100);
		ImGui::SliderInt("blueScaleB", &blueScaleB, 0, 100);
		ImGui::SliderInt("blueScaleC", &blueScaleC, 0, 100);
		ImGui::SliderFloat("bluePersistence", &bluepersistence, 0, 1);

		ImGui::SliderFloat("r weight", &redWeight, 0.0, 10.0);
		ImGui::SliderFloat("g weight", &greenWeight, 0.0, 10.0);
		ImGui::SliderFloat("b weight", &blueWeight, 0.0, 10.0);
		ImGui::SliderFloat("a weight", &alphaWeight, 0.0, 10.0);
	}
	ImGui::EndGroup();

	ImGui::SliderFloat("cloudOffsetX", &cloudOffsetX, 0, 100);
	ImGui::SliderFloat("cloudOffsetY", &cloudOffsetY, 0, 100);
	ImGui::SliderFloat("cloudOffsetZ", &cloudOffsetZ, 0, 100);

	// ImGui::SameLine();

	ImGui::SliderInt("numStepsLight", &numStepsLight, 0, 100);

	ImGui::SliderFloat("CloudScale", &cloudScale, 0, 1);
	ImGui::SliderFloat("TimeScale", &timeScale, 0, 1);

	ImGui::SliderFloat("x_pos", &xpos, 0, 10000);
	ImGui::SliderFloat("y_pos", &ypos, 0, 10000);
	ImGui::SliderFloat("z_pos", &zpos, 0, 10000);

	ImGui::SliderFloat("boundX", &boundsScaleX, 0, 100000);
	ImGui::SliderFloat("boundY", &boundsScaleY, 0, 100000);
	ImGui::SliderFloat("boundZ", &boundsScaleZ, 0, 100000);

	ImGui::SliderFloat("densityOffset", &densityOffset, -10, 10);
	ImGui::SliderFloat("lightAbsorptionThroughCloud", &lightAbsorptionThroughCloud, 0.0, 10);
	ImGui::SliderFloat("lightAbsorptionTowardSun", &lightAbsorptionTowardSun, 0.0, 10);
	ImGui::SliderFloat("darknessThreshold", &darknessThreshold, 0.0, 1);

	ImGui::SliderFloat("topFadeStart", &topFadeStart, 0.0, 1.0);
	ImGui::SliderFloat("topFadeEnd", &topFadeEnd, 0.0, 1.0);
	ImGui::SliderFloat("bottomFadeStart", &bottomFadeStart, 0.0, 1.0);
	ImGui::SliderFloat("bottomFadeEnd", &bottomFadeEnd, 0.0, 1.0);

	ImGui::BeginGroup();
	{
		ImGui::Checkbox("Red Detail Channel", &redDetailChannel);
		ImGui::SliderInt("rDetailScaleA", &redDetailScaleA, 0, 100);
		ImGui::SliderInt("rDetailScaleB", &redDetailScaleB, 0, 100);
		ImGui::SliderInt("rDetailScaleC", &redDetailScaleC, 0, 100);
		ImGui::SliderFloat("rDetailPersistence", &redDetailpersistence, 0, 1);

		ImGui::Checkbox("Green Detail Channel", &greenDetailChannel);
		ImGui::SliderInt("gDetailScaleA", &greenDetailScaleA, 0, 100);
		ImGui::SliderInt("gDetailScaleB", &greenDetailScaleB, 0, 100);
		ImGui::SliderInt("gDetailScaleC", &greenDetailScaleC, 0, 100);
		ImGui::SliderFloat("gDetailPersistence", &greenDetailpersistence, 0, 1);

		ImGui::Checkbox("Blue Detail Channel", &blueDetailChannel);
		ImGui::SliderInt("bDetailScaleA", &blueDetailScaleA, 0, 100);
		ImGui::SliderInt("bDetailScaleB", &blueDetailScaleB, 0, 100);
		ImGui::SliderInt("bDetailScaleC", &blueDetailScaleC, 0, 100);
		ImGui::SliderFloat("bDetailPersistence", &blueDetailpersistence, 0, 1);

		ImGui::SliderFloat("rDetailweight", &redDetailWeight, 0.0, 1.0);
		ImGui::SliderFloat("gDetailweight", &greenDetailWeight, 0.0, 1.0);
		ImGui::SliderFloat("bDetailweight", &blueDetailWeight, 0.0, 1.0);
		ImGui::SliderFloat("aDetailweight", &alphaDetailWeight, 0.0, 1.0);

		ImGui::SliderFloat("detailOffset", &detailOffset, 0.0, 10.0);
		ImGui::SliderFloat("detailNoiseScale", &detailNoiseScale, 0.0, 10.0);
		ImGui::SliderFloat("detailNoiseWeight", &detailNoiseWeight, 0.0, 10.0);
	}
	ImGui::EndGroup();

	ImGui::SliderFloat("lightX", &lightX, -10000.0, 10000.0);
	ImGui::SliderFloat("lightY", &lightY, -10000.0, 10000.0);
	ImGui::SliderFloat("lightZ", &lightZ, -10000.0, 10000.0);

	ImGui::SliderFloat("lightR", &lightR, 0.0, 1.0);
	ImGui::SliderFloat("lightG", &lightG, 0.0, 1.0);
	ImGui::SliderFloat("lightB", &lightB, 0.0, 1.0);

	ImGui::SliderFloat("forwardScatter", &forwardScatter, 0.0, 10.0);
	ImGui::SliderFloat("backwardScatter", &backwardScatter, 0.0, 10.0);
	ImGui::SliderFloat("baseBrightness", &baseBrightness, 0.0, 10.0);
	ImGui::SliderFloat("strength", &strength, 0.0, 1.0);

	static char inpFileName[256];

	ImGui::InputText("File Name", inpFileName, 256);

	ImGui::SameLine();

	if (ImGui::Button("Save To File", ImVec2(100, 30)))
	{
		SaveCloudSettings(std::string(inpFileName));
	}

	// ImGui::End();
}

void VolumetricClouds::SaveCloudSettings(std::string filename)
{
	std::ofstream file(filename);

	if (!file.is_open())
	{
		MessageBox(NULL, TEXT("File Not Open"), TEXT("MSGBOX"), MB_OK);
		return;
	}

	file << "xpos=" << xpos << '\n';
	file << "ypos=" << ypos << '\n';
	file << "zpos=" << zpos << '\n';

	file << "boundsScaleX=" << boundsScaleX << '\n';
	file << "boundsScaleY=" << boundsScaleY << '\n';
	file << "boundsScaleZ=" << boundsScaleZ << '\n';

	file << "zSlice=" << zSlice << '\n';

	file << "redChannel=" << redChannel << '\n';
	file << "redScaleA=" << redScaleA << '\n';
	file << "redScaleB=" << redScaleB << '\n';
	file << "redScaleC=" << redScaleC << '\n';
	file << "redPersistence=" << redpersistence << '\n';

	file << "greenChannel=" << greenChannel << '\n';
	file << "greenScaleA=" << greenScaleA << '\n';
	file << "greenScaleB=" << greenScaleB << '\n';
	file << "greenScaleC=" << greenScaleC << '\n';
	file << "greenPersistence=" << greenpersistence << '\n';

	file << "blueChannel=" << blueChannel << '\n';
	file << "blueScaleA=" << blueScaleA << '\n';
	file << "blueScaleB=" << blueScaleB << '\n';
	file << "blueScaleC=" << blueScaleC << '\n';
	file << "bluePersistence=" << bluepersistence << '\n';

	file << "redWeight=" << redWeight << '\n';
	file << "greenWeight=" << greenWeight << '\n';
	file << "blueWeight=" << blueWeight << '\n';
	file << "alphaWeight=" << alphaWeight << '\n';

	file << "densityMultiplier=" << densityMultiplier << '\n';
	file << "densityOffset=" << densityOffset << '\n';
	file << "cloudScale=" << cloudScale << '\n';

	file << "redDetailChannel=" << redDetailChannel << '\n';
	file << "redDetailScaleA=" << redDetailScaleA << '\n';
	file << "redDetailScaleB=" << redDetailScaleB << '\n';
	file << "redDetailScaleC=" << redDetailScaleC << '\n';
	file << "redDetailPersistence=" << redDetailpersistence << '\n';

	file << "greenDetailChannel=" << greenDetailChannel << '\n';
	file << "greenDetailScaleA=" << greenDetailScaleA << '\n';
	file << "greenDetailScaleB=" << greenDetailScaleB << '\n';
	file << "greenDetailScaleC=" << greenDetailScaleC << '\n';
	file << "greenDetailPersistence=" << greenDetailpersistence << '\n';

	file << "blueDetailChannel=" << blueDetailChannel << '\n';
	file << "blueDetailScaleA=" << blueDetailScaleA << '\n';
	file << "blueDetailScaleB=" << blueDetailScaleB << '\n';
	file << "blueDetailScaleC=" << blueDetailScaleC << '\n';
	file << "blueDetailPersistence=" << blueDetailpersistence << '\n';

	file << "detailOffset=" << detailOffset << '\n';
	file << "detailNoiseScale=" << detailNoiseScale << '\n';
	file << "detailNoiseWeight=" << detailNoiseWeight << '\n';

	file << "redDetailWeight=" << redDetailWeight << '\n';
	file << "greenDetailWeight=" << greenDetailWeight << '\n';
	file << "blueDetailWeight=" << blueDetailWeight << '\n';
	file << "alphaDetailWeight=" << alphaDetailWeight << '\n';

	file << "bottomFadeStart=" << bottomFadeStart << '\n';
	file << "bottomFadeEnd=" << bottomFadeEnd << '\n';
	file << "topFadeStart=" << topFadeStart << '\n';
	file << "topFadeEnd=" << topFadeEnd << '\n';

	file << "numStepsLight=" << numStepsLight << '\n';

	file << "timeScale=" << timeScale << '\n';

	file << "lightAbsorptionThroughCloud=" << lightAbsorptionThroughCloud << '\n';
	file << "lightAbsorptionTowardSun=" << lightAbsorptionTowardSun << '\n';
	file << "darknessThreshold=" << darknessThreshold << '\n';

	file << "lightX=" << lightX << '\n';
	file << "lightY=" << lightY << '\n';
	file << "lightZ=" << lightZ << '\n';

	file << "lightR=" << lightR << '\n';
	file << "lightG=" << lightG << '\n';
	file << "lightB=" << lightB << '\n';

	file << "forwardScatter=" << forwardScatter << '\n';
	file << "backwardScatter=" << backwardScatter << '\n';
	file << "baseBrightness=" << baseBrightness << '\n';
	file << "strength=" << strength << '\n';

	file << "cloudOffsetX=" << cloudOffsetX << '\n';
	file << "cloudOffsetY=" << cloudOffsetY << '\n';
	file << "cloudOffsetZ=" << cloudOffsetZ << '\n';

	file.close();
}

void VolumetricClouds::Uninitialize()
{
	// Code
	if (basicFbo)
	{
		basicFbo->Uninitialize();
		delete basicFbo;
		basicFbo = NULL;
	}

	if (basicCloud)
	{
		basicCloud->Uninitialize();
		delete basicCloud;
		basicCloud = NULL;
	}

	if (detailCloud)
	{
		detailCloud->Uninitialize();
		delete detailCloud;
		detailCloud = NULL;
	}

	if (cprogram)
	{
		cprogram->Uninitialize();
		delete cprogram;
		cprogram = NULL;
	}

	if (triangle)
	{
		triangle->Uninitialize();
		delete triangle;
		triangle = NULL;
	}
}
