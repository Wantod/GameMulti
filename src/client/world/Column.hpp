#ifndef COLUMN_HPP
#define COLUMN_HPP value

#include "Chunk.hpp"

class World;
class GeneratorChunk;
class Column
{
public:
	Column(World &world, glm::ivec2& position);
	~Column();

	void load();// GeneratorChunk& generator
	void update();
	void render();

	void setBlock(int x, int y, int z, unsigned int b);
	unsigned int getBlock(int x, int y, int z) const;
	
	Chunk *getChunk(int y);
	bool hasLoad() const;

private:
	std::vector<Chunk> _chunks;
	glm::ivec2 _position;
	bool _load;
	World *_world;
};


#endif