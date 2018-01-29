#include "World.hpp"


bool operator==(const glm::ivec2 & left, const glm::ivec2 & right) noexcept
{
	return  (left.x == right.x) &&
		(left.y == right.y);
}
World::World()
{
	
	for (int x = -1; x < 1; x++)
	for (int z = -1; z < 1; z++)
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


glm::vec4 World::TraceRay(glm::vec3 posit, glm::vec3 dir, int max, bool last)
{
	glm::vec3 vox = glm::floor(posit);
	glm::vec3 next(max, max, max);
	glm::vec3 delta(max, max, max);
	glm::vec3 step(0, 0, 0);
	glm::vec3 lastVox(-1);
	glm::vec4 lastBlock = glm::vec4(-1);

	if (this->getBlock(vox[0], vox[1], vox[2]) > 0) {
		if (last)
			return glm::vec4(-1);
		return glm::vec4(vox[0], vox[1], vox[2], 0);
	}

	for (int i = 0; i < 3; ++i) {
		if (dir[i] < 0) {
			step[i] = -1;
			delta[i] = step[i] / dir[i];
			next[i] = (vox[i] - posit[i]) / dir[i];
		}
		else if (dir[i] != 0) {
			step[i] = 1;
			delta[i] = step[i] / dir[i];
			next[i] = ((vox[i] + 1) - posit[i]) / dir[i];
		}
	}

	int nb = 0;
	while (nb < max) {
		lastVox = vox;
		// Perform DDA
		int side = 0;
		for (int i = 1; i < 3; ++i) {
			if (next[side] > next[i]) {
				side = i;
			}
		}
		next[side] += delta[side];
		vox[side] += step[side];

		// Sample volume data at calculated pos and make collision calculations
		if (this->getBlock(vox[0], vox[1], vox[2]) > 0) {
			lastBlock = glm::vec4(lastVox, side);
			if (last)
				return glm::vec4(lastVox, side);
			return glm::vec4(vox[0], vox[1], vox[2], side);
		}
		nb++;
	}
	return glm::vec4(-1); // No voxel found
}