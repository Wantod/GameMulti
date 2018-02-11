#include "GameManager.hpp"

GameManager::GameManager()
{
	run();
}

GameManager::~GameManager()
{
}

/*
GameManager& GameManager::instance() {
    static GameManager theInstance;
    return theInstance;
}*/



void GameManager::run()
{
	InputManager &input = Input::get();
	window = std::make_unique<Window>(&input);
	GLFWwindow* win = window->init_glfw("Test", 800, 600);
	_state = std::make_unique<StateMain>(*this);
	GLfloat fpsTime = glfwGetTime();
	GLfloat lastTime = glfwGetTime();
	GLfloat deltaTime = 0.0f;
	GLfloat currentTime;

	int frame = 0;
	int fps = 0;

	GLfloat minTime = 0.0f;
	GLfloat minTimeTmp = 1000.0f;

	ResourceManager::get().init();
	ResourceManager::get().resize(window->getWidth(), window->getHeight());

	_state->resize(window->getWidth(), window->getHeight());

	while (!_state->end())
	{
		if (window->isResize()) {
			_state->resize(window->getWidth(), window->getHeight());
			ResourceManager::get().resize(window->getWidth(), window->getHeight());
		}

		
		// clean
		glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		// fps
		currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;
		frame++;

		// Mettre en pause le jeux pour reduire la consomation du CPU
		//if (deltaTime < 1) {
		//	std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1 - (deltaTime))));
		//}
		
		_state->update((float)deltaTime);

		if (minTime < deltaTime)
			minTime = deltaTime;

		if (currentTime - fpsTime >= 1.0) {
			fps = frame / (currentTime - fpsTime);
			fps = (int) (1 / minTime);
			fpsTime = currentTime;
			frame = 0;
			minTime = 0.f;
		}


		// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // mettre en fils de fer
		// glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		
		_state->render(fps);
		glfwSwapBuffers(win);


		if (_stateChange) {
			_stateChange = false;
			_state = std::move(_stateTmp);
			_state->resize(window->getWidth(), window->getHeight());
		}

		input.cleanRel();
		input.cleanKey();

		// Check and call events
		glfwPollEvents();
	}
}
