#include "Game.hpp"
#include <iostream>

Game::Game(Input *i, Window *w) : GameInterface(i, w)
{
}

void Game::render()
{

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