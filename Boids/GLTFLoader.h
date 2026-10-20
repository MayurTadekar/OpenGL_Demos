/***************************************************************************
 * S.G.M.P 
 * @file: GLTFLoader.h
 * @brief: GLTF Model Loader using Assimp with Texture Support
 * @author: Mayur S. Tadekar(mrtadekar@gmail.com)
 * @date: Saturday 2026-08-15 6:33:44 PM
 ***************************************************************************/

#pragma once

#include <GL/glew.h>
#include <GL/GL.h>
// #include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>
// #include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <iostream>

#include "macros.h"
#include "TextureLoader.h"

// Forward declaration
class Shader;
class Program;

/*
 * Structure to hold vertex data
 */
struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoord;
	glm::vec3 tangent;
	glm::vec3 bitangent;
};

/*
 * Structure to hold texture data
 */
struct Texture
{
	GLuint id;
	std::string type;
	std::string path;
};

/*
 * Structure to hold material properties
 */
struct Material
{
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;
	std::vector<Texture> textures;
};

/*
 * Mesh class to handle individual mesh rendering
 */
class Mesh
{
private:
	GLuint vao, vbo, ebo;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	Material material;

	void SetupMesh()
	{
		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &ebo);

		glBindVertexArray(vao);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

		// Vertex Positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

		// Vertex Normals
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

		// Vertex Texture Coordinates
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));

		// Vertex Tangent
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));

		// Vertex Bitangent
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangent));

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

		glBindVertexArray(0);
	}

public:
	Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const Material& material)
		: vertices(vertices), indices(indices), material(material), vao(0), vbo(0), ebo(0)
	{
		SetupMesh();
	}

	~Mesh()
	{
		if (vao != 0) glDeleteVertexArrays(1, &vao);
		if (vbo != 0) glDeleteBuffers(1, &vbo);
		if (ebo != 0) glDeleteBuffers(1, &ebo);
	}

	void Draw(GLuint shaderProgram, uint32_t instanceCount = 0)
	{
		// Bind textures
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;
		unsigned int normalNr = 1;
		unsigned int heightNr = 1;

		for (unsigned int i = 0; i < material.textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);

			std::string number;
			std::string name = material.textures[i].type;

			if (name == "texture_diffuse")
				number = std::to_string(diffuseNr++);
			else if (name == "texture_specular")
				number = std::to_string(specularNr++);
			else if (name == "texture_normal")
				number = std::to_string(normalNr++);
			else if (name == "texture_height")
				number = std::to_string(heightNr++);

			GLint uniform = glGetUniformLocation(shaderProgram, ("material." + name + number).c_str());
			if (uniform != -1)
				glUniform1i(uniform, i);

			glBindTexture(GL_TEXTURE_2D, material.textures[i].id);
		}
		glActiveTexture(GL_TEXTURE0);

		// Set material properties
		GLint ambientLoc = glGetUniformLocation(shaderProgram, "material.ambient");
		GLint diffuseLoc = glGetUniformLocation(shaderProgram, "material.diffuse");
		GLint specularLoc = glGetUniformLocation(shaderProgram, "material.specular");
		GLint shineLoc = glGetUniformLocation(shaderProgram, "material.shininess");

		if (ambientLoc != -1)
			glUniform3f(ambientLoc, material.ambient[0], material.ambient[1], material.ambient[2]);
		if (diffuseLoc != -1)
			glUniform3f(diffuseLoc, material.diffuse[0], material.diffuse[1], material.diffuse[2]);
		if (specularLoc != -1)
			glUniform3f(specularLoc, material.specular[0], material.specular[1], material.specular[2]);
		if (shineLoc != -1)
			glUniform1f(shineLoc, material.shininess);

		// Draw mesh
		glBindVertexArray(vao);
		if (instanceCount == 0)
			glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		else
			glDrawElementsInstanced(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0, instanceCount);
		glBindVertexArray(0);
	}

	const Material& GetMaterial() const { return material; }
	size_t GetIndexCount() const { return indices.size(); }
};

/*
 * Main GLTF Model class
 */
class GLTFModel
{
private:
	std::vector<Mesh*> meshes;
	std::vector<Texture> textures_loaded;
	std::string directory;
	const aiScene* scene;
	Assimp::Importer importer;

	std::string TextureTypeToString(aiTextureType type)
	{
		switch (type)
		{
		case aiTextureType_DIFFUSE:
			return "texture_diffuse";
		case aiTextureType_SPECULAR:
			return "texture_specular";
		case aiTextureType_NORMALS:
			return "texture_normal";
		case aiTextureType_HEIGHT:
			return "texture_height";
		case aiTextureType_AMBIENT:
			return "texture_ambient";
		default:
			return "texture_unknown";
		}
	}

