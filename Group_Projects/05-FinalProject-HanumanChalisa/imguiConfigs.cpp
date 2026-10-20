#include <windows.h>
#include "OGL.h"
#include "./modules/imgui/imgui.h"
#include "./modules/imgui/imgui_impl_win32.h"
#include "./modules/imgui/imgui_impl_opengl3.h"

#include "./effects/SceneLighting/SceneLighting.h"
#include "./effects/Skydome/Skydome.h"
#include "./effects/Snowfall/Snowfall.h"
#include "./effects/GodRays/GodRays.h"
#include "./effects/Ocean-2/effects/Ocean/Ocean.h"
#include "./effects/Water/Water.h"
#include "./effects/FogEffect/FogEffect.h"
#include "./effects/MayursEffects/SingleLightProgram/SingleLightProgram.h"
#include "./effects/MayursEffects/VolumetricClouds/VolumetricClouds.hpp"

// External globals used in ImGui controls
extern float mountainPeakLightX;
extern float mountainPeakLightY;
extern float mountainPeakLightZ;
extern struct ShadowEssentials hanumanShadow;
extern struct ShadowEssentials vibhishanShadow;
extern struct ShadowEssentials fireKundShadow;
extern struct ShadowEssentials ministerChairShadow;
extern struct ShadowEssentials pillarShadow;
extern float hanumanPosX;
extern float hanumanPosY;
extern float hanumanPosZ;
extern struct ShadowEssentials ramVachanShadow;
extern struct ShadowEssentials asurShadow;
extern struct ShadowEssentials hanumanYuddha01Shadow;
extern struct ShadowEssentials ramVachanTreeShadow;
// extern struct ShadowEssentials ramworshipAnimalShadow;
extern SingleLightProgram *mountainPeakProgram;
extern SceneLightParams caveInteriorScene_HanumajiLights;
extern SceneLightParams sabhamandapScene_ThroneLights;
extern SceneLightParams sabhamandapScene_HanumajiLights;
extern SceneLightParams generalHanumanJiLights;
extern SceneLightParams flyingHanumanJiLights;
extern SceneLightParams sabhamandapScene_VibhishanLights;
extern SceneLightParams ramvachanLights;
extern SkydomeParams skydomeParams[5];
extern SnowfallParams snowfallParams;
extern GodRaysParams godRaysParams;
extern GodRaysParams godRaysParamsForRamWorship;
extern WaterParams waterParams[2];
extern OceanParams oceanParams;
extern OceanParams gOcean;
extern vmath::vec3 hanumanOnMountainLightpos;
extern float radiance;
extern float emmissiveStrength;
extern std::vector<vmath::vec3> positionsMountainPeakScene;
extern std::vector<vmath::vec3> positionsYuddhaScene1;
extern float flyingY;

extern VolumetricClouds *volumetriccloudsForPeakScene;
extern VolumetricClouds *volumetriccloudsForFlyingScene;
extern VolumetricClouds *volumetriccloudsForYuddhaScene;
extern VolumetricClouds *volumetriccloudsForOcean;

extern float hanumanOceanXPos;
extern float hanumanOceanYPos;
extern float hanumanOceanZPos;
extern float hanumanOceanXFactor;

void initializeImGui(void)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplWin32_Init(ghwnd);
    ImGui_ImplOpenGL3_Init("#version 460 core");
}

