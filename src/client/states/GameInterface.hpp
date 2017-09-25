#ifndef GAMEINTERFACE_HPP
#define GAMEINTERFACE_HPP

//# include "../GameManager.hpp"
# include "../core/Window.hpp"
# include "../core/Input.hpp"

class GameManager;

class GameInterface
{
public:
	GameInterface(GameManager &gm);
	~GameInterface();
	
	virtual void render(int fps = 0) = 0;
	virtual void update(float deltatime) = 0;
	virtual void resize(int w, int h) = 0;
	virtual bool end() = 0;

protected:
	GameManager *_gm;
};

#endif