#ifndef GAME_HPP
#define GAME_HPP

#include <GL/glew.h>
#include "../states/GameInterface.hpp"
#include "../GameManager.hpp"

#include "../core\Shader.hpp"
#include "../core\Text2D.hpp"
#include "../core\Texture.hpp"
#include "../core\Sprit2D.hpp"
#include "../core\ResourceManager.hpp"

#include "../gui\Button.hpp"


#include "../core/Mesh.hpp"
#include "../Camera.hpp"
#include "../entity/Player.hpp"

class Game : public GameInterface
{
public:
	Game(GameManager &gm);
	~Game();

	void render(int fps = 0);
	void update(float deltatime);
	void resize(int w, int h);
	bool end();

private:
	Texture texture;
	Button btnResume;
	Button btnMain;
	Button btnOption;

	std::unique_ptr<Mesh> _cube;
	std::unique_ptr<Camera> _camera;

	Player _player;

	bool menu_focus;
	Shader &shader;
	std::vector<Vertex> vertice;
};

#endif // !GAME_HPP
