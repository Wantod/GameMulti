#include "Entity.hpp"

Entity::Entity()
	: pos(0), vel(0), acc(0)
{

}

Entity::~Entity() {

}

glm::vec3 Entity::getPos() const {
	return pos;
}

void Entity::update(float deltatime, const World *world)
{
	vel = vel + acc * deltatime;
	pos = pos + vel * deltatime;

	if (world->getBlock(pos.x, pos.y, pos.z) > 0) {

	}

	posTmp = pos;
}
