#ifndef ENTITY_HPP
# define ENTITY_HPP

# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include <glm/gtc/type_ptr.hpp>

# include "../world/World.hpp"
# include "../Camera.hpp"
# include "../core/Input.hpp"

class Entity
{
public:
	Entity();
	~Entity();

	glm::vec3 getPos() const;

	void update(float deltatime, const World *world);
	// virtual void render() = 0;
	glm::vec3 collide(glm::vec3 _pos, glm::vec3 _vel, const World * world);

protected:
	glm::vec3 posTmp;
	glm::vec3 pos;
	glm::vec3 vel;
	glm::vec3 acc;
	glm::vec3 vel_move;

	float masse;
	bool ground = false;
	bool flying = false;
};

#endif // !ENTITY_HPP