#include "Entity.hpp"

Entity::Entity()
	: pos(0, 100, 0), vel(0), vel_move(0), acc(0)
{

}

Entity::~Entity() {

}

glm::vec3 Entity::getPos() const {
	return pos;
}

void Entity::update(float deltatime, const World *world)
{
	// vel = vel + acc * dt
	// pos = vel * dt
	vel = vel + acc * deltatime;
	glm::vec3 velocity = (vel + vel_move) * deltatime;


	vitess = vel + vel_move;
	vel_move = {0, 0, 0};
	ground = false;


	// Collision
	pos = this->collide(pos, { velocity.x, 0, 0 }, world);
	pos = this->collide(pos, { 0, 0, velocity.z }, world);
	pos = this->collide(pos, { 0, velocity.y, 0 }, world);

	if (pos.y < -1) {
		pos.y = -1;
		ground = true;
		vel.y = 0;
	}

	if (ground) {
		// frotement 100%
		vel.x = 0;
		vel.z = 0;
	} else {
		// frotement 10%
		vel.x -= vel.x * 0.10 * deltatime;
		vel.z -= vel.z * 0.10 * deltatime;
	}

	//std::cout << "vel: " << vel.x << ':' << vel.y << ':' << vel.z << std::endl;
	//std::cout << "colition vel: " << (int)pos.x << ":" << (int)pos.y << ":" << (int)pos.z << std::endl;
	posTmp = pos;
}

glm::vec3 Entity::collide(glm::vec3 _pos, glm::vec3 _vel, const World * world)
{
	_pos = _pos + _vel;
	
	glm::vec3 box = glm::vec3(0.45f, 1.5f, 0.45f);
	for (int x = floor(_pos.x - box.x); x < _pos.x + box.x; x++)
		for (int y = floor(_pos.y); y < _pos.y + box.y; y++)
			for (int z = floor(_pos.z - box.z); z < _pos.z + box.z; z++)
			{
				auto block = world->getBlock(x, y, z);
				if (block != 0) {
					if (_vel.y > 0) {
						_pos.y = y - box.y;
						vel.y = 0;
					}
					else if (_vel.y < 0) {
						_pos.y = y + 1;
						ground = true;
						vel.y = 0;
					}

					if (_vel.x > 0) {
						_pos.x = x - box.x;
					}
					else if (_vel.x < 0) {
						_pos.x = x + box.x + 1;
					}

					if (_vel.z > 0) {
						_pos.z = z - box.z;
					}
					else if (_vel.z < 0) {
						_pos.z = z + box.z + 1;
					}
				}
			}
	return _pos;
}
