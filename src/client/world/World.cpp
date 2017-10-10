#include "World.hpp"

World::World() : chunk(glm::vec3(1, 0, 1))
{
	
	int i = 0;
	for (int x = -2; x < 2; x++)
	for (int z = -2; z < 2; z++)
	{
		i++;
		Chunk *ch = new Chunk(glm::vec3(x, 0, z));
		ch->load();
		_map.emplace(i, ch);
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
