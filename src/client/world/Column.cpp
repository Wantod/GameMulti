#include "Column.hpp"
#include "World.hpp"
#include "Generation/GeneratorChunk.hpp"

Column::Column(World & world, glm::ivec2 & position)
	: _world(&world), _position(position)
{
}

Column::~Column()
{
}

void Column::load(GeneratorChunk & generator)
{
	// generator.
	_load = true;
}

void Column::setBlock(int x, int y, int z, unsigned int b)
{
	//Chunk *c = getChunk(y >> 4);
	//return (c != nullptr) ? c->getCube(x, y & 15, z) : -1;
	_chunks[y >> 4].setBlock(x, y & 0xF, z, b);
}

unsigned int Column::getBlock(int x, int y, int z) const
{
	return _chunks[y >> 4].getBlock(x, y & 0xF, z);
}
/*
Chunk & Column::getChunk(int y)
{
//	return (y < 0 || y >= _chunks.size()) ? nullptr : _chunks[y];
	return Chunk();
}*/

bool Column::hasLoad() const
{
	return _load;
}
