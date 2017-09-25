#include "StateMain.hpp"
#include "Game.hpp"
#include "StateOption.hpp"

StateMain::StateMain(GameManager &gm)
	: GameInterface(gm),
	btnPlay(std::string("Singleplayer"), glm::ivec2(0, 24), glm::ivec2(284, 44)),
	btnOption(std::string("option"), glm::ivec2(0, 24 + 44 + 10), glm::ivec2(284, 44)),
	btnQuiter(std::string("Quit Game"), glm::ivec2(0, 24 + (44 + 10) * 2 ), glm::ivec2(284, 44))
{
}

void StateMain::render(int fps)
{
	btnPlay.render();
	btnOption.render();
	btnQuiter.render();
}

void StateMain::update(float deltatime)
{
	if (btnPlay.onClick() && Input::getMouse(GLFW_MOUSE_BUTTON_1) == 1) {
		_gm->setState<Game>(*_gm);
	}
	if (btnOption.onClick() && Input::getMouse(GLFW_MOUSE_BUTTON_1) == 1) {
		_gm->setState<StateOption>(*_gm);
	}
}

void StateMain::resize(int w, int h)
{
	btnPlay.resize(w, h);
	btnOption.resize(w, h);
	btnQuiter.resize(w, h);
}

bool StateMain::end()
{
	return (Input::getKey(GLFW_KEY_ESCAPE) == 2 || _gm->window->closeButton() || (btnQuiter.onClick() && Input::getMouse(GLFW_MOUSE_BUTTON_1) == 1)) ? true : false;
}