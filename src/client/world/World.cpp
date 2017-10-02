#include "World.hpp"

World::World() : chunk(glm::vec3(1, 0, 1))
{
	
	
	for (size_t x = 0; x < 2; x++)
	for (size_t z = 0; z < 2; z++)
	{
		Chunk *ch = new Chunk(glm::vec3(x, 0, z));
		ch->load();
		_map.emplace((x << 8) + z, ch);
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
