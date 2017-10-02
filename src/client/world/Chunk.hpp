#ifndef CHUNK_HPP
# define CHUNK_HPP

# include "../core/Mesh.hpp"

class Chunk
{
public:
	Chunk(glm::ivec3 pos);
	~Chunk();

	void load();
	void update();
	void render();

private:
	Mesh mesh;
	glm::ivec3 _position;
};


#endif // !CHUNK_HPP