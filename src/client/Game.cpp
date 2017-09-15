#include "Game.hpp"
#include <iostream>


Game::Game(Input *i, Window *w) : GameInterface(i, w), text(200, 100)
{
	shText.compile("./data/Shaders/text.vs", "./data/Shaders/text.frag");
	text.TextShader = shText;
	text.update(w->getWidth(), w->getHeight());
	text.Load("./data/Fonts/Arial-Unicode-MS.ttf", 12);
}


void Game::render()
{
	text.RenderText("Petit pierre", 10, 10, 1, glm::vec3(0, 0, 0));
}

void Game::update(float deltatime)
{
	
}

void Game::resize(int w, int h)
{
	text.update(w, h);
}

bool Game::end()
{
	return (input->getKey(GLFW_KEY_ESCAPE) == 2 || window->closeButton()) ? true : false;
}