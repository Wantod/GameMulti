#include "Mesh.hpp"

Mesh::Mesh(Shader &shader, std::vector<Vertex> &vertice)
	: shader(shader), vertices(vertice)
{
}

Mesh::Mesh(Shader &shader)
	: shader(shader)
{
}

Mesh::Mesh() : shader(ResourceManager::get().getShader("voxel"))
{
}

Mesh::~Mesh()
{
	// Destruction du VBO
	if (glIsBuffer(this->VBO) == GL_TRUE)
		glDeleteBuffers(1, &this->VBO);
	// Destruction du VAO
	if (glIsVertexArray(this->VAO) == GL_TRUE)
		glDeleteVertexArrays(1, &this->VAO);
}

void Mesh::setVertice(std::vector<Vertex> &vertice)
{
	this->vertices = std::vector<Vertex>(vertice);
}

void Mesh::load()
{
	// géréné les identifiant
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);

	// Verrouillage du VAO 
	glBindVertexArray(this->VAO);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);

		// Vertex Positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
		// Vertex Normals
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Color));
	glBindVertexArray(0);
}

void Mesh::draw(glm::mat4 model)
{
	// model = glm::rotate(model, 180.0f, glm::vec3(1, 0, 0));
	shader.use().set("model", model);

	// Draw mesh
	glBindVertexArray(this->VAO);
	glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());
	glBindVertexArray(0);
}