#include "Game.hpp"
#include <iostream>

Game::Game(GameManager &gm)
	: GameInterface(gm), menu_focus(false),
	btnResume(std::string("Back to game"), glm::ivec2(0, 24), glm::ivec2(284, 44)),
	btnOption(std::string("Option"), glm::ivec2(0, 24 + 44 + 10), glm::ivec2(284, 44)),
	btnMain(std::string("save and to menu"), glm::ivec2(0, 24 + (44 + 10) * 2 ), glm::ivec2(284, 44))
{
	// shText2.compile("./data/Shaders/texture.vs", "./data/Shaders/texture.frag");
	// sprit = new SpriteRenderer(shText2);
	// this->resize(w->getWidth(), w->getHeight());
	texture = ResourceManager::get().getTexture("awesomeface.png", true);
}

Game::~Game()
{
}

void Game::render(int fps)
{
	std::string fpsString = std::to_string(fps) + " FPS 1";
	ResourceManager::get().text.RenderText(fpsString, 10, 10, 1, glm::vec3(0.7, 0.1, 0.1));
	ResourceManager::get().text.RenderText("Petit pierre", 10, 110, 1, glm::vec3(0.7, 0.1, 0.1));
	ResourceManager::get().text.RenderText("Petit pierre", 10, 124, 1, glm::vec3(0.1, 0.1, 0.1));
	ResourceManager::get().sprit.DrawSprite(texture, glm::vec2(_gm->window->getWidth() / 2 - 13, _gm->window->getHeight() / 2 - 13), glm::vec2(27, 27), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));

	if (!Input::isFocus())
		menu_focus = true;
	if (menu_focus) {
		btnResume.render();
		btnOption.render();
		btnMain.render();
	}
}

void Game::update(float deltatime)
{
	if (btnResume.onClick() && Input::getMouse(GLFW_MOUSE_BUTTON_1) == 1) {
		menu_focus = false;
	}
	if (btnMain.onClick() && Input::getMouse(GLFW_MOUSE_BUTTON_1) == 1) {
		_gm->setState<StateMain>(*_gm);
	}
	if (Input::getKey(GLFW_KEY_ESCAPE) == 2)
		menu_focus = true;
}

void Game::resize(int w, int h)
{
	btnResume.resize(w, h);
	btnOption.resize(w, h);
	btnMain.resize(w, h);
}

bool Game::end()
{
	return (_gm->window->closeButton()) ? true : false;
}