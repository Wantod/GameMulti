#ifndef CAMERA_HPP_
# define CAMERA_HPP_

# include <iostream>
# include <string>
# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include <glm/gtc/type_ptr.hpp>
# include "Core/Input.hpp"

class Camera
{
public:
	Camera();
	~Camera();

	void update(glm::ivec2 dep);
	float getAlpha();
	
	glm::mat4 lookAt(glm::vec3 position = glm::vec3(0.0f, 30.0f, 30.0f));
	glm::vec3 get_front() const;

private:
	glm::vec3 _front;
	glm::vec3 _up;

	float alpha;
	float delta;
	float speed;

	void updateFront();
};

#endif // !CAMERA_HPP_