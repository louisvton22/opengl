#pragma once
#ifndef MODEL_H
#define MODEL_H

#include "shader.h"
#include "mesh.h"
#include <vector>
#include <cstring>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include "stb_image.h"
#include <glad/glad.h>
#include <iostream>
class Model {


	public:
		Model(const char* path)
		{
			loadModel(path);
		}
		void Draw(Shader &shader);
	private:
		std::vector<Mesh> meshes;
		std::string directory;

		// stores textures we've already loaded to optimize loading times
		std::vector<Texture> textures_loaded;

		void loadModel(std::string path);
		void processNode(aiNode *node, const aiScene *scene);
		Mesh processMesh(aiMesh *mesh, const aiScene *scene);
		std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);


};
#endif