/***************************************************************************
 * S.G.M.P
 * @file: VolumetricClouds.hpp
 * @brief:
 * @author: Mayur S. Tadekar(mrtadekar@gmail.com)
 * @copyright ©2020-2025 MarshallingVoid
 * @date: Thursday 2026-06-04 12:57:20 PM
 ***************************************************************************/

#ifndef _VOLUMETRIC_CLOUDS_HPP
#define _VOLUMETRIC_CLOUDS_HPP

#include <fstream>
#include <string>
#include <unordered_map>

#include "CloudProgram.h"

#include "FrameBufferObjectWithDepth.h"
#include "ComputeShader.hpp"

#include "triangle.h"

#include "./../../../modules/imgui/imgui.h"
#include "./../../../modules/imgui/imgui_impl_win32.h"
#include "./../../../modules/imgui/imgui_impl_opengl3.h"

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

class VolumetricClouds
{
private:
	ComputeShader *basicCloud = nullptr;
	ComputeShader *detailCloud = nullptr;
	CloudsProgram *cprogram = nullptr;
	FrameBufferObjectWithDepth *basicFbo = nullptr;
	Triangle *triangle = NULL;

	float xpos;
	float ypos;
	float zpos;

	float boundsScaleX;
	float boundsScaleY;
	float boundsScaleZ;

	float zSlice;

	bool redChannel;
	int redScaleA;
	int redScaleB;
	int redScaleC;
	float redpersistence;

	bool greenChannel;
	int greenScaleA;
	int greenScaleB;
	int greenScaleC;
	float greenpersistence;

	bool blueChannel;
	int blueScaleA;
	int blueScaleB;
	int blueScaleC;
	float bluepersistence;

	float redWeight;
	float greenWeight;
	float blueWeight;
	float alphaWeight;

	float densityMultiplier;
	float densityOffset;
	float cloudScale;

	bool redDetailChannel;
	int redDetailScaleA;
	int redDetailScaleB;
	int redDetailScaleC;
	float redDetailpersistence;

	bool greenDetailChannel;
	int greenDetailScaleA;
	int greenDetailScaleB;
	int greenDetailScaleC;
	float greenDetailpersistence;

	bool blueDetailChannel;
	int blueDetailScaleA;
	int blueDetailScaleB;
	int blueDetailScaleC;
	float blueDetailpersistence;

	float detailOffset;
	float detailNoiseScale;
	float detailNoiseWeight;

	float redDetailWeight;
	float greenDetailWeight;
	float blueDetailWeight;
	float alphaDetailWeight;

	float bottomFadeStart;
	float bottomFadeEnd;
	float topFadeStart;
	float topFadeEnd;

	int numStepsLight;

	float timeScale;

	float lightAbsorptionThroughCloud;
	float lightAbsorptionTowardSun;
	float darknessThreshold;

	float lightX;
	float lightY;
	float lightZ;

	float lightR;
	float lightG;
	float lightB;

	float forwardScatter;
	float backwardScatter;
	float baseBrightness;
	float strength;

	float cloudOffsetX;
	float cloudOffsetY;
	float cloudOffsetZ;

public:
	VolumetricClouds();
	VolumetricClouds(const char *filename);

	std::unordered_map<std::string, std::string> LoadSettings(const char *filename);

	float GetFloat(const std::unordered_map<std::string, std::string> &settings,
				   const std::string &key,
				   float defaultValue = 0.0f);

	int GetInt(const std::unordered_map<std::string, std::string> &settings,
			   const std::string &key,
			   int defaultValue = 0);

	bool GetBool(const std::unordered_map<std::string, std::string> &settings,
				 const std::string &key,
				 bool defaultValue = false);

	void Resize(int width, int height);

	void RenderCloudTextures();

	void StartRenderingToFBO();
	void StopRenderingToFBO();

	void SaveCloudSettings(std::string filename);

	void Display(vmath::mat4 &projectionMatrix,
				 vmath::mat4 &modelMatrix,
				 vmath::mat4 &viewMatrix,
				 vmath::vec3 cameraPosition,
				 float time);
	void RenderIMGUI();

	void Uninitialize();
};


#endif /* _VOLUMETRIC_CLOUDS_HPP */
