/***************************************************************************
 * S.G.M.P
 * @file: flock.h
 * @brief:
 * @author: Mayur S. Tadekar(mrtadekar@gmail.com)
 * @copyright ©2020-2025 MarshallingVoid
 * @date: Saturday 2026-06-27 11:54:33 AM
 ***************************************************************************/

#pragma once

#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <vector>

#define _USE_MATH_DEFINES
#include <math.h>

#include "Pyramid.h"
#include "flockCompute.hpp"
#include "imgui.h"
#include "backends/imgui_impl_win32.h"
#include "backends/imgui_impl_opengl3.h"
#include "point.h"
#include "GLTFLoader.h"

#define NR_GOALS 5
#define MAX_BIRD_COUNT 1024

class Flock;

class BoidHelper
{
public:
    int numViewDirections = 500;

    std::vector<glm::vec4> directions;

    float ratio = 0.0f;

    BoidHelper()
    {
        // Code

        UpdateDirections();
    }

    void UpdateDirections()
    {
        // Code
        // LOG_ENTRY("log.txt", "Create Boid Helper");

        directions.clear();
        directions.resize(numViewDirections);

        float goldenRatio = (1.0f + sqrt(5.0f)) / 2.0f;
        float angleIncrement = M_PI * 2.0f * goldenRatio;

        for (int le = 0; le < numViewDirections; ++le)
        {
            float t = (float)le / numViewDirections;
            float inclination = acos(1.0f - 2.0f * t);
            float azimuth = angleIncrement * le;

            float x = 10.0f * sin(inclination) * cos(azimuth);
            float y = 10.0f * sin(inclination) * sin(azimuth);
            float z = 10.0f * cos(inclination);

            // LOG_ENTRY("log.txt", "x = %f, y = %f, z = %f", x, y, z);

            directions[le] = glm::vec4(x, y, z, 0.0f);
        }

        // LOG_ENTRY("log.txt", "Created %zu directions", directions.size());
    }

    void IncreaseDirections()
    {
        numViewDirections += 10;
        UpdateDirections();
    }

    void DecreaseDirections()
    {
        numViewDirections -= 10;
        UpdateDirections();
    }

    friend class Flock;
};

class Flock
{
public:
    Flock();

    ~Flock()
    {
        delete flockCompute;

        delete (point);
    }

    void Update(float deltaTime);

    void Draw(glm::mat4 &projectionMatrix,
              glm::mat4 &viewMatrix);

    void Draw(GLuint shaderProgramID);

    void Flock::DrawDirections();

    // void SetGoal(const glm::vec3 &goal)
    // {
    //     this->goal = goal;
    // }

    void SetBirdCount(GLuint count);

    void DisplayIMGUI();

    std::vector<glm::vec3> &GetGoals() { return (goals); }

    void Pause()
    {
        isOpenCLOn = false;
        isCUDAOn = false;
    }

    void setOpenCLON()
    {
        // Code
        isOpenCLOn = true;
        isCUDAOn = false;
    }

    void setCUDAOn()
    {
        // Code
        isCUDAOn = true;
        isOpenCLOn = false;
    }

    void Increase() { boidHelper.IncreaseDirections(); }
    void Decrease() { boidHelper.DecreaseDirections(); }

private:
    GLuint birdCount;

    Pyramid birdMesh;

    GLTFModel *fishModel;

    // glm::vec3 goal;

    std::vector<glm::vec3> goals;

    float angle;
    float deltaTime;

    float closestAllowedDistance;

    float rule1Weight;
    float rule2Weight;
    float rule3Weight;
    float rule4Weight;
    float boundaryAvoidanceWeight;
    float obstacleAvoidanceWeight;

    float minSpeed;
    float maxSpeed;

    float worldRadius;
    float boidRadius;
    float boundaryMargin;
    float lookAheadDistance;
    float avoidancePaddingFactor;

    FlockCompute *flockCompute;

    bool isOpenCLOn;
    bool isCUDAOn;

    Point *point = nullptr;

    // std::vector<Point *> points;

    BoidHelper boidHelper;
};

