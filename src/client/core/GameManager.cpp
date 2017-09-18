# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include <glm/gtc/type_ptr.hpp>
#include "GameManager.hpp"
#include "ResourceManager.hpp"
#include "../Game.hpp"

GameManager::GameManager()
{
	run();
}

GameManager::~GameManager()
{
}

GameManager& GameManager::instance() {
    static GameManager theInstance;
    return theInstance;
}

void GameManager::run()
{
	Input input;
	Window win(&input);
	GLFWwindow* window = win.init_glfw("Test", 800, 600);
	Game game(&input, &win);

	GLfloat fpsTime = glfwGetTime();
	GLfloat lastTime = glfwGetTime();
	GLfloat deltaTime = 0.0f;
	GLfloat currentTime;

	int frame = 0;
	int fps = 0;

	ResourceManager::get().init();
	ResourceManager::get().resize(win.getWidth(), win.getHeight());

	while (!game.end())
	{
		if (win.isResize()) {
			game.resize(win.getWidth(), win.getHeight());
			ResourceManager::get().resize(win.getWidth(), win.getHeight());
		}

		// Check and call events
		glfwPollEvents();
		
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
		
		game.update((float)deltaTime);

		if (currentTime - fpsTime >= 1.0) {
			fps = frame;
			frame = 0;
			fpsTime += 1.0;
		}


		// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // mettre en fils de fer
		// glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		
		game.render();
		glfwSwapBuffers(window);

		input.cleanRel();
		input.cleanKey();
	}
}
