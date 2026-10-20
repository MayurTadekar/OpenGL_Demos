#pragma once

// Header files
#include "../include/common.h"
#include "../modules/Texture/Texture.h"

// structs
typedef struct MeshVertex
{
	vmath::vec3 position;
	vmath::vec3 normal;
	vmath::vec3 tangent;
	vmath::vec2 texcoord;
} MeshVertex;

typedef struct Mesh
{
	Texture *textures;

	Texture blackTexture;
	Texture whiteTexture;

	bool hasBaseColor = false;
	bool hasNormal = false;
	bool hasRoughness = false;
	bool hasMetallic = false;
	bool hasEmissive = false;
	bool hasSpecular = false;

	size_t vertexCount;
	size_t indexCount;
	size_t textureCount;

	GLuint vao;
	GLuint vbo;
	GLuint ebo;
} Mesh;

// function declarations
// Mesh processAssimpMesh(aiMesh *mesh, const aiScene *scene, char *directory);
Mesh processAssimpMesh(aiMesh *mesh, const aiScene *scene, char *directory, bool isPBR);
void renderMesh(Mesh *mesh);
void renderMeshPBR(Mesh *mesh);
