#ifndef GAME_HPP
#define GAME_HPP

#include <GL/glew.h>
#include "core/GameInterface.hpp"

#include "core\Shader.hpp"
#include "core\Text2D.hpp"
#include "core\Texture.hpp"
#include "core\Sprit2D.hpp"
#include "core\ResourceManager.hpp"

#include "gui\Button.hpp"

class Game : public GameInterface
{
public:
	Game(InputManager *i, Window *w);
	~Game();

	void render();
	void update(float deltatime);
	void resize(int w, int h);
	bool end();

private:
	Texture texture;
	Button btn;
};

#endif // !GAME_HPP
