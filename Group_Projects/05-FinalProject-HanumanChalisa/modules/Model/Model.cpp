// Header files
#include "../include/common.h"
#include "./../Mesh/Mesh.h"
#include "./Model.h"

Model *importModel(const char *filename, const char *name, bool isPBR)
{
	// function declaration
	void processAssimpNode(aiNode *, const aiScene *, Model *, bool isPBR);

	// local variable
	Model *pModel = NULL;

	// code
	pModel = (Model *)malloc(sizeof(Model));
	if (pModel == NULL)
	{
		LOG("importModel(): malloc() failed.\n");
		uninitialize();
		exit(EXIT_FAILURE);
	}

	ZeroMemory((void *)pModel, sizeof(Model));

	pModel->szName = strdup(name);

	// import the model into an aiScene structure
	const struct aiScene *scene = aiImportFile(filename, aiProcess_Triangulate | aiProcess_FlipUVs);
	if ((scene == NULL) || (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE))
	{
		LOG("importModel(): aiImportFile() failed. (%s)\n", filename);
		freeModel(pModel);
		pModel = NULL;
		uninitialize();
		exit(EXIT_FAILURE);
	}

	// store the directory of the Model
	int wordLength = 0;
	int i, j;
	size_t filenameSize = strlen(filename);

	pModel->szDirectory = (char *)malloc(sizeof(char) * (filenameSize + 1));
	if (pModel->szDirectory == NULL)
	{
		LOG("importModel(): malloc() failed for szDirectory.\n");
		freeModel(pModel);
		pModel = NULL;
		uninitialize();
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < filenameSize; i++)
	{
		pModel->szDirectory[i] = filename[i];
		if (filename[i] == '/')
		{
			wordLength = 0;
		}
		else
		{
			wordLength++;
		}
	}

	for (j = i - wordLength; j < filenameSize; j++)
	{
		pModel->szDirectory[j] = '\0';
	}

	processAssimpNode(scene->mRootNode, scene, pModel, isPBR);
	aiReleaseImport(scene);

	return (pModel);
}

void renderModel(Model *pModel)
{
	// code
	for (int i = 0; i < pModel->numMeshes; i++)
	{
		renderMesh(&(pModel->meshArray[i]));
	}
}

void renderModelPBR(Model *pModel)
{
	// code
	for (int i = 0; i < pModel->numMeshes; i++)
	{

		if (pModel->meshArray[i].textureCount > 1)
			renderMeshPBR(&(pModel->meshArray[i]));
		else
			renderMesh(&(pModel->meshArray[i]));
	}
}

void freeModel(Model *pModel)
{
	// code
	if (pModel->meshArray)
	{
		const int meshCount = pModel->numMeshes;
		for (int i = 0; i < meshCount; i++)
		{
			Mesh meshToFree = pModel->meshArray[i];

			if (meshToFree.ebo)
			{
				glDeleteBuffers(1, &meshToFree.ebo);
				meshToFree.ebo = 0;
			}

			if (meshToFree.vbo)
			{
				glDeleteBuffers(1, &meshToFree.vbo);
				meshToFree.vbo = 0;
			}

			if (meshToFree.vao)
			{
				glDeleteVertexArrays(1, &meshToFree.vao);
				meshToFree.vao = 0;
			}

			if (meshToFree.textures)
			{
				free(meshToFree.textures);
				meshToFree.textures = NULL;
			}
		}

		if (pModel->meshArray)
		{
			free(pModel->meshArray);
			pModel->meshArray = NULL;
		}
	}

	if (pModel->szDirectory)
	{
		free(pModel->szDirectory);
		pModel->szDirectory = NULL;
	}

	if (pModel->szName)
	{
		free(pModel->szName);
		pModel->szName = NULL;
	}

	if (pModel)
	{
		free(pModel);
		pModel = NULL;
	}
}

// Internal Functions
void processAssimpNode(aiNode *pNode, const aiScene *scene, Model *pModel, bool isPBR)
{
	// Local variables
	int i;

	// code
	for (i = 0; i < pNode->mNumMeshes; i++)
	{
		// process the current mesh
		aiMesh *pMesh = scene->mMeshes[pNode->mMeshes[i]];
		Mesh processedMesh = processAssimpMesh(pMesh, scene, pModel->szDirectory, isPBR);
		(pModel->numMeshes)++;

		// add the process mesh to the mesh array
		pModel->meshArray = (Mesh *)realloc(pModel->meshArray, sizeof(Mesh) * pModel->numMeshes);
		if (pModel->meshArray == NULL)
		{
			LOG("processAssimpNode(): realloc() failed for szDirectory.\n");
			freeModel(pModel);
			pModel = NULL;
			uninitialize();
			exit(EXIT_FAILURE);
		}

		pModel->meshArray[pModel->numMeshes - 1] = processedMesh;
	}

	for (i = 0; i < pNode->mNumChildren; i++)
	{
		processAssimpNode(pNode->mChildren[i], scene, pModel, isPBR);
	}
}
