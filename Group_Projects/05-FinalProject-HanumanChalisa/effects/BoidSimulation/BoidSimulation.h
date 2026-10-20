#pragma once

#include "../../include/common.h"
#include "../../modules/Model/Model.h"
#include <vector>

enum BoidType {
    BOID_V_SHAPE = 0,
    BOID_FLOCK = 1
};

struct BoidParams {
    BOOL bEnable = TRUE;
    int type = BOID_V_SHAPE;
    vmath::vec3 position = vmath::vec3(0.0f, 150.0f, 0.0f);
    float speed = 1.0f;
    float wingSpeed = 15.0f;
    float scale = 0.2f;
    int count = 22;
};

class BoidSimulation {
public:
    BoidSimulation();
    ~BoidSimulation();

    BOOL Initialize();
    void Update(float deltaTime, BoidParams& params);
    void Render(const vmath::mat4& projectionMatrix, const vmath::mat4& viewMatrix, BoidParams& params);
    void Uninitialize();

private:
    GLuint shaderProgramObject = 0;
    GLuint modelMatrixUniform = 0;
    GLuint viewMatrixUniform = 0;
    GLuint projectionMatrixUniform = 0;
    GLuint timeUniform = 0;
    GLuint wingSpeedUniform = 0;

    float currentTime = 0.0f;
    std::vector<vmath::mat4> instanceMatrices;
};