Flock::Flock() : fishModel(nullptr)
{
    birdCount = MAX_BIRD_COUNT;

    angle = 0.0f;

    // goal = glm::vec3(0.0f);
    for (int le = 0; le < NR_GOALS; ++le)
    {
        goals.push_back(glm::vec3(0.0f));
    }

    std::vector<glm::vec4> obstacles =
        {
            // Center XYZ, radius
            // glm::vec4(90.0f, 0.0f, 0.0f, 80.0f),
            // glm::vec4(-90.0f, 0.0f, 0.0f, 50.0f),
            // glm::vec4(0.0f, 0.0f, -90.0f, 70.0f),
            // glm::vec4(0.0f, 0.0f, 90.0f, 30.0f),
            // glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
    };

    deltaTime = 0.016f;

    closestAllowedDistance = 50.0f;

    rule1Weight = 0.80f;            // Separation (avoid collisions)
    rule2Weight = 0.1f;             // Alignment (match neighbors' direction)
    rule3Weight = 30.0f;            // Goal seeking (fly towards target)
    rule4Weight = 0.08f;            // Cohesion (move toward flock center)
    boundaryAvoidanceWeight = 2.0f; // Avoiding (move away from boundary)
    obstacleAvoidanceWeight = 50.0f;

    worldRadius = 300.0f;
    boidRadius = 5.0f;
    boundaryMargin = 5.0f;
    lookAheadDistance = 5.0f;
    avoidancePaddingFactor = 0.2f;

    minSpeed = 5.0f;
    maxSpeed = 500.0f;

    point = new Point();

    flockCompute = new FlockCompute(".\\flock_cs.glsl", birdCount, NR_GOALS);
    birdMesh.Initialize();

    isOpenCLOn = false;
    isCUDAOn = false;

    // for (int le = 0; le < boidHelper.numViewDirections; ++le)
    // {
    //     Point *newPoint = new Point();

    //     newPoint->SetPosition(boidHelper.directions[le]);

    //     points.push_back(newPoint);
    // }

    flockCompute->SetDirectionData(boidHelper.directions);

    flockCompute->SetObstaclesData(obstacles);

    fishModel = new GLTFModel();
    if (NULL == fishModel)
    {
        LOG_ENTRY("log.txt", "GLTF Model Object Creation Failed");
        exit(1);
    }
    else
    {
        LOG_ENTRY("log.txt", "GLTF Model Object Created Successfully");
    }

    if (fishModel->LoadModel("./scene.gltf"))
    {
        LOG_ENTRY("log.txt", "GLTF Model Loaded Successfully");
    }
    else
    {
        LOG_ENTRY("log.txt", "GLTF Model Loading Failed");
        exit(1);
    }
}

void Flock::DisplayIMGUI()
{
    // Code

    if (ImGui::CollapsingHeader("Flock"))
    {

        ImGui::DragFloat(
            "Closest Allowed Distance",
            &closestAllowedDistance,
            0.01f);

        ImGui::DragFloat(
            "Rule 1 - Separation",
            &rule1Weight,
            0.01f);

        ImGui::DragFloat(
            "Rule 2 - Alignment",
            &rule2Weight,
            0.01f);

        ImGui::DragFloat(
            "Rule 3 - Goal Seeking",
            &rule3Weight,
            0.01f);

        ImGui::DragFloat(
            "Rule 4 - To Flock Center",
            &rule4Weight,
            0.01f);

        ImGui::DragFloat(
            "boundaryAvoidanceWeight",
            &boundaryAvoidanceWeight,
            0.01f);

        ImGui::DragFloat(
            "obstacleAvoidanceWeight",
            &obstacleAvoidanceWeight,
            0.01f);

        ImGui::DragFloat(
            "Min Speed",
            &minSpeed,
            0.01f);

        ImGui::DragFloat(
            "Max Speed",
            &maxSpeed,
            0.01f);

        ImGui::DragFloat(
            "World Radius",
            &worldRadius,
            1.0f);

        ImGui::DragFloat(
            "Boid Radius",
            &boidRadius,
            1.0f);

        ImGui::DragFloat(
            "AvoidancePaddingFactor",
            &avoidancePaddingFactor,
            1.0f);

        ImGui::DragFloat(
            "Boundary Margin",
            &boundaryMargin,
            1.0f);

        ImGui::DragFloat(
            "Look Ahead Distance",
            &lookAheadDistance,
            1.0f);

        for (int le = 0; le < goals.size(); ++le)
        {
            auto &goal = goals[le];

            std::string lable("Goal");

            lable += '0' + le;

            ImGui::DragFloat3(
                lable.c_str(),
                &goal.x,
                0.01f);
        }
    }

    if (ImGui::CollapsingHeader("Boid Helper"))
    {

        int nums = boidHelper.numViewDirections;

        ImGui::DragInt("Number Of Directions",
                       &boidHelper.numViewDirections, 1.0, 1, 1000);

        if (boidHelper.numViewDirections != nums)
        {
            boidHelper.UpdateDirections();
        }

        float ratio = boidHelper.ratio;
        ImGui::DragFloat(
            "Ratio",
            &boidHelper.ratio,
            0.001f,
            0.0f,
            1.0f,
            "%0.5f");

        if (ratio != boidHelper.ratio)
        {
            boidHelper.UpdateDirections();
        }
    }
}

