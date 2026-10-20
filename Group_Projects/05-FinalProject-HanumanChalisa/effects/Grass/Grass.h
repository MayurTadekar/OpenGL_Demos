#pragma once

// header files
#include <vector>
#include "../include/common.h"
#include "../modules/Texture/Texture.h"

// structs
typedef struct GrassVertex
{
    vmath::vec3 position;
    float animationTime;
} GrassVertex;

// class declaration
class Grass
{
private:
    GLuint        m_vao           = 0;
    GLuint        m_vbo           = 0;
    GLfloat       m_animationTime = 0.0f; 
    std::vector<GrassVertex> m_positions;

    GLfloat m_scale = 2.270f;
    GLfloat m_density = 0.1f;
    

    // textures
    Texture m_grassTexture;
    Texture m_flowTexture;

public:
    // grass will only be generated in XZ plane
    float m_grassY = 10.0f;
    // vmath::vec2 m_generationVectorStart = vmath::vec2(-60.0f, -60.0f);
    // vmath::vec2 m_generationVectorEnd   = vmath::vec2(10.0f, 10.0f);

    // vmath::vec2 m_generationVectorStart = vmath::vec2(-15.0f, -45.0f);
    // vmath::vec2 m_generationVectorEnd   = vmath::vec2(10.0f, 10.0f);

    vmath::vec2 m_generationVectorStart = vmath::vec2(7.0f, 7.0f);
    vmath::vec2 m_generationVectorEnd   = vmath::vec2(12.0f, 12.0f);

    int m_numGrassBladesToGenerate = 1000;

    BOOL bOnGPU = FALSE;

    Grass(void);
    void generateGrass(void);
    void render(vmath::mat4 viewMatrix, vmath::mat4 projectionMatrix, vmath::vec3 cameraPosition);
    //void renderUsingMatrices(DynamicArray *arrMatrices, vmath::mat4 viewMatrix, vmath::mat4 projectionMatrix, vmath::vec3 cameraPosition);
    void update(void);

    ~Grass(void);
};
