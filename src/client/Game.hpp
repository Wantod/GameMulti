#ifndef GAME_HPP
#define GAME_HPP

#include "core/GameInterface.hpp"

class Game : public GameInterface
{
public:
	Game(Input *i, Window *w);

	void render();
	void update(float deltatime);
	void resize(int w, int h);
	bool end();
};

#endif // !GAME_HPP
