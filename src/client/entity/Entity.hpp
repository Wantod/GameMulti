#ifndef ENTITY_HPP
# define ENTITY_HPP

class Entity
{
public:
	Entity();
	~Entity();

	glm::vec3 getPos() const;

protected:
	glm::vec3 pos;
	glm::vec3 vel;
	glm::vec3 acc;

	float masse;
};

#endif // !ENTITY_HPP