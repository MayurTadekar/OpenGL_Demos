#pragma once

// structs
struct Texture
{
	unsigned int id;
	int width;
	int height;
	int components;

	aiTextureType type;
};

typedef struct Texture Texture;

// extern variables
extern GLuint shaderProgramObjectTextures;
extern GLuint modelMatrixUniformTextures;
extern GLuint viewMatrixUniformTextures;
extern GLuint projectionMatrixUniformTextures;
extern GLuint textureSamplerUniformTextures;

extern GLuint vaoTextures;
extern GLuint vboTextures;
extern GLuint eboTextures;

extern struct Texture creditsTexture[10];
extern GLuint creditsTextureNum;
extern GLuint alphaUniformTextures;
extern GLfloat alpha;

// function declarations
Texture loadTexture(const char *filename, BOOL bFlipImage);
BOOL loadTerrainTexture(GLuint *texture, const char *ImageFilePath);
Texture loadCubemapTexture(const char *filenames[6]);
bool LoadTextureFromFile(const char *filepath, GLuint *texture);

void initializeTextures(void);
void displayTextures(GLuint textureID, float alpha);
void updateTextures(void);
void uninitializeTextures(void);
