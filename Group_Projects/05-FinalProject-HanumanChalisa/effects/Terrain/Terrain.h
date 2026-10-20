#ifndef TERRAIN_H
#define TERRAIN_H

/******************************************* Header Files *******************************************/
#include <vector>
#include "../include/common.h"
#include "../modules/Texture/Texture.h"
#include "../modules/Camera/Camera.h"

/******************************************* Class Declaration *******************************************/
class Terrain
{
    private :
        // Shader Related variables
        GLuint ShaderProgramObject;
        GLuint VAO;
        GLuint VBO;
        GLuint EBO;

        // Transformation related uniforms
        GLuint ModelMatrixUniform;
        GLuint ViewMatrixUniform;
        GLuint ProjectionMatrixUniform;
        vmath::mat4 PerspectiveProjectionMatrix;

        // Terrain related data
        GLfloat * MeshVertexdata;
        int MeshVertexDataCount;
        GLuint * IndexData;
        int IndexCount;
        int TerrainResolution;
        GLfloat TerrainLength;
        GLfloat TerrainHeightScale;

        // Must match vertex shader displacement / normals
        GLuint TerrainWorldSizeUniform;
        GLuint HeightScaleUniform;

        // Light related variables
        GLfloat LightDirection[3];
        GLfloat LightColor[3];
        GLuint LightColorUniform;
        GLuint LightDirectionUniform;
        GLuint CameraPositionUniform;

        // Terrain maps
        GLuint HeightMapTexture;
        GLuint AlbedoMapTexture;
        GLuint NormalMapTexture;
        GLuint RoughnessMapTexture;
        GLuint AmbientOcclusionMapTexture;

        GLuint HeightMapSamplerUniform;
        GLuint AlbedoMapSamplerUniform;
        GLuint NormalMapSamplerUniform;
        GLuint RoughnessMapSamplerUniform;
        GLuint AmbientOcclusionMapSamplerUniform;

    public :
        // Constructor
        Terrain();

        // Functions
        int initialize(const char *, const char *, const char *, const char *, const char *);
        void GenerateTerrainData(int, int, GLfloat, GLfloat, GLfloat**, int *, GLuint**, int*);
        GLchar* LoadShaderSource(const char*);
        void resize(int, int);
        void display(void);
        void Terrain::render(Camera *pCamera, vmath::mat4 projectionMatrix);
        void update(void);
        void uninitialize(void);
};

#endif
