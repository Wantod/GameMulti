#include "Camera.hpp"

Camera::Camera()
	: _front(glm::vec3(0.0f)), alpha(0.0f), delta(10.0f), speed(0.1f), _up(glm::vec3(0.0f, 1.0f, 0.0f)) // speed 0.1f
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

glm::vec3 Camera::get_front() const
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
	/*
	glm::vec3 truc;
	 	truc.x = cos(glm::radians(alpha + 120));
	 	truc.y = 1.5;
	 	truc.z = sin(glm::radians(alpha + 120));
		truc.x *= 2;
		truc.z *= 2;

		truc.x -= this->_front.x * 2;
		truc.z -= this->_front.z * 2;
		// truc.x = 1;
		//truc.y = 1;
		//truc.z = -1;
	// camera TPS	
	position.y += 0;
	position.z += sin(glm::radians(alpha + 90)) * 0.5;
	position.x += cos(glm::radians(alpha + 90)) * 0.5;
	glm::vec3 position2 = position;
	position2 -= (this->_front + this->_front + this->_front + this->_front);
	 	return glm::lookAt(position2, position + this->_front, this->_up); // position de eye // point pointer // axe verical, mis en Y (x, y, z)
	*/	
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