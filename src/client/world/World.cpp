#include "World.hpp"


bool operator==(const glm::ivec2 & left, const glm::ivec2 & right) noexcept
{
	return  (left.x == right.x) &&
		(left.y == right.y);
}
World::World()
{
	
	for (int x = -2; x < 10; x++)
	for (int z = -2; z < 10; z++)
	{
		Column *col = new Column(*this, glm::ivec2(x, z));
		col->load();
		_map.emplace(glm::ivec2(x, z), col);
	}
}

World::~World() {
	for (auto itr = _map.begin(); itr != _map.end(); itr++) {
		delete itr->second;
	}
}

void World::render() {
	for (auto itr = _map.begin(); itr != _map.end(); itr++) {
		itr->second->render();
	}
}

void World::update() {
}


void World::setBlock(int x, int y, int z, unsigned int b) {
	glm::ivec2 pos(x >> 4, z >> 4);
	if (_map.find(pos) != _map.end())
		_map[pos]->setBlock(x & 0xF, y, z & 0xF, b);
}

unsigned int World::getBlock(int x, int y, int z) const {
	glm::ivec2 pos(x >> 4, z >> 4);
	if (_map.find(pos) != _map.end())
		return _map.at(pos)->getBlock(x & 0xF, y, z & 0xF);
	return 0;
}


