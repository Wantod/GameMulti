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

	const glm::vec3 getPos() const;

	void setBlock(int x, int y, int z, unsigned int b);
	unsigned int getBlock(int x, int y, int z) const;

private:
	Mesh mesh;
	unsigned int _block[16 * 16 * 16];
	glm::ivec3 _position;
};


#endif // !CHUNK_HPP