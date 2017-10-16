#include "Player.hpp"

/*
        a8-----a7
      / |     / |
   a5 --|- a6   |
   |    |  |    |
   |   a4--|---a3
   |  /    |  /
  a1 ---- a2 /

*/

std::vector<Vertex> cubeGenerator(float x, float y, float z) {
	std::vector<Vertex> vert;
	glm::vec3 color(1,0,1);
	glm::vec3 point[8] = {
		glm::vec3(-0.5*x,0*y,z*0.5),
		glm::vec3(0.5*x,0*y,z*0.5),
		glm::vec3(0.5*x,0*y,z*-0.5),
		glm::vec3(-0.5*x,0*y,z*-0.5),
		glm::vec3(-0.5*x,1*y,z*0.5),
		glm::vec3(0.5*x,1*y,z*0.5),
		glm::vec3(0.5*x,1*y,z*-0.5),
		glm::vec3(-0.5*x,1*y,z*-0.5)
	};

	// face
	vert.push_back(Vertex { point[0], color });
	vert.push_back(Vertex { point[5], color });
	vert.push_back(Vertex { point[4], color });
	vert.push_back(Vertex { point[0], color });
	vert.push_back(Vertex { point[1], color });
	vert.push_back(Vertex { point[5], color });
	
	//
	vert.push_back(Vertex { point[0], color });
	vert.push_back(Vertex { point[3], color });
	vert.push_back(Vertex { point[2], color });
	vert.push_back(Vertex { point[0], color });
	vert.push_back(Vertex { point[2], color });
	vert.push_back(Vertex { point[1], color });

	color *= 0.1;
	//
	vert.push_back(Vertex { point[2], color });
	vert.push_back(Vertex { point[3], color });
	vert.push_back(Vertex { point[6], color });
	vert.push_back(Vertex { point[6], color });
	vert.push_back(Vertex { point[3], color });
	vert.push_back(Vertex { point[7], color });

	//
	vert.push_back(Vertex { point[4], color });
	vert.push_back(Vertex { point[6], color });
	vert.push_back(Vertex { point[7], color });
	vert.push_back(Vertex { point[4], color });
	vert.push_back(Vertex { point[5], color });
	vert.push_back(Vertex { point[6], color });

	//
	vert.push_back(Vertex { point[1], color });
	vert.push_back(Vertex { point[2], color });
	vert.push_back(Vertex { point[6], color });
	vert.push_back(Vertex { point[1], color });
	vert.push_back(Vertex { point[6], color });
	vert.push_back(Vertex { point[5], color });

	//
	vert.push_back(Vertex { point[0], color });
	vert.push_back(Vertex { point[7], color });
	vert.push_back(Vertex { point[3], color });
	vert.push_back(Vertex { point[0], color });
	vert.push_back(Vertex { point[4], color });
	vert.push_back(Vertex { point[7], color });
	return vert;
}


Player::Player() : Entity(), _speedTimeTmp(0) {
	_speed = false;
	//Shader &shader = ResourceManager::get().getShader("voxel");

	tete.setVertice(cubeGenerator(0.6, 0.6, 0.6));
	tete.load();
	corp.setVertice(cubeGenerator(0.3, 0.6, 0.3));
	corp.load();
	pied1.setVertice(cubeGenerator(0.2, 0.1, 0.2));
	pied1.load();
	pied2.setVertice(cubeGenerator(0.2, 0.1, 0.2));
	pied2.load();
	bras1.setVertice(cubeGenerator(0.2, 0.2, 0.2));
	bras1.load();
	bras2.setVertice(cubeGenerator(0.2, 0.2, 0.2));
	bras2.load();
	// pied1->setVertice(cubeGenerator({glm::vec3(),glm::vec3(),glm::vec3(),glm::vec3(),glm::vec3(),glm::vec3(),glm::vec3(),glm::vec3(),}));
	// pied2->setVertice(cubeGenerator({glm::vec3(),glm::vec3(),glm::vec3(),glm::vec3(),glm::vec3(),glm::vec3(),glm::vec3(),glm::vec3(),}));
	// bras1->setVertice(cubeGenerator({glm::vec3(),glm::vec3(),glm::vec3(),glm::vec3(),glm::vec3(),glm::vec3(),glm::vec3(),glm::vec3(),}));
	// bras2->setVertice(cubeGenerator({glm::vec3(),glm::vec3(),glm::vec3(),glm::vec3(),glm::vec3(),glm::vec3(),glm::vec3(),glm::vec3(),}));
}

Player::~Player() {

}

