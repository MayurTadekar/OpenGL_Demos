#include <windows.h>
#include "OGL.h"
#include "./modules/Model/Model.h"

// Global Model Pointer Definitions
Model *gpTerrainWithCave = NULL;
Model *gpTreesOnFirstTerrain = NULL;
Model *gpSabhaMandapModel = NULL;
Model *gpFirePotModel = NULL;
Model *gpMinisterChairModel = NULL;
Model *gpPillarModel = NULL;
Model *gpThroneModel = NULL;
Model *gpHanumanJiModel = NULL;
Model *gpVibhishanModel = NULL;
Model *gpRamVachan_TerrainModel = NULL;
Model *gpRamVachan_RamWithHanuman = NULL;
Model *gpRamVachan_Trees = NULL;
Model *gpMountain = NULL;
Model *gpSideMountain = NULL;
Model *gpHanumanOnMountain = NULL;
Model *gpYuddhaScene1Platform = NULL;
Model *gpAsurSena = NULL;
Model *gpHanumanJiInYuddha_one = NULL;
Model *gpAsurPlatform = NULL;
Model *gpHanumanJi_Prahar = NULL;
Model *gpHanumanJi_FlyingModel = NULL;
Model *gpOceanSceneBirdModel = NULL;

Model *gpModelsOnLastTerrain[RAM_WORSHIP_MODELS_SIZE];
Model *gpYudhaScene2Models[YUDDHA_SCENE2_MODELS_SIZE];
Model *gpCaveInteriorModels[CAVE_INTERIOR_MODELS_SIZE];

// Global models parameter struct Array (Definitions moved from OGL.cpp)
ModelParams gpWorshipModelParams[RAM_WORSHIP_MODELS_SIZE] = {0};
ModelParams gpYudhaScene2Params[YUDDHA_SCENE2_MODELS_SIZE] = {0};
ModelParams gpCaveInteriorParams[CAVE_INTERIOR_MODELS_SIZE] = {0};