	GLuint TextureFromFile(const std::string& path, const std::string& directory)
	{
		std::string filename = std::string(path);
		filename = directory + "/" + filename;

		// Check if texture is already loaded
		for (const auto& tex : textures_loaded)
		{
			if (tex.path == filename)
				return tex.id;
		}

		GLuint textureID;
		glGenTextures(1, &textureID);

		// Read image data (using a simple BMP loader or STB image)
		// For production, use stb_image or similar library
		int width, height, nrComponents;
		const unsigned char* data = LoadImageData(filename.c_str(), width, height, nrComponents);

		if (data)
		{
			GLenum format = GL_RGB;
			if (nrComponents == 1)
				format = GL_RED;
			else if (nrComponents == 3)
				format = GL_RGB;
			else if (nrComponents == 4)
				format = GL_RGBA;

			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			FreeImageData(data);

			LOG_ENTRY("log.txt", "Loaded texture at path: %s", filename.c_str());
		}
		else
		{
			// std::cerr << "ERROR: Failed to load texture at path: " << filename << std::endl;
			LOG_ENTRY("log.txt", "ERROR: Failed to load texture at path: %s", filename.c_str());
			// Create a default white texture
			unsigned char defaultData[] = { 255, 255, 255 };
			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, defaultData);
		}

		// Store texture info
		Texture texture;
		texture.id = textureID;
		texture.path = filename;
		textures_loaded.push_back(texture);

		return textureID;
	}

	const unsigned char* LoadImageData(const char* filename, int& width, int& height, int& channels)
	{
		// TODO: Implement image loading (use stb_image or similar)
		// // For now, return nullptr to use default texture
		// width = 1;
		// height = 1;
		// channels = 3;
		// return nullptr;
		return(TextureLoader::LoadTextureImageDataFromFile(filename, width, height, channels));
	}

	void FreeImageData(const unsigned char* data)
	{
		if (data)
			delete[] data; // Note: This assumes the data was allocated with new[]. If using stb_image, use stbi_image_free(data);
	}

	void ProcessNode(aiNode* node, const aiScene* scene)
	{

		LOG_ENTRY("log.txt", "Processing node %s", node->mName.C_Str());

		// Process all meshes in this node
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			meshes.push_back(ProcessMesh(mesh, scene));
		}

		// Process all children
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			ProcessNode(node->mChildren[i], scene);
		}
	}

	Mesh* ProcessMesh(aiMesh* mesh, const aiScene* scene)
	{
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		Material material;

		// Initialize material properties
		material.ambient = glm::vec3(0.2f);
		material.diffuse = glm::vec3(0.8f);
		material.specular = glm::vec3(1.0f);
		material.shininess = 32.0f;

		LOG_ENTRY("log.txt", "Processing mesh %s", mesh->mName.C_Str());
		LOG_ENTRY("log.txt", "Number of vertices: %d", mesh->mNumVertices);
		if(mesh->HasNormals())
		{
			LOG_ENTRY("log.txt", "Mesh has normals");
		}
		else
		{
			LOG_ENTRY("log.txt", "Mesh does not have normals");
		}

		if (mesh->HasTangentsAndBitangents())
		{
			LOG_ENTRY("log.txt", "Mesh has tangents and bitangents");
		}
		else
		{
			LOG_ENTRY("log.txt", "Mesh does not have tangents and bitangents");
		}
		

		// Process vertices
		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;

			// Position
			vertex.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);

			// Normal
			if (mesh->HasNormals())
			{
				vertex.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
			}
			else
			{
				vertex.normal = glm::vec3(0.0f, 0.0f, 1.0f);
			}

			// Texture Coordinates
			if (mesh->mTextureCoords[0])
			{
				vertex.texCoord = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
			}
			else
			{
				vertex.texCoord = glm::vec2(0.0f, 0.0f);
			}

			// Tangent
			if (mesh->HasTangentsAndBitangents())
			{
				vertex.tangent = glm::vec3(mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z);
				vertex.bitangent = glm::vec3(mesh->mBitangents[i].x, mesh->mBitangents[i].y, mesh->mBitangents[i].z);
			}
			else
			{
				vertex.tangent = glm::vec3(1.0f, 0.0f, 0.0f);
				vertex.bitangent = glm::vec3(0.0f, 1.0f, 0.0f);
			}

			vertices.push_back(vertex);
		}

		// Process indices
		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);
			}
		}

		// Process materials
		if (mesh->mMaterialIndex >= 0)
		{
			aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];

			// Load textures
			std::vector<Texture> diffuseMaps = LoadMaterialTextures(mat, aiTextureType_DIFFUSE, "texture_diffuse");
			material.textures.insert(material.textures.end(), diffuseMaps.begin(), diffuseMaps.end());

			std::vector<Texture> specularMaps = LoadMaterialTextures(mat, aiTextureType_SPECULAR, "texture_specular");
			material.textures.insert(material.textures.end(), specularMaps.begin(), specularMaps.end());

			std::vector<Texture> normalMaps = LoadMaterialTextures(mat, aiTextureType_NORMALS, "texture_normal");
			material.textures.insert(material.textures.end(), normalMaps.begin(), normalMaps.end());

			// Load material properties
			aiColor3D color(0.8f, 0.8f, 0.8f);
			mat->Get(AI_MATKEY_COLOR_DIFFUSE, color);
			material.diffuse = glm::vec3(color.r, color.g, color.b);

			mat->Get(AI_MATKEY_COLOR_SPECULAR, color);
			material.specular = glm::vec3(color.r, color.g, color.b);

			mat->Get(AI_MATKEY_COLOR_AMBIENT, color);
			material.ambient = glm::vec3(color.r, color.g, color.b);

			float shininess = 32.0f;
			mat->Get(AI_MATKEY_SHININESS, shininess);
			material.shininess = shininess;
		}

		return new Mesh(vertices, indices, material);
	}

	std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName)
	{
		std::vector<Texture> textures;

		LOG_ENTRY("log.txt", "Loading material textures of type: %s(%d)", typeName.c_str(), mat->GetTextureCount(type));

		for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString str;
			mat->GetTexture(type, i, &str);

			// Check if texture is already loaded
			bool skip = false;
			for (const auto& loaded : textures_loaded)
			{
				if (std::string(str.C_Str()) == loaded.path)
				{
					Texture texture;
					texture.id = loaded.id;
					texture.type = typeName;
					texture.path = str.C_Str();
					textures.push_back(texture);
					skip = true;
					break;
				}
			}

			if (!skip)
			{
				LOG_ENTRY("log.txt", "Loading texture: %s", str.C_Str());
				Texture texture;
				texture.id = TextureFromFile(str.C_Str(), directory);
				texture.type = typeName;
				texture.path = str.C_Str();
				textures.push_back(texture);
			}
		}

		return textures;
	}

