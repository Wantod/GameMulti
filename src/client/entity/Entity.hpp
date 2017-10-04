#ifndef ENTITY_HPP
# define ENTITY_HPP

# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include <glm/gtc/type_ptr.hpp>

# include "../Camera.hpp"
# include "../core/Input.hpp"

class Entity
{
public:
	Entity();
	~Entity();

	glm::vec3 getPos() const;

	void update(float deltatime);
	// virtual void render() = 0;

protected:
	glm::vec3 pos;
	glm::vec3 vel;
	glm::vec3 acc;

	float masse;
};

#endif // !ENTITY_HPP