void displayImGui(void)
{
    // code
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Demo Scene Editor");

    if (ImGui::CollapsingHeader("Mountain Peak Light Pos"))
    {
        ImGui::DragFloat("LX", &mountainPeakLightX, 0.1f);
        ImGui::DragFloat("LY", &mountainPeakLightY, 0.1f);
        ImGui::DragFloat("LZ", &mountainPeakLightZ, 0.1f);

        mountainPeakProgram->SetLightPosition(vmath::vec3(mountainPeakLightX, mountainPeakLightY, mountainPeakLightZ));
    }

    if (ImGui::CollapsingHeader("Asur Shadow"))
    {

        ImGui::DragFloat("asurShadowLX", &asurShadow.lightX, 0.1f);
        ImGui::DragFloat("asurShadowLY", &asurShadow.lightY, 0.1f);
        ImGui::DragFloat("asurShadowLZ", &asurShadow.lightZ, 0.1f);
        ImGui::DragInt("asurPower", &asurShadow.shadowPower);

        ImGui::DragFloat("asurShadowX", &asurShadow.shadowX, 0.1f);
        ImGui::DragFloat("asurShadowY", &asurShadow.shadowY, 0.1f);
        ImGui::DragFloat("asurShadowZ", &asurShadow.shadowZ, 0.1f);
    }

    if (ImGui::CollapsingHeader("HanumanYuddha 01 Shadow"))
    {

        ImGui::DragFloat("hanumanYuddha01ShadowLX", &hanumanYuddha01Shadow.lightX, 0.1f);
        ImGui::DragFloat("hanumanYuddha01ShadowLY", &hanumanYuddha01Shadow.lightY, 0.1f);
        ImGui::DragFloat("hanumanYuddha01ShadowLZ", &hanumanYuddha01Shadow.lightZ, 0.1f);
        ImGui::DragInt("hanumanYuddha01ShadowPower", &hanumanYuddha01Shadow.shadowPower);

        ImGui::DragFloat("hanumanYuddha01ShadowX", &hanumanYuddha01Shadow.shadowX, 0.1f);
        ImGui::DragFloat("hanumanYuddha01ShadowY", &hanumanYuddha01Shadow.shadowY, 0.1f);
        ImGui::DragFloat("hanumanYuddha01ShadowZ", &hanumanYuddha01Shadow.shadowZ, 0.1f);
    }

    if (ImGui::CollapsingHeader("Ramvachan Shadow"))
    {

        ImGui::DragFloat("rvShadowLX", &ramVachanShadow.lightX, 0.1f);
        ImGui::DragFloat("rvShadowLY", &ramVachanShadow.lightY, 0.1f);
        ImGui::DragFloat("rvShadowLZ", &ramVachanShadow.lightZ, 0.1f);
        ImGui::DragInt("rvPower", &ramVachanShadow.shadowPower);

        ImGui::DragFloat("rvShadowX", &ramVachanShadow.shadowX, 0.1f);
        ImGui::DragFloat("rvShadowY", &ramVachanShadow.shadowY, 0.1f);
        ImGui::DragFloat("rvShadowZ", &ramVachanShadow.shadowZ, 0.1f);
    }

    // if (ImGui::CollapsingHeader("Ramworship Animals Shadow"))
    // {

    //     ImGui::DragFloat("animalShadowLX", &ramworshipAnimalShadow.lightX, 0.1f);
    //     ImGui::DragFloat("animalShadowLY", &ramworshipAnimalShadow.lightY, 0.1f);
    //     ImGui::DragFloat("animalShadowLZ", &ramworshipAnimalShadow.lightZ, 0.1f);
    //     ImGui::DragInt("animalPower", &ramworshipAnimalShadow.shadowPower);

    //     ImGui::DragFloat("animalShadowPX", &ramworshipAnimalShadow.shadowX, 0.1f);
    //     ImGui::DragFloat("animalShadowPY", &ramworshipAnimalShadow.shadowY, 0.1f);
    //     ImGui::DragFloat("animalShadowPZ", &ramworshipAnimalShadow.shadowZ, 0.1f);
    // }

    if (ImGui::CollapsingHeader("Ramvachan Tree Shadow"))
    {

        ImGui::DragFloat("rtShadowLX", &ramVachanTreeShadow.lightX, 0.1f);
        ImGui::DragFloat("rtShadowLY", &ramVachanTreeShadow.lightY, 0.1f);
        ImGui::DragFloat("rtShadowLZ", &ramVachanTreeShadow.lightZ, 0.1f);
        ImGui::DragInt("rtPower", &ramVachanTreeShadow.shadowPower);

        ImGui::DragFloat("rtShadowX", &ramVachanTreeShadow.shadowX, 0.1f);
        ImGui::DragFloat("rtShadowY", &ramVachanTreeShadow.shadowY, 0.1f);
        ImGui::DragFloat("rtShadowZ", &ramVachanTreeShadow.shadowZ, 0.1f);
    }

    if (ImGui::CollapsingHeader("Hanuman PosX"))
    {
        ImGui::DragFloat("hanumanPosX", &hanumanPosX, 0.1f);
        ImGui::DragFloat("hanumanPosY", &hanumanPosY, 0.1f);
        ImGui::DragFloat("hanumanPosZ", &hanumanPosZ, 0.1f);
    }

    if (ImGui::CollapsingHeader("HanumanOnMountainLightpos PosX"))
    {
        ImGui::DragFloat("hanumanOnMPosX", &hanumanOnMountainLightpos[0], 0.1f);
        ImGui::DragFloat("hanumanOnMPosY", &hanumanOnMountainLightpos[1], 0.1f);
        ImGui::DragFloat("hanumanOnMPosZ", &hanumanOnMountainLightpos[2], 0.1f);

        ImGui::DragFloat("radiance", &radiance, 0.1f);
        ImGui::DragFloat("emmissiveStrength", &emmissiveStrength, 0.1f);
    }

    if (ImGui::CollapsingHeader("Shadow Editor"))
    {
        ImGui::DragFloat("fkShadowLX", &fireKundShadow.lightX, 0.1f);
        ImGui::DragFloat("fkShadowLY", &fireKundShadow.lightY, 0.1f);
        ImGui::DragFloat("fkShadowLZ", &fireKundShadow.lightZ, 0.1f);
        ImGui::DragInt("fkPower", &fireKundShadow.shadowPower);

        ImGui::DragFloat("fkShadowX", &fireKundShadow.shadowX, 0.1f);
        ImGui::DragFloat("fkShadowY", &fireKundShadow.shadowY, 0.1f);
        ImGui::DragFloat("fkShadowZ", &fireKundShadow.shadowZ, 0.1f);

        ImGui::DragFloat("hShadowLX", &hanumanShadow.lightX, 0.1f);
        ImGui::DragFloat("hShadowLY", &hanumanShadow.lightY, 0.1f);
        ImGui::DragFloat("hShadowLZ", &hanumanShadow.lightZ, 0.1f);
        ImGui::DragInt("hPower", &hanumanShadow.shadowPower);

        ImGui::DragFloat("hShadowX", &hanumanShadow.shadowX, 0.1f);
        ImGui::DragFloat("hShadowY", &hanumanShadow.shadowY, 0.1f);
        ImGui::DragFloat("hShadowZ", &hanumanShadow.shadowZ, 0.1f);

        ImGui::DragFloat("vShadowLX", &vibhishanShadow.lightX, 0.1f);
        ImGui::DragFloat("vShadowLY", &vibhishanShadow.lightY, 0.1f);
        ImGui::DragFloat("vShadowLZ", &vibhishanShadow.lightZ, 0.1f);
        ImGui::DragInt("vPower", &vibhishanShadow.shadowPower);

        ImGui::DragFloat("vShadowX", &vibhishanShadow.shadowX, 0.1f);
        ImGui::DragFloat("vShadowY", &vibhishanShadow.shadowY, 0.1f);
        ImGui::DragFloat("vShadowZ", &vibhishanShadow.shadowZ, 0.1f);

        ImGui::DragFloat("mcShadowLX", &ministerChairShadow.lightX, 0.1f);
        ImGui::DragFloat("mcShadowLY", &ministerChairShadow.lightY, 0.1f);
        ImGui::DragFloat("mcShadowLZ", &ministerChairShadow.lightZ, 0.1f);
        ImGui::DragInt("mcPower", &ministerChairShadow.shadowPower);

        ImGui::DragFloat("mcShadowX", &ministerChairShadow.shadowX, 0.1f);
        ImGui::DragFloat("mcShadowY", &ministerChairShadow.shadowY, 0.1f);
        ImGui::DragFloat("mcShadowZ", &ministerChairShadow.shadowZ, 0.1f);

        ImGui::DragFloat("pShadowLX", &pillarShadow.lightX, 0.1f);
        ImGui::DragFloat("pShadowLY", &pillarShadow.lightY, 0.1f);
        ImGui::DragFloat("pShadowLZ", &pillarShadow.lightZ, 0.1f);
        ImGui::DragInt("pPower", &pillarShadow.shadowPower);

        ImGui::DragFloat("pShadowX", &pillarShadow.shadowX, 0.1f);
        ImGui::DragFloat("pShadowY", &pillarShadow.shadowY, 0.1f);
        ImGui::DragFloat("pShadowZ", &pillarShadow.shadowZ, 0.1f);
    }

    if (ImGui::CollapsingHeader("Cave Interior Lighting - Hanumanji"))
    {
        displaySceneLightingImGui(caveInteriorScene_HanumajiLights);
    }

    if (ImGui::CollapsingHeader("Sabhamandap Lighting - Throne"))
    {
        displaySceneLightingImGui(sabhamandapScene_ThroneLights);
    }

    if (ImGui::CollapsingHeader("Sabhamandap Lighting - HanumanJi"))
    {
        displaySceneLightingImGui(sabhamandapScene_HanumajiLights);
    }

    if (ImGui::CollapsingHeader("Sabhamandap Lighting - Vibhishan"))
    {
        displaySceneLightingImGui(sabhamandapScene_VibhishanLights);
    }

    if (ImGui::CollapsingHeader("Sabhamandap Lighting - Ramvachan"))
    {
        displaySceneLightingImGui(ramvachanLights);
    }

    

    if (ImGui::CollapsingHeader("YUDDHA 01 Lighting - HanumanJi"))
    {
        displaySceneLightingImGui(generalHanumanJiLights);
    }
    

    if (ImGui::CollapsingHeader("Flying - HanumanJi"))
    {
        displaySceneLightingImGui(flyingHanumanJiLights);
    }

    //
    // Environment
    //
    if (ImGui::CollapsingHeader("Skydome"))
    {
        displaySkydomeImGui(skydomeParams[0]);
    }

    if (ImGui::CollapsingHeader("Snowfall"))
    {
        displaySnowfallImGui(snowfallParams);
    }

    if (ImGui::CollapsingHeader("God Rays"))
    {
        displayGodRaysImGui(godRaysParams);
    }

    if (ImGui::CollapsingHeader("RamWorship God Rays"))
    {
        displayGodRaysImGui(godRaysParamsForRamWorship);
    }

    if (ImGui::CollapsingHeader("Water"))
    {
        ImGui::Separator();
        ImGui::DragFloat3("Water Translation", &waterParams[0].translation[0], 0.1f);
        ImGui::DragFloat3("Water Scale", &waterParams[0].scale[0], 0.01f);

        ImGui::Separator();
        ImGui::DragFloat("Water tiling", &waterParams[0].titling, 0.01f);
        ImGui::DragFloat("Water waveStrength", &waterParams[0].waveStrength, 0.01f);

        ImGui::Separator();
        ImGui::ColorEdit3("Water Tint Color", &waterParams[0].tintColor[0]);
        ImGui::DragFloat("Water waveTintFactor", &waterParams[0].tintFactor, 0.001f);
    }

    if (ImGui::CollapsingHeader("Ocean"))
    {
        ImGui::DragFloat3("Translation", &gOcean.translation[0], 0.1f);
        ImGui::DragFloat("Extent", &gOcean.extent, 1.0f);

        ImGui::SeparatorText("Waves");

        static float global_wave_angle = 0.0f;
        static float last_global_wave_angle = 0.0f;
        if (ImGui::SliderAngle("Rotate All Wave Directions", &global_wave_angle))
        {
            float delta = global_wave_angle - last_global_wave_angle;
            float cos_d = (float)cos(delta);
            float sin_d = (float)sin(delta);
            for (int i = 0; i < gOcean.numWaves; ++i)
            {
                float nx = gOcean.waves[i].direction[0] * cos_d - gOcean.waves[i].direction[1] * sin_d;
                float ny = gOcean.waves[i].direction[0] * sin_d + gOcean.waves[i].direction[1] * cos_d;
                float len = (float)sqrt(nx * nx + ny * ny);
                if (len > 0.0001f)
                {
                    gOcean.waves[i].direction[0] = nx / len;
                    gOcean.waves[i].direction[1] = ny / len;
                }
            }
            last_global_wave_angle = global_wave_angle;
        }

        if (ImGui::Button("Increase Overall Amplitude (+10%)"))
        {
            for (int i = 0; i < gOcean.numWaves; ++i)
                gOcean.waves[i].amplitude *= 1.1f;
        }
        ImGui::SameLine();
        if (ImGui::Button("Decrease Overall Amplitude (-10%)"))
        {
            for (int i = 0; i < gOcean.numWaves; ++i)
                gOcean.waves[i].amplitude *= 0.9f;

            fprintf(gpFILE, "Ocean Overall Amplitude %.4ff,\n", gOcean.waves[0].amplitude);
            fflush(gpFILE);
        }

        gOcean.waves[0].amplitude = 0.8725f;

        ImGui::Text("Current Base Amplitude (Wave 1): %.4f", gOcean.waves[0].amplitude);
        if (ImGui::Button("Print All Waves To Log File"))
        {
            fprintf(gpFILE, "\n--- COPY WAVES PRESET TO C++ ---\n");
            fprintf(gpFILE, "p.numWaves = %d;\n", gOcean.numWaves);
            for (int i = 0; i < gOcean.numWaves; ++i)
            {
                fprintf(gpFILE, "p.waves[%d] = { vmath::vec2(%.4ff, %.4ff), %.4ff, %.4ff, %.4ff, %.4ff };\n",
                    i, gOcean.waves[i].direction[0], gOcean.waves[i].direction[1],
                    gOcean.waves[i].amplitude, gOcean.waves[i].wavelength,
                    gOcean.waves[i].speed, gOcean.waves[i].steepness);
            }
            fprintf(gpFILE, "--------------------------------\n");
            fflush(gpFILE);
        }

        ImGui::SliderInt("Num Waves", &gOcean.numWaves, 0, OCEAN_MAX_WAVES);
        for (int i = 0; i < gOcean.numWaves; i++)
        {
            ImGui::PushID(i);
            ImGui::Text("Wave %d", i + 1);
            ImGui::DragFloat2("Direction", &gOcean.waves[i].direction[0], 0.01f);
            ImGui::DragFloat("Amplitude", &gOcean.waves[i].amplitude, 0.01f);
            ImGui::DragFloat("Wavelength", &gOcean.waves[i].wavelength, 0.1f);
            ImGui::DragFloat("Speed", &gOcean.waves[i].speed, 0.01f);
            ImGui::DragFloat("Steepness", &gOcean.waves[i].steepness, 0.01f);
            ImGui::PopID();
        }

        ImGui::SeparatorText("Colors");
        ImGui::ColorEdit3("Shallow Color", &gOcean.shallowColor[0]);
        ImGui::ColorEdit3("Deep Color", &gOcean.deepColor[0]);
        ImGui::ColorEdit3("Foam Color", &gOcean.foamColor[0]);

        ImGui::SeparatorText("Foam");
        ImGui::DragFloat("Foam Threshold", &gOcean.foamThreshold, 0.01f);
        ImGui::DragFloat("Foam Softness", &gOcean.foamSoftness, 0.01f);
        ImGui::DragFloat("Foam Choppiness Gain", &gOcean.foamChoppinessGain, 0.01f);

        ImGui::SeparatorText("Sun & Lighting");
        if (ImGui::DragFloat3("Sun Direction", &gOcean.sunDirection[0], 0.01f))
            gOcean.sunDirection = vmath::normalize(gOcean.sunDirection);
        ImGui::ColorEdit3("Sun Color", &gOcean.sunColor[0]);
        ImGui::DragFloat("Sun Shininess", &gOcean.sunShininess, 1.0f);
        ImGui::DragFloat("Sun Intensity", &gOcean.sunIntensity, 0.1f);
        ImGui::DragFloat("Fresnel Strength", &gOcean.fresnelStrength, 0.01f);
        ImGui::DragFloat("Reflection Strength", &gOcean.reflectionStrength, 0.01f);

        ImGui::SeparatorText("Fog");
        ImGui::ColorEdit3("Horizon Fog Color", &gOcean.horizonFogColor[0]);
        ImGui::DragFloat("Fog Density", &gOcean.fogDensity, 0.0001f, 0.0f, 1.0f, "%.4f");
    }

    if (ImGui::CollapsingHeader("Clouds Peak Scene"))
    {
        volumetriccloudsForPeakScene->RenderIMGUI();
    }

    if (ImGui::CollapsingHeader("Clouds Flying Scene"))
    {
        volumetriccloudsForFlyingScene->RenderIMGUI();
        ImGui::DragFloat("Flying Y Position", &flyingY, 0.1f, 0.0f, 10000.0f);
    }

    if (ImGui::CollapsingHeader("Clouds Yuddha Scene"))
    {
        volumetriccloudsForYuddhaScene->RenderIMGUI();
    }

    if (ImGui::CollapsingHeader("Clouds Ocean Scene"))
    {
        volumetriccloudsForOcean->RenderIMGUI();
    }

    if (ImGui::CollapsingHeader("Fog"))
    {
        renderFogImGuiControls();
    }

    if (ImGui::CollapsingHeader("Hanuman Ocean Flying Params"))
    {
        ImGui::DragFloat("hanuman Pos X", &hanumanOceanXPos, 0.01f);
        ImGui::DragFloat("hanuman Pos Y", &hanumanOceanYPos, 0.01f);
        ImGui::DragFloat("hanuman Pos Z", &hanumanOceanZPos, 0.01f);
        ImGui::DragFloat("hanuman Pos X Factor", &hanumanOceanXFactor, 0.01f);
    }

    // if (ImGui::CollapsingHeader("Boid Simulation (V-Shape)"))
    // {
    //     ImGui::Checkbox("Enable V-Shape Boids", (bool *)&boidParamsVshape.bEnable);
    //     ImGui::Text("Boid Type: V-Shape (22 birds)");
    //     ImGui::DragInt("Bird Count (V-Shape)", &boidParamsVshape.count, 1, 1, 10);
    //     ImGui::DragFloat3("Base Position (V-Shape)", &boidParamsVshape.position[0], 1.0f);
    //     ImGui::DragFloat("Speed (V-Shape)", &boidParamsVshape.speed, 0.1f, 0.0f, 10.0f);
    //     ImGui::DragFloat("Wing Animation Speed (V-Shape)", &boidParamsVshape.wingSpeed, 0.5f, 0.0f, 50.0f);
    //     ImGui::DragFloat("Bird Scale (V-Shape)", &boidParamsVshape.scale, 0.01f, 0.05f, 5.0f);
    // }

    // if (ImGui::CollapsingHeader("Boid Simulation (Flock)"))
    // {
    //     ImGui::Checkbox("Enable Flock Boids", (bool *)&boidParamsFlock.bEnable);
    //     ImGui::Text("Boid Type: Flock (200 birds)");
    //     ImGui::DragInt("Bird Count (Flock)", &boidParamsFlock.count, 1, 1, 10);
    //     ImGui::DragFloat3("Base Position (Flock)", &boidParamsFlock.position[0], 1.0f);
    //     ImGui::DragFloat("Speed (Flock)", &boidParamsFlock.speed, 0.1f, 0.0f, 10.0f);
    //     ImGui::DragFloat("Wing Animation Speed (Flock)", &boidParamsFlock.wingSpeed, 0.5f, 0.0f, 50.0f);
    //     ImGui::DragFloat("Bird Scale (Flock)", &boidParamsFlock.scale, 0.01f, 0.05f, 5.0f);
    // }

    if (ImGui::CollapsingHeader("Mountain Camera Points"))
    {
        // renderFogImGuiControls();
        for (int le = 0; le < positionsMountainPeakScene.size(); ++le)
        {
            std::string lable("point");
            lable += ('a' + le);

            float v[3] = {positionsMountainPeakScene[le][0], positionsMountainPeakScene[le][1], positionsMountainPeakScene[le][2]};

            ImGui::DragFloat3(lable.c_str(), v, 0.1f);

            positionsMountainPeakScene[le][0] = v[0];
            positionsMountainPeakScene[le][1] = v[1];
            positionsMountainPeakScene[le][2] = v[2];
        }

        if (ImGui::Button("Save To File Points", ImVec2(100, 30)))
        {
            std::ofstream of("cam_points.txt");
            for (int le = 0; le < positionsMountainPeakScene.size(); ++le)
            {
                float v[3] = {positionsMountainPeakScene[le][0], positionsMountainPeakScene[le][1], positionsMountainPeakScene[le][2]};

                of << "vmath::vec3( " << v[0] << ", " << v[1] << ", " << v[2] << ")," << std::endl;
            }
            of.close();
        }
    }

    if (ImGui::CollapsingHeader("Yuddha Scene 01 Points"))
    {
        // renderFogImGuiControls();
        for (int le = 0; le < positionsYuddhaScene1.size(); ++le)
        {
            std::string lable("y_point");
            lable += ('a' + le);

            float v[3] = {positionsYuddhaScene1[le][0], positionsYuddhaScene1[le][1], positionsYuddhaScene1[le][2]};

            ImGui::DragFloat3(lable.c_str(), v, 0.1f);

            positionsYuddhaScene1[le][0] = v[0];
            positionsYuddhaScene1[le][1] = v[1];
            positionsYuddhaScene1[le][2] = v[2];
        }

        if (ImGui::Button("Save To File Points", ImVec2(100, 30)))
        {
            std::ofstream of("cam_pointyuddha.txt");
            for (int le = 0; le < positionsYuddhaScene1.size(); ++le)
            {
                float v[3] = {positionsYuddhaScene1[le][0], positionsYuddhaScene1[le][1], positionsYuddhaScene1[le][2]};

                of << "vmath::vec3( " << v[0] << ", " << v[1] << ", " << v[2] << ")," << std::endl;
            }
            of.close();
        }
    }

    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void uninitializeImGui(void)
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}