public:
	GLTFModel() : scene(nullptr) 
	{
		LOG_ENTRY("log.txt", "GLTF Model Initialized");
	}

	~GLTFModel()
	{
		// Clean up meshes
		for (auto mesh : meshes)
		{
			if (mesh)
				delete mesh;
		}
		meshes.clear();

		// Clean up textures
		for (const auto& tex : textures_loaded)
		{
			glDeleteTextures(1, &tex.id);
		}
		textures_loaded.clear();
	}

	bool LoadModel(const std::string& path)
	{
		LOG_ENTRY("log.txt", "Loading GLTF Model");

		// Extract directory path from file path
		size_t lastSlash = path.find_last_of("/\\");
		directory = (lastSlash == std::string::npos) ? "" : path.substr(0, lastSlash);

		LOG_ENTRY("log.txt", "Loading GLTF Model from path: %s", path.c_str());

		// Load scene using Assimp
		scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenNormals | 
													  aiProcess_CalcTangentSpace | aiProcess_FlipUVs | 
													  aiProcess_PreTransformVertices);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			// std::cerr << "ERROR: Assimp failed to load model: " << importer.GetErrorString() << std::endl;
			LOG_ENTRY("log.txt", "ERROR: Assimp failed to load model: %s", importer.GetErrorString());
			return false;
		}

		// Process root node and all children
		ProcessNode(scene->mRootNode, scene);

		std::cout << "Successfully loaded model with " << meshes.size() << " meshes." << std::endl;
		return true;
	}

	void Draw(GLuint shaderProgram)
	{
		for (auto mesh : meshes)
		{
			if (mesh)
				mesh->Draw(shaderProgram);
		}
	}

	void DrawInstances(GLuint shaderProgram, uint32_t instanceCount)
	{
		for (auto mesh : meshes)
		{
			if (mesh)
				mesh->Draw(shaderProgram, instanceCount);
		}
	}

	size_t GetMeshCount() const { return meshes.size(); }
	Mesh* GetMesh(size_t index) const { return (index < meshes.size()) ? meshes[index] : nullptr; }
	const std::string& GetDirectory() const { return directory; }
};

