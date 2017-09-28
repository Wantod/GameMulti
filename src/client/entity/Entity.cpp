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