void initializeModelsConfig(void)
{
    // cave interior models paramarters initilization
    gpCaveInteriorParams[0].translation = vmath::vec3(0.0f, 0.0f, 0.0f);
    gpCaveInteriorParams[0].scale = vmath::vec3(1.0f, 1.0f, 1.0f);

    // cave interior models paramarters initilization
    gpCaveInteriorParams[1].translation = vmath::vec3(0.0f, 0.0f, 0.0f);
    gpCaveInteriorParams[1].scale = vmath::vec3(1.0f, 1.0f, 1.0f);

    // worshipscene models paramarters initilization Gulmohor Tree
    gpWorshipModelParams[0].translation = vmath::vec3(0.0f, 0.0f, 0.0f);
    gpWorshipModelParams[0].scale = vmath::vec3(1.0f, 1.0f, 1.0);

    //***************** worshipscene models paramarters initilization For Mango Tree******************
    // worshipscene models paramarters initilization//
    gpWorshipModelParams[1].translation = vmath::vec3(0.0f, 0.0f, 0.0f);
    gpWorshipModelParams[1].scale = vmath::vec3(1.0f, 1.0f, 1.0f);

    // Last Sceene Hanuman
    gpWorshipModelParams[3].translation = vmath::vec3(0.0f, 0.0f, 0.0f);
    gpWorshipModelParams[3].scale = vmath::vec3(1.0f, 1.0f, 1.0f);

    // Last Sceene Ram
    gpWorshipModelParams[2].translation = vmath::vec3(327.56f, 34.46f, -7.42f);
    gpWorshipModelParams[2].scale = vmath::vec3(1.0f, 1.0f, 1.0f);

    //************************************************************************************* */

    // YuddhaScene2 paramarters initilization		// Asu nikandan Terrain
    gpYudhaScene2Params[0].translation = vmath::vec3(0.0f, 0.0f, 0.0f);
    gpYudhaScene2Params[0].scale = vmath::vec3(1.0f, 1.0f, 1.0);

    // Yuddh Scene2 paramarters initilization
    gpYudhaScene2Params[1].translation = vmath::vec3(0.0f, 0.0f, 0.0f);
    gpYudhaScene2Params[1].scale = vmath::vec3(1.0f, 1.0f, 1.0f);

    // Sabhamandap Scene Models
    SetWindowTextA(ghwnd, "Importing SabhaMandapModel Model");
    gpSabhaMandapModel = importModel("./resources/Models/02-SabhaMandapScene/01-SabhaMandap/Sabhamandap.gltf", "SabhaMandapModel", false);

    SetWindowTextA(ghwnd, "Importing fire_pot Model");
    gpFirePotModel = importModel("./resources/Models/02-SabhaMandapScene/05_FirePot/fire_pot.gltf", "fire_pot", false);

    SetWindowTextA(ghwnd, "Importing MinisterChair Model");
    gpMinisterChairModel = importModel("./resources/Models/02-SabhaMandapScene/06_MinisterChair/MinisterChair.gltf", "MinisterChair", false);

    SetWindowTextA(ghwnd, "Importing Pillars Model");
    gpPillarModel = importModel("./resources/Models/02-SabhaMandapScene/07_Pillars/pillars.gltf", "Pillars", false);

    SetWindowTextA(ghwnd, "Importing SabhaMandap Throne Model");
    gpThroneModel = importModel("./resources/Models/02-SabhaMandapScene/02-Throne/Throne.gltf", "ThroneModel", false);

    SetWindowTextA(ghwnd, "Importing HanumanJi_inVibhishanScene Model");
    gpHanumanJiModel = importModel("./resources/Models/03_HanumanJi/01_InVibhishanScene/HanumanJi_inVibhishanScene.gltf", "HanumanJiModel", true);

    SetWindowTextA(ghwnd, "Importing VibhishanModel Model");
    gpVibhishanModel = importModel("./resources/Models/02-SabhaMandapScene/04-Vibhishan/Vibhishan.gltf", "VibhishanModel", false);

    // RamVacahan Scene Models
    SetWindowTextA(ghwnd, "Importing RamVachanSceneModel_Terrain Model");
    gpRamVachan_TerrainModel = importModel("./resources/Models/05_Ram_Vachan/01-Terrain/Terrain.gltf", "RamVachanSceneModel_Terrain", false);

    SetWindowTextA(ghwnd, "Importing RamVachanSceneModel_RamWithHanuman Model");
    gpRamVachan_RamWithHanuman = importModel("./resources/Models/05_Ram_Vachan/03_RamAndHanuman/ram_and_hanuman.gltf", "RamVachanSceneModel_RamWithHanuman", false);

    SetWindowTextA(ghwnd, "Importing RamVachanSceneModel_Trees Model");
    gpRamVachan_Trees = importModel("./resources/Models/05_Ram_Vachan/04_RamVachanTrees/trees.gltf", "RamVachanSceneModel_Trees", false);

    SetWindowTextA(ghwnd, "Importing TerrainWithCave Model");
    gpTerrainWithCave = importModel("./resources/Models/01_MountainExterriorScene/01_TerrainWithCave/TerrainWithCave.gltf", "TerrainWithCave", false);

    SetWindowTextA(ghwnd, "Importing TreesOnTerrain Model");
    gpTreesOnFirstTerrain = importModel("./resources/Models/01_MountainExterriorScene/02_TreesOnTerrain/TreesOnTerrain.gltf", "TerrainWithCave", false);

    // Mountain Peak
    SetWindowTextA(ghwnd, "Importing SnowPeak Model");
    LOG_ENTRY("log.txt", "Importing SnowPeak Model");
    gpMountain = importModel("./resources/Models/06_SnowPeak/SnowPeak.gltf", "Mountain", false);

    SetWindowTextA(ghwnd, "Importing SideMountain Model");
    LOG_ENTRY("log.txt", "Importing SideMountain Model");
    gpSideMountain = importModel("./resources/Models/06_SnowPeak/side_mountain.gltf", "SideMountain", false);

    SetWindowTextA(ghwnd, "Importing HanumanOnMountain Model");
    LOG_ENTRY("log.txt", "Importing HanumanOnMountain Model");
    gpHanumanOnMountain = importModel("./resources/Models/03_HanumanJi/02_HanumanJiOnMountPeak/HanumanJi_OnMountainPeak.gltf", "HanumanOnMountain", true);

    // Yudha Scene 1 Models
    SetWindowTextA(ghwnd, "Importing Lanka platform");
    gpYuddhaScene1Platform = importModel("./resources/Models/07_Yuddha_Scene/Scene1/Asur_Lanka_Platform/Asur_Lanka_Platform.gltf", "LankaPlatform", false);

    SetWindowTextA(ghwnd, "Importing AsurSena");
    gpAsurSena = importModel("./resources/Models/07_Yuddha_Scene/Scene1/Asur/Asur.gltf", "AsurSena", false);

    SetWindowTextA(ghwnd, "Importing Gada Model");
    gpHanumanJiInYuddha_one = importModel("./resources/Models/07_Yuddha_Scene/Scene1/HanumanJiInYudha_one/HanumanJiInYuddha_one.gltf", "Gada", false);

    SetWindowTextA(ghwnd, "Importing Flying Model");
    gpHanumanJi_FlyingModel = importModel("./resources/Models/03_HanumanJi/03_HanumanJi_Flying/HanumanJi_Flying.gltf", "FlyingModel", false);

    SetWindowTextA(ghwnd, "Importing Bird Model");
    gpOceanSceneBirdModel = importModel("./resources/Models/Birds/1-OceanSceneBird/scene.gltf", "Bird", false);

    // SCENE_CaveInterior
    SetWindowTextA(ghwnd, "Importing Cave Interior Model");
    gpCaveInteriorModels[0] = importModel("./resources/Models/09_CaveInteriorScene/01_Cave/Cave.gltf", "CaveInterior");
    gpCaveInteriorModels[1] = importModel("./resources/Models/09_CaveInteriorScene/02_HanumanCave/HanumanCave.gltf", "CaveInteriorHanuman", false);

    // SCENE_YUDDHA2
    SetWindowTextA(ghwnd, "Importing Yuddha Scene 2 Model");
    gpYudhaScene2Models[0] = importModel("./resources/Models/07_Yuddha_Scene/Scene2/Asur_Platform/Asur_Platform.gltf", "AsurPlatform", false);
    gpYudhaScene2Models[1] = importModel("./resources/Models/07_Yuddha_Scene/Scene2/HanumanJi_Prahar/HanumanJi_Prahar.gltf", "HanumanJiPrahar", false);

    // SCENE_RAM_WORSHIP
    SetWindowTextA(ghwnd, "Importing TreesOnLastTerrain Model");
    gpModelsOnLastTerrain[0] = importModel("./resources/Models/10-RamWorkshipScene/03-Trees/Trees.gltf", "TreesOnLastTerrain", false);
    SetWindowTextA(ghwnd, "Importing AnimalsTrees Model");
    gpModelsOnLastTerrain[1] = importModel("./resources/Models/10-RamWorkshipScene/04-Animals/AnimalTrees.gltf", "AnimalsTrees", false);
    SetWindowTextA(ghwnd, "Importing LastSceneRam Model");
    gpModelsOnLastTerrain[2] = importModel("./resources/Models/10-RamWorkshipScene/01-Ram/Ram.gltf", "LastSceneRam", false);
    SetWindowTextA(ghwnd, "Importing LastSceneHanuman Model");
    gpModelsOnLastTerrain[3] = importModel("./resources/Models/03_HanumanJi/04_HanumanJiInlastScene/HanumanJiPranam.gltf", "LastSceneHanuman", false);

    SetWindowTextA(ghwnd, "Imported All Models Successfully!");
}
