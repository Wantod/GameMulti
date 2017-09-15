#ifndef GAME_HPP
#define GAME_HPP

#include <GL/glew.h>
#include "core/GameInterface.hpp"

#include "core\Shader.hpp"
#include "core\Text2D.hpp"

class Game : public GameInterface
{
public:
	Game(Input *i, Window *w);

	void render();
	void update(float deltatime);
	void resize(int w, int h);
	bool end();

protected:
	Shader shText;
	TextRenderer text;
};

#endif // !GAME_HPP
