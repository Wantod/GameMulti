#include "World.hpp"

World::World()
{
	
	int i = 0;
	for (int x = -2; x < 2; x++)
	for (int z = -2; z < 2; z++)
	{
		i++;
		Column *col = new Column(*this, glm::ivec2(x, z));
		col->load();
		_map.emplace(i, col);
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