void Player::update(float deltatime) {
	acc = glm::vec3(0, -20, 0);
	Entity::update(deltatime);
	ResourceManager::get().text.RenderText("TEST " + std::to_string(glm::length(vel)), 10, 100, 1);
	if (pos.y < 0) {
		pos.y = 0;
		vel.y = 0;
	}
}

void Player::render(const Camera *camera) {
	glm::mat4 model(1);
	corp.draw(model);
	model = glm::translate(model, pos);
	model = glm::rotate(model, -glm::radians(camera->getAlpha() + 90), glm::vec3(0, 1, 0));
	
	glm::mat4 model2 = glm::translate(model, glm::vec3(-0.16, 0, 0));
	model2 = glm::translate(model2, glm::vec3(0, 0.2, 0)); // pour la rotation
	model2 = glm::rotate(model2, _speedDeplacement * (float)(cos(glfwGetTime() * 6)), glm::vec3(1, 0, 0));
	model2 = glm::translate(model2, glm::vec3(0, -0.2, 0)); // pour la rotation

	pied1.draw(model2);

	model2 = glm::translate(model, glm::vec3(0.16, 0, 0));
	model2 = glm::translate(model2, glm::vec3(0, 0.2, 0)); // pour la rotation
	model2 = glm::rotate(model2, _speedDeplacement * (float)(-cos(glfwGetTime() * 6)), glm::vec3(1, 0, 0));
	model2 = glm::translate(model2, glm::vec3(0, -0.2, 0)); // pour la rotation

	pied2.draw(model2);
	float deformation = 0.05 * cos(glfwGetTime() * 2);
	// corp
	model = glm::translate(model, glm::vec3(0, 0.2, 0));
	corp.draw(model);

	// bras
	bras1.draw(glm::translate(model, glm::vec3(-0.28, 0.1 - deformation, 0)));
	bras2.draw(glm::translate(model, glm::vec3(0.28, 0.1 - deformation, 0)));

	// tête
	GLfloat angle = -3.141592 / 2;
	if (-1 < 0)
		angle += acos(1);
	else {
		angle += 3.141592 * 2;
		angle -= acos(1);
	}

	model = glm::translate(model, glm::vec3(0, 0.4 + deformation, 0));

	model = glm::translate(model, glm::vec3(0, 0, 0));
	model = glm::rotate(model, glm::radians(camera->getDelta()), glm::vec3(1, 0, 0));
	model = glm::translate(model, -glm::vec3(0, 0, 0));

	tete.draw(model);
}

void Player::updateInput(float deltatime, const Camera *camera) {
	glm::vec3 dir = camera->get_front();
	glm::vec3 dirD(0);
	dir = glm::normalize(glm::vec3(dir.x, 0, dir.z));
	float speed = 5.f;

	// deplacement X - Z
	if (Input::getKey(GLFW_KEY_LEFT_SHIFT))
	{
	}

	if (Input::getKey(GLFW_KEY_W) == 1) {
		if (_speedTimeTmp + 0.6 > glfwGetTime())
			_speed = true;
		std::cout << ((_speed) ? "true" : "false") << ":" << _speedTimeTmp << "-" << glfwGetTime() << std::endl;
		_speedTimeTmp = glfwGetTime();
	}


	if (Input::getKey(GLFW_KEY_W)) {
		dirD += dir;
		if (_speed) speed *= 3;
	} else {
		_speed = false;
	}
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
	if (Input::getKey(GLFW_KEY_SPACE) == 1) {
		vel.y += 8;
		vel.x += dirD.x * speed / 2;
		vel.z += dirD.z * speed / 2;
	}
	
	// std::cout << pos.x << ":" << pos.y << std::endl;
	if (dirD.x != 0 && dirD.z != 0) {
		_speedDeplacement += deltatime;
		if (_speedDeplacement > 1) _speedDeplacement = 1;
		dirD = glm::normalize(dirD);
		pos += dirD * speed * deltatime;
	}
	else {
		_speedDeplacement -= deltatime;
		if (_speedDeplacement < 0) _speedDeplacement = 0;
	}

	if (Input::getKey(GLFW_KEY_G) == 1) {
		vel.x -= dirD.x * 4;
		vel.y += 3;
		vel.z -= dirD.z * 4;
	}

	this->update(deltatime);

	if (pos.y == 0) {
		vel.x = 0;
		vel.z = 0;
	} else {
		vel.x -= vel.x * 0.10 * deltatime;
		vel.z -= vel.z * 0.10 * deltatime;
	}
}
