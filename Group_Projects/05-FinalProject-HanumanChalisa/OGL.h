#pragma once

#ifndef RC_INVOKED
#include <windows.h>
#include "./modules/Model/Model.h"
#endif

struct ShadowEssentials
{
	float lightX;
	float lightY;
	float lightZ;
	int shadowPower;
	float shadowX;
	float shadowY;
	float shadowZ;
};

#define MYICON 101

// Global variable declarations (shared across files)
#ifndef RC_INVOKED
extern HWND ghwnd;
extern Model *gpSabhaMandapModel;
extern Model *gpFirePotModel;
extern Model *gpMinisterChairModel;
extern Model *gpPillarModel;
extern Model *gpThroneModel;
extern Model *gpHanumanJiModel;
extern Model *gpVibhishanModel;
extern Model *gpRamVachan_TerrainModel;
extern Model *gpRamVachan_RamWithHanuman;
extern Model *gpRamVachan_Trees;
extern Model *gpTerrainWithCave;
extern Model *gpTreesOnFirstTerrain;
extern Model *gpMountain;
extern Model *gpSideMountain;
extern Model *gpHanumanOnMountain;
extern Model *gpYuddhaScene1Platform;
extern Model *gpAsurSena;
extern Model *gpHanumanJiInYuddha_one;
extern Model *gpAsurPlatform;
extern Model *gpHanumanJi_Prahar;
extern Model *gpHanumanJi_FlyingModel;

extern Model *gpModelsOnLastTerrain[RAM_WORSHIP_MODELS_SIZE];
extern Model *gpYudhaScene2Models[YUDDHA_SCENE2_MODELS_SIZE];
extern Model *gpCaveInteriorModels[CAVE_INTERIOR_MODELS_SIZE];

extern ModelParams gpWorshipModelParams[RAM_WORSHIP_MODELS_SIZE];
extern ModelParams gpYudhaScene2Params[YUDDHA_SCENE2_MODELS_SIZE];
extern ModelParams gpCaveInteriorParams[CAVE_INTERIOR_MODELS_SIZE];

// Function declarations
void initializeModelsConfig(void);

// ImGui Configuration Functions
void initializeImGui(void);
void displayImGui(void);
void uninitializeImGui(void);
#endif
