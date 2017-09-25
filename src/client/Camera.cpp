#include "Camera.hpp"

Camera::Camera()
	: _front(glm::vec3(0.0f)), alpha(0.0f), delta(10.0f), speed(1.f), _up(glm::vec3(0.0f, 1.0f, 0.0f)) // speed 0.1f
{
	this->updateFront();
}

Camera::~Camera()
{
}

void Camera::updateFront()
{
	glm::vec3 front;

	front.x = cos(glm::radians(this->alpha)) * cos(glm::radians(this->delta));
	front.y = sin(glm::radians(this->delta));
	front.z = sin(glm::radians(this->alpha)) * cos(glm::radians(this->delta));

	this->_front = glm::normalize(front);
}

glm::vec3 Camera::get_front()
{
	return _front;
}

void Camera::update(glm::ivec2 dep)
{
	alpha -= (dep.x * speed);
	delta += (dep.y * speed);

	if (delta > 89.0f)
		delta = 89.0f;
	else if (delta < -89.0f)
		delta = -89.0f;

	this->updateFront();
}

glm::mat4 Camera::lookAt(glm::vec3 position)
{
	return glm::lookAt(position, position + this->_front, this->_up); // position de eye // point pointer // axe verical, mis en Y (x, y, z)
}

// glm::mat4 Camera::lookAtTPS(glm::vec3 position)
// {
// 	glm::vec3 truc;
// 	truc.x = cos(glm::radians(alpha));
// 	truc.y = 0;
// 	truc.z = sin(glm::radians(alpha));
// 	truc *= 2;
// 	return glm::lookAt(position + truc, position + truc + this->_front, this->_up); // position de eye // point pointer // axe verical, mis en Y (x, y, z)
// }

float Camera::getAlpha()
{
	return alpha;
}