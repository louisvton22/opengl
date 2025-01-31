#pragma once
#ifndef MESH_H
#define MESH_H
	
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <string>
#include <vector>
#include "shader.h"
#include "assimp/scene.h"
struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture
{
	unsigned int id; 
	std::string type; // diffuse, specular, etc.
	std::string path;
};

class Mesh
{

	public:
		std::vector<Vertex> vertices;
		std::vector<Texture> textures;
		std::vector<unsigned int> indices;

		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

		void Draw(Shader &shader);

		unsigned int VAO;

	private:

		unsigned int VBO, EBO;

		void setupMesh();
};
#endif //MESH_H