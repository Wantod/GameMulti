#include "StateOption.hpp"
#include "Game.hpp"

StateOption::StateOption(GameManager &gm)
	: GameInterface(gm),
	btnReturn(std::string("Retourn"), glm::ivec2(0, 24), glm::ivec2(284, 44))
{
}

void StateOption::render(int fps)
{
	btnReturn.render();
}

void StateOption::update(float deltatime)
{
	if (btnReturn.onClick() && Input::getMouse(GLFW_MOUSE_BUTTON_1) == 1) {
		_gm->setState<StateMain>(*_gm);
	}
}

void StateOption::resize(int w, int h)
{
	btnReturn.resize(w, h);
}

bool StateOption::end()
{
	return (Input::getKey(GLFW_KEY_ESCAPE) == 2 || _gm->window->closeButton()) ? true : false;
}