void Flock::Update(float dt)
{
    deltaTime = dt;

    angle += glm::radians(10.0f) * deltaTime;

    angle += deltaTime;

    for (int i = 0; i < NR_GOALS; i++)
    {
        float radius = 70.0f + 10.0f * i;
        float speed = 0.3f + 0.15f * i;
        float phase = M_PI * i / NR_GOALS;

        goals[i] = glm::vec3(
            radius * cos(angle * speed + phase),
            radius * 0.6f * sin(angle * (speed + 0.2f) + phase * 0.7f),
            radius * sin(angle * speed + phase));
    }

    if (isOpenCLOn)
    {
        flockCompute->RenderUsingComputeShader(
            dt,
            goals,
            closestAllowedDistance,
            rule1Weight,
            rule2Weight,
            rule3Weight,
            rule4Weight,
            boundaryAvoidanceWeight,
            obstacleAvoidanceWeight,
            worldRadius,
            boidRadius,
            boundaryMargin,
            lookAheadDistance,
            avoidancePaddingFactor,
            minSpeed,
            maxSpeed,
            birdCount);
    }
    else if (isCUDAOn)
    {
        flockCompute->RenderUsingCUDA(
            dt,
            goals,
            closestAllowedDistance,
            rule1Weight,
            rule2Weight,
            rule3Weight,
            rule4Weight,
            boundaryAvoidanceWeight,
            obstacleAvoidanceWeight,
            worldRadius,
            boidRadius,
            boundaryMargin,
            lookAheadDistance,
            avoidancePaddingFactor,
            minSpeed,
            maxSpeed,
            birdCount);
    }
}

void Flock::Draw(glm::mat4 &projection,
                 glm::mat4 &view)
{
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER,
                     0,
                     flockCompute->GetCurrentSSBO());

    birdMesh.DrawInstanced(projection,
                           view,
                           birdCount);
}

void Flock::Draw(GLuint shaderProgramID)
{
    // Code

    glBindBufferBase(GL_SHADER_STORAGE_BUFFER,
                     0,
                     flockCompute->GetCurrentSSBO());

    fishModel->DrawInstances(shaderProgramID, birdCount);
}

void Flock::DrawDirections()
{
    // Code

    glBindBufferBase(GL_SHADER_STORAGE_BUFFER,
                     0,
                     flockCompute->GetCurrentSSBO());

    for (int le = 0; le < boidHelper.numViewDirections; ++le)
    {
        point->SetPosition(boidHelper.directions[le]);

        if (le >= VFP(boidHelper.numViewDirections, 70))
        {
            point->SetColor(glm::vec3(1.0f, 0.0f, 0.0f));
        }
        else
        {
            point->SetColor(glm::vec3(0.0f, 1.0f, 0.0f));
        }

        point->Draw(MAX_BIRD_COUNT);
    }
}
