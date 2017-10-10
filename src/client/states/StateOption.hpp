#ifndef STATEOPTION_HPP
#define STATEOPTION_HPP

#include "GameInterface.hpp"
#include "../GameManager.hpp"
#include "../gui/Button.hpp"
#include <iostream>

class StateOption: public GameInterface
{
public:
	StateOption(GameManager &gm);
	~StateOption() {}
	
	void render(int fps = 0);
	void update(float deltatime);
	void resize(int w, int h);
	bool end();

protected:
	Button btnReturn;
};

#endif // !STATEOPTION_HPP
