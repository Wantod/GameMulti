#include "Player.hpp"

Player::Player() : Entity() {

}

Player::~Player() {

}

void Player::updateInput(float deltatime, const Camera *camera) {
	glm::vec3 dir = camera->get_front();
	glm::vec3 dirD(0);
	dir = glm::normalize(glm::vec3(dir.x, 0, dir.z));


	// deplacement X - Z
	// if (input->getKey(GLFW_KEY_LEFT_SHIFT)) // input->getKey(GLFW_KEY_LEFT_SHIFT)
	// {
	// 	speedKeys *= 2;
	// }

	if (Input::getKey(GLFW_KEY_W))
		dirD += dir;
	if (Input::getKey(GLFW_KEY_S))
		dirD -= dir;
	if (Input::getKey(GLFW_KEY_D)) {
		dirD.x -= dir.z;
		dirD.z += dir.x;
	}
	if (Input::getKey(GLFW_KEY_A)) {
		dirD.x += dir.z;
		dirD.z -= dir.x;
	}
	std::cout << pos.x << ":" << pos.y << std::endl;
	if (dirD.x != 0 && dirD.z != 0) {
		dirD = glm::normalize(dirD);
		pos += dirD * (deltatime * 5);
	}
}
