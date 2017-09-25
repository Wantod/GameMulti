#ifndef STATEMAIN_HPP
#define STATEMAIN_HPP

#include "GameInterface.hpp"
#include "../GameManager.hpp"
#include "../gui/Button.hpp"
#include <iostream>

class StateMain: public GameInterface
{
public:
	StateMain(GameManager &gm);
	~StateMain() {}
	
	void render(int fps = 0);
	void update(float deltatime);
	void resize(int w, int h);
	bool end();

protected:
	Button btnQuiter;
	Button btnPlay;
	Button btnOption;
};

#endif // !STATEMAIN_HPP