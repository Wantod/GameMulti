#ifndef MESH_HPP
# define MESH_HPP

# include <iostream>
# include <vector>
# include <GL/glew.h>

#include "./Shader.hpp"

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Color;
};

class Mesh
{
public:
	Mesh(Shader &shader, std::vector<Vertex> &vertice);
	Mesh(Shader &shader);
	~Mesh();

	void load();
	void setVertice(std::vector<Vertex> &vertice);
	void draw(glm::mat4 model);

protected:
	std::vector<Vertex> vertices;

	GLuint VAO, VBO;
	Shader shader;
};

#endif // MESH_HPP