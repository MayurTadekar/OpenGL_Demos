// header files
#include "Mesh.h"

// function defination
Mesh processAssimpMesh(aiMesh *mesh, const aiScene *scene, char *directory, bool isPBR)
{
	// function declaration
	void loadMaterialTextures(Mesh * pMesh, aiMaterial * material, const char *directory);
	void loadMaterialTexturesPBR(Mesh * pMesh, aiMaterial * material, const char *directory);

	// local variable
	MeshVertex *vertices = NULL;
	GLuint *indices = NULL;
	size_t currentIndicesIndex = 0;
	int i, j;

	Mesh processedMesh;

	// code
	ZeroMemory((void *)&processedMesh, sizeof(Mesh));

	LOG_ENTRY_WITH_PARAM("log.txt", "Processing Mesh %s", mesh->mName.C_Str());

	// calculate number of total indices
	for (i = 0; i < mesh->mNumFaces; i++)
	{
		processedMesh.indexCount = processedMesh.indexCount + mesh->mFaces[i].mNumIndices;
	}

	processedMesh.vertexCount = mesh->mNumVertices;
	vertices = (MeshVertex *)malloc(sizeof(MeshVertex) * processedMesh.vertexCount);
	indices = (GLuint *)malloc(sizeof(GLuint) * processedMesh.indexCount);

	for (i = 0; i < (processedMesh.vertexCount); i++)
	{
		MeshVertex vertex;

		vertex.position[0] = mesh->mVertices[i].x;
		vertex.position[1] = mesh->mVertices[i].y;
		vertex.position[2] = mesh->mVertices[i].z;

		vertex.normal[0] = mesh->mNormals[i].x;
		vertex.normal[1] = mesh->mNormals[i].y;
		vertex.normal[2] = mesh->mNormals[i].z;

		// vertex.tangent[0] = mesh->mTangents[i].x;
		// vertex.tangent[1] = mesh->mTangents[i].y;
		// vertex.tangent[2] = mesh->mTangents[i].z;
		if (mesh->mTangents)
		{
			vertex.tangent[0] = mesh->mTangents[i].x;
			vertex.tangent[1] = mesh->mTangents[i].y;
			vertex.tangent[2] = mesh->mTangents[i].z;
		}
		else
		{
			memset(&vertex.tangent, 0, sizeof(vertex.tangent));
		}

		if (mesh->mTextureCoords[0])
		{
			vertex.texcoord[0] = mesh->mTextureCoords[0][i].x;
			vertex.texcoord[1] = mesh->mTextureCoords[0][i].y;
		}

		vertices[i] = vertex;
	}

	for (i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (j = 0; j < face.mNumIndices; j++)
		{
			indices[currentIndicesIndex] = face.mIndices[j];
			currentIndicesIndex++;
		}
	}

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
		if (isPBR)
		{
			loadMaterialTexturesPBR(&processedMesh, material, directory);
		}
		else
		{
			loadMaterialTextures(&processedMesh, material, directory);
		}
	}

	// step 17 : create VAO (vertex array object)
	glGenVertexArrays(1, &processedMesh.vao);

	// step 18 : bind with VAO (vertex array object)
	glBindVertexArray(processedMesh.vao);

	// step 19 : VBO(Vertex Buffer Object) for position + texcoord
	glGenBuffers(1, &processedMesh.vbo);

	// step 20 : bind with VBO( Vertex Buffer Object) for position
	glBindBuffer(GL_ARRAY_BUFFER, processedMesh.vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(MeshVertex) * processedMesh.vertexCount, vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(AMC_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (const void *)(0 * sizeof(vmath::vec3)));

	glEnableVertexAttribArray(AMC_ATTRIBUTE_POSITION);

	glVertexAttribPointer(AMC_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (const void *)(1 * sizeof(vmath::vec3)));

	glEnableVertexAttribArray(AMC_ATTRIBUTE_NORMAL);

	glVertexAttribPointer(AMC_ATTRIBUTE_TANGENT, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (const void *)(2 * sizeof(vmath::vec3)));

	glEnableVertexAttribArray(AMC_ATTRIBUTE_TANGENT);

	glVertexAttribPointer(AMC_ATTRIBUTE_TEXCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (const void *)(3 * sizeof(vmath::vec3)));

	glEnableVertexAttribArray(AMC_ATTRIBUTE_TEXCOORD);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//  EBO
	glGenBuffers(1, &processedMesh.ebo);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, processedMesh.ebo);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * processedMesh.indexCount, indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	free(indices);
	indices = NULL;
	free(vertices);
	vertices = NULL;
	return (processedMesh);
}

void renderMesh(Mesh *mesh)
{
	// code
	// Bind the zero'th Texture [if any]
	if (mesh->textureCount > 0)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textures[0].id);
	}

	// render
	glBindVertexArray(mesh->vao);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);
	glDrawElements(GL_TRIANGLES, mesh->indexCount, GL_UNSIGNED_INT, NULL);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void renderMeshPBR(Mesh *mesh)
{
	// code
	// Bind the zero'th Texture [if any]
	// if (mesh->textureCount > 0)
	// {
	// }

	for (int le = 0; le < mesh->textureCount; ++le)
	{
		switch (mesh->textures[le].type)
		{
		case aiTextureType_BASE_COLOR:
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, mesh->textures[le].id);
			break;

		case aiTextureType_NORMALS:
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, mesh->textures[le].id);
			break;

		case aiTextureType_DIFFUSE_ROUGHNESS:
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, mesh->textures[le].id);
			break;

		case aiTextureType_METALNESS:
			glActiveTexture(GL_TEXTURE3);
			glBindTexture(GL_TEXTURE_2D, mesh->textures[le].id);
			break;

		case aiTextureType_EMISSIVE:
			glActiveTexture(GL_TEXTURE4);
			glBindTexture(GL_TEXTURE_2D, mesh->textures[le].id);
			break;
		}
	}

	if (!mesh->hasBaseColor)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->whiteTexture.id);
	}

	if (!mesh->hasNormal)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, mesh->blackTexture.id);
	}

	if (!mesh->hasRoughness)
	{
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, mesh->whiteTexture.id);
	}

	if (!mesh->hasMetallic)
	{
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, mesh->blackTexture.id);
	}

	if (!mesh->hasEmissive)
	{
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, mesh->blackTexture.id);
	}

	// render
	glBindVertexArray(mesh->vao);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);
	glDrawElements(GL_TRIANGLES, mesh->indexCount, GL_UNSIGNED_INT, NULL);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void loadMaterialTextures(Mesh *pMesh, aiMaterial *material, const char *directory)
{
	// local variables
	int textureCount;
	int i;

	// code
	aiString path;

	// for (unsigned int i = 0; i < material->GetTextureCount(aiTextureType_BASE_COLOR); i++)
	// {
	// 	material->GetTexture(aiTextureType_BASE_COLOR, i, &path);
	// 	LOG_ENTRY_WITH_PARAM("log.txt", "Base Color Texture Name = %s", path.C_Str());
	// 	// printf("BaseColor : %s\n", path.C_Str());
	// }

	// // Diffuse (older glTFs sometimes map here)
	// for (unsigned int i = 0; i < material->GetTextureCount(aiTextureType_DIFFUSE); i++)
	// {
	// 	material->GetTexture(aiTextureType_DIFFUSE, i, &path);
	// 	LOG_ENTRY_WITH_PARAM("log.txt", "Diffuse Texture Name = %s", path.C_Str());
	// }

	// // Normal
	// for (unsigned int i = 0; i < material->GetTextureCount(aiTextureType_NORMALS); i++)
	// {
	// 	material->GetTexture(aiTextureType_NORMALS, i, &path);
	// 	LOG_ENTRY_WITH_PARAM("log.txt", "Normal Texture Name = %s", path.C_Str());
	// }

	// // Roughness
	// for (unsigned int i = 0; i < material->GetTextureCount(aiTextureType_DIFFUSE_ROUGHNESS); i++)
	// {
	// 	material->GetTexture(aiTextureType_DIFFUSE_ROUGHNESS, i, &path);
	// 	LOG_ENTRY_WITH_PARAM("log.txt", "Roughness Texture Name = %s", path.C_Str());
	// }

	// // Metallic
	// for (unsigned int i = 0; i < material->GetTextureCount(aiTextureType_METALNESS); i++)
	// {
	// 	material->GetTexture(aiTextureType_METALNESS, i, &path);
	// 	LOG_ENTRY_WITH_PARAM("log.txt", "Metallic Texture Name = %s", path.C_Str());
	// }

	// // Emissive
	// for (unsigned int i = 0; i < material->GetTextureCount(aiTextureType_EMISSIVE); i++)
	// {
	// 	material->GetTexture(aiTextureType_EMISSIVE, i, &path);
	// 	LOG_ENTRY_WITH_PARAM("log.txt", "Emissive Texture Name = %s", path.C_Str());
	// }

	// for base color texture
	textureCount = aiGetMaterialTextureCount(material, aiTextureType_BASE_COLOR);

	LOG_ENTRY_WITH_PARAM("log.txt", "Base Color Texture Count = %d", textureCount);

	for (i = 0; i < textureCount; i++)
	{
		// create the texture's path string
		aiString str;
		aiGetMaterialTexture(material, aiTextureType_BASE_COLOR, i, &str);
		LOG_ENTRY_WITH_PARAM("log.txt", "Base Color Texture Name = %s", str.C_Str());

		char *texturePath = (char *)malloc(strlen(directory) + strlen(str.data) + 1);

		strcpy(texturePath, directory);

		strcat(texturePath, str.data);

		// load the texture
		Texture texture = loadTexture(texturePath, false);

		(pMesh->textureCount)++;

		// free the texturePath string
		free(texturePath);
		texturePath = NULL;

		// add the texture to the array
		pMesh->textures = (Texture *)realloc(pMesh->textures, sizeof(Texture) * pMesh->textureCount);

		pMesh->textures[pMesh->textureCount - 1] = texture;
	}

	// for diffuse color texture
	textureCount = aiGetMaterialTextureCount(material, aiTextureType_DIFFUSE);

	// LOG_ENTRY_WITH_PARAM("log.txt", "Diffuse Color Texture Count = %d", textureCount);

	// for (i = 0; i < textureCount; i++)
	// {
	// 	// create the texture's path string
	// 	aiString str;
	// 	aiGetMaterialTexture(material, aiTextureType_DIFFUSE, i, &str);
	// 	LOG_ENTRY_WITH_PARAM("log.txt", "Diffuse Color Texture Name = %s", str.C_Str());

	// 	char *texturePath = (char *)malloc(strlen(directory) + strlen(str.data) + 1);

	// 	strcpy(texturePath, directory);

	// 	strcat(texturePath, str.data);

	// 	// load the texture
	// 	Texture texture = loadTexture(texturePath, false);

	// 	(pMesh->textureCount)++;

	// 	// free the texturePath string
	// 	free(texturePath);
	// 	texturePath = NULL;

	// 	// add the texture to the array
	// 	pMesh->textures = (Texture *)realloc(pMesh->textures, sizeof(Texture) * pMesh->textureCount);

	// 	pMesh->textures[pMesh->textureCount - 1] = texture;
	// }
}

void loadMaterialTexturesPBR(Mesh *pMesh, aiMaterial *material, const char *directory)
{
	// local variables
	int textureCount;
	int i;

	// code
	aiString path;

	pMesh->hasBaseColor = false;
	pMesh->hasNormal = false;
	pMesh->hasRoughness = false;
	pMesh->hasMetallic = false;
	pMesh->hasEmissive = false;

	// for (unsigned int i = 0; i < material->GetTextureCount(aiTextureType_BASE_COLOR); i++)
	// {
	// 	material->GetTexture(aiTextureType_BASE_COLOR, i, &path);
	// 	LOG_ENTRY_WITH_PARAM("log.txt", "Base Color Texture Name = %s", path.C_Str());
	// 	// printf("BaseColor : %s\n", path.C_Str());
	// }

	// // Diffuse (older glTFs sometimes map here)
	// for (unsigned int i = 0; i < material->GetTextureCount(aiTextureType_DIFFUSE); i++)
	// {
	// 	material->GetTexture(aiTextureType_DIFFUSE, i, &path);
	// 	LOG_ENTRY_WITH_PARAM("log.txt", "Diffuse Texture Name = %s", path.C_Str());
	// }
	// for base color texture
	textureCount = aiGetMaterialTextureCount(material, aiTextureType_BASE_COLOR);
	LOG_ENTRY_WITH_PARAM("log.txt", "Base Color Texture Count = %d", textureCount);
	for (i = 0; i < textureCount; i++)
	{
		// create the texture's path string
		aiString str;
		aiGetMaterialTexture(material, aiTextureType_BASE_COLOR, i, &str);
		LOG_ENTRY_WITH_PARAM("log.txt", "Base Color Texture Name = %s", str.C_Str());

		char *texturePath = (char *)malloc(strlen(directory) + strlen(str.data) + 1);

		strcpy(texturePath, directory);

		strcat(texturePath, str.data);

		// load the texture
		Texture texture = loadTexture(texturePath, false);
		texture.type = aiTextureType_BASE_COLOR;
		pMesh->hasBaseColor = true;

		(pMesh->textureCount)++;

		// free the texturePath string
		free(texturePath);
		texturePath = NULL;

		// add the texture to the array
		pMesh->textures = (Texture *)realloc(pMesh->textures, sizeof(Texture) * pMesh->textureCount);

		pMesh->textures[pMesh->textureCount - 1] = texture;
	}

	// // Normal
	// for (unsigned int i = 0; i < material->GetTextureCount(aiTextureType_NORMALS); i++)
	// {
	// 	material->GetTexture(aiTextureType_NORMALS, i, &path);
	// 	LOG_ENTRY_WITH_PARAM("log.txt", "Normal Texture Name = %s", path.C_Str());
	// }
	// for base normals texture
	textureCount = aiGetMaterialTextureCount(material, aiTextureType_NORMALS);
	LOG_ENTRY_WITH_PARAM("log.txt", "Normal Texture Count = %d", textureCount);
	for (i = 0; i < textureCount; i++)
	{
		// create the texture's path string
		aiString str;
		aiGetMaterialTexture(material, aiTextureType_NORMALS, i, &str);
		LOG_ENTRY_WITH_PARAM("log.txt", "Normal Texture Name = %s", str.C_Str());

		char *texturePath = (char *)malloc(strlen(directory) + strlen(str.data) + 1);

		strcpy(texturePath, directory);

		strcat(texturePath, str.data);

		// load the texture
		Texture texture = loadTexture(texturePath, false);
		texture.type = aiTextureType_NORMALS;
		pMesh->hasNormal = true;

		(pMesh->textureCount)++;

		// free the texturePath string
		free(texturePath);
		texturePath = NULL;

		// add the texture to the array
		pMesh->textures = (Texture *)realloc(pMesh->textures, sizeof(Texture) * pMesh->textureCount);

		pMesh->textures[pMesh->textureCount - 1] = texture;
	}

	// // Roughness
	// for (unsigned int i = 0; i < material->GetTextureCount(aiTextureType_DIFFUSE_ROUGHNESS); i++)
	// {
	// 	material->GetTexture(aiTextureType_DIFFUSE_ROUGHNESS, i, &path);
	// 	LOG_ENTRY_WITH_PARAM("log.txt", "Roughness Texture Name = %s", path.C_Str());
	// }
	// for base Roughness texture
	textureCount = aiGetMaterialTextureCount(material, aiTextureType_DIFFUSE_ROUGHNESS);
	LOG_ENTRY_WITH_PARAM("log.txt", "Roughness Texture Count = %d", textureCount);
	for (i = 0; i < textureCount; i++)
	{
		// create the texture's path string
		aiString str;
		aiGetMaterialTexture(material, aiTextureType_DIFFUSE_ROUGHNESS, i, &str);
		LOG_ENTRY_WITH_PARAM("log.txt", "Roughness Texture Name = %s", str.C_Str());

		char *texturePath = (char *)malloc(strlen(directory) + strlen(str.data) + 1);

		strcpy(texturePath, directory);

		strcat(texturePath, str.data);

		// load the texture
		Texture texture = loadTexture(texturePath, false);
		texture.type = aiTextureType_DIFFUSE_ROUGHNESS;
		pMesh->hasRoughness = true;

		(pMesh->textureCount)++;

		// free the texturePath string
		free(texturePath);
		texturePath = NULL;

		// add the texture to the array
		pMesh->textures = (Texture *)realloc(pMesh->textures, sizeof(Texture) * pMesh->textureCount);

		pMesh->textures[pMesh->textureCount - 1] = texture;
	}

	// // Metallic
	// for (unsigned int i = 0; i < material->GetTextureCount(aiTextureType_METALNESS); i++)
	// {
	// 	material->GetTexture(aiTextureType_METALNESS, i, &path);
	// 	LOG_ENTRY_WITH_PARAM("log.txt", "Metallic Texture Name = %s", path.C_Str());
	// }
	// for base Metallic texture
	textureCount = aiGetMaterialTextureCount(material, aiTextureType_METALNESS);
	LOG_ENTRY_WITH_PARAM("log.txt", "Metallic Texture Count = %d", textureCount);
	for (i = 0; i < textureCount; i++)
	{
		// create the texture's path string
		aiString str;
		aiGetMaterialTexture(material, aiTextureType_METALNESS, i, &str);
		LOG_ENTRY_WITH_PARAM("log.txt", "Metallic Texture Name = %s", str.C_Str());

		char *texturePath = (char *)malloc(strlen(directory) + strlen(str.data) + 1);

		strcpy(texturePath, directory);

		strcat(texturePath, str.data);

		// load the texture
		Texture texture = loadTexture(texturePath, false);
		texture.type = aiTextureType_METALNESS;
		pMesh->hasMetallic = true;

		(pMesh->textureCount)++;

		// free the texturePath string
		free(texturePath);
		texturePath = NULL;

		// add the texture to the array
		pMesh->textures = (Texture *)realloc(pMesh->textures, sizeof(Texture) * pMesh->textureCount);

		pMesh->textures[pMesh->textureCount - 1] = texture;
	}

	// // Emissive
	// for (unsigned int i = 0; i < material->GetTextureCount(aiTextureType_EMISSIVE); i++)
	// {
	// 	material->GetTexture(aiTextureType_EMISSIVE, i, &path);
	// 	LOG_ENTRY_WITH_PARAM("log.txt", "Emissive Texture Name = %s", path.C_Str());
	// }
	// for base Emissive texture
	textureCount = aiGetMaterialTextureCount(material, aiTextureType_EMISSIVE);
	LOG_ENTRY_WITH_PARAM("log.txt", "Emissive Texture Count = %d", textureCount);
	for (i = 0; i < textureCount; i++)
	{
		// create the texture's path string
		aiString str;
		aiGetMaterialTexture(material, aiTextureType_EMISSIVE, i, &str);
		LOG_ENTRY_WITH_PARAM("log.txt", "Emissive Texture Name = %s", str.C_Str());

		char *texturePath = (char *)malloc(strlen(directory) + strlen(str.data) + 1);

		strcpy(texturePath, directory);

		strcat(texturePath, str.data);

		// load the texture
		Texture texture = loadTexture(texturePath, false);
		texture.type = aiTextureType_EMISSIVE;
		pMesh->hasEmissive = true;

		(pMesh->textureCount)++;

		// free the texturePath string
		free(texturePath);
		texturePath = NULL;

		// add the texture to the array
		pMesh->textures = (Texture *)realloc(pMesh->textures, sizeof(Texture) * pMesh->textureCount);

		pMesh->textures[pMesh->textureCount - 1] = texture;
	}

	// // // Specular
	// // for (unsigned int i = 0; i < material->GetTextureCount(aiTextureType_SPECULAR); i++)
	// // {
	// // 	material->GetTexture(aiTextureType_SPECULAR, i, &path);
	// // 	LOG_ENTRY_WITH_PARAM("log.txt", "Emissive Texture Name = %s", path.C_Str());
	// // }
	// // for base Specular texture
	// textureCount = aiGetMaterialTextureCount(material, aiTextureType_SPECULAR);
	// LOG_ENTRY_WITH_PARAM("log.txt", "Specular Texture Count = %d", textureCount);
	// for (i = 0; i < textureCount; i++)
	// {
	// 	// create the texture's path string
	// 	aiString str;
	// 	aiGetMaterialTexture(material, aiTextureType_SPECULAR, i, &str);
	// 	LOG_ENTRY_WITH_PARAM("log.txt", "Specular Texture Name = %s", str.C_Str());

	// 	char *texturePath = (char *)malloc(strlen(directory) + strlen(str.data) + 1);

	// 	strcpy(texturePath, directory);

	// 	strcat(texturePath, str.data);

	// 	// load the texture
	// 	Texture texture = loadTexture(texturePath, false);
	// 	texture.type = aiTextureType_SPECULAR;
	// 	pMesh->hasSpecular = true;

	// 	(pMesh->textureCount)++;

	// 	// free the texturePath string
	// 	free(texturePath);
	// 	texturePath = NULL;

	// 	// add the texture to the array
	// 	pMesh->textures = (Texture *)realloc(pMesh->textures, sizeof(Texture) * pMesh->textureCount);

	// 	pMesh->textures[pMesh->textureCount - 1] = texture;
	// }

	// for diffuse color texture
	// textureCount = aiGetMaterialTextureCount(material, aiTextureType_DIFFUSE);

	// LOG_ENTRY_WITH_PARAM("log.txt", "Diffuse Color Texture Count = %d", textureCount);

	// for (i = 0; i < textureCount; i++)
	// {
	// 	// create the texture's path string
	// 	aiString str;
	// 	aiGetMaterialTexture(material, aiTextureType_DIFFUSE, i, &str);
	// 	LOG_ENTRY_WITH_PARAM("log.txt", "Diffuse Color Texture Name = %s", str.C_Str());

	// 	char *texturePath = (char *)malloc(strlen(directory) + strlen(str.data) + 1);

	// 	strcpy(texturePath, directory);

	// 	strcat(texturePath, str.data);

	// 	// load the texture
	// 	Texture texture = loadTexture(texturePath, false);

	// 	(pMesh->textureCount)++;

	// 	// free the texturePath string
	// 	free(texturePath);
	// 	texturePath = NULL;

	// 	// add the texture to the array
	// 	pMesh->textures = (Texture *)realloc(pMesh->textures, sizeof(Texture) * pMesh->textureCount);

	// 	pMesh->textures[pMesh->textureCount - 1] = texture;
	// }

	pMesh->blackTexture = loadTexture("./resources/Texture/black.jpg", false);
	pMesh->whiteTexture = loadTexture("./resources/Texture/white.jpg", false);

	LOG_ENTRY_WITH_PARAM("log.txt", "Texture Count = %zu", pMesh->textureCount);
	LOG_ENTRY("log.txt", "");
}
