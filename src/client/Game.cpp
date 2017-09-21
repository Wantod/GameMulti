#include "Game.hpp"
#include <iostream>

Game::Game(InputManager *i, Window *w) : GameInterface(i, w), btn(std::string("Salut"), 100, 100)
{
	// shText2.compile("./data/Shaders/texture.vs", "./data/Shaders/texture.frag");
	// sprit = new SpriteRenderer(shText2);
	// this->resize(w->getWidth(), w->getHeight());
	texture = ResourceManager::get().getTexture("awesomeface.png", true);
}

Game::~Game()
{
}

void Game::render()
{
	ResourceManager::get().text.RenderText("Petit pierre", 10, 10, 1, glm::vec3(0.7, 0.1, 0.1));
	ResourceManager::get().text.RenderText("Petit pierre", 10, 24, 1, glm::vec3(0.1, 0.1, 0.1));
	ResourceManager::get().sprit.DrawSprite(texture, glm::vec2(window->getWidth() / 2 - 13, window->getHeight() / 2 - 13), glm::vec2(27, 27), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	btn.render(*window);
}

void Game::update(float deltatime)
{
	
}

void Game::resize(int w, int h)
{
}

bool Game::end()
{
	return (input->getKey(GLFW_KEY_ESCAPE) == 2 || window->closeButton()) ? true : false;
}