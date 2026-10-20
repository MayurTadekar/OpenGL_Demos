#pragma once
// header files
#include "../Mesh/Mesh.h"

#define RAM_WORSHIP_MODELS_SIZE 4
#define YUDDHA_SCENE2_MODELS_SIZE 2
#define CAVE_INTERIOR_MODELS_SIZE 2

// struct
typedef struct Model
{
	Mesh *meshArray = NULL;
	int numMeshes;
	char *szDirectory;
	char *szName;
} Model;

typedef struct ModelParams
{
	vmath::vec3 translation;
	vmath::vec3 scale;
} ModelParams;

// function declarations
Model *importModel(const char *filename, const char *name, bool isPBR = false);
void renderModel(Model *pModel);
void renderModelPBR(Model *pModel);
void freeModel(Model *pModel);