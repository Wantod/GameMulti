#ifndef GAMEINTERFACE_HPP
#define GAMEINTERFACE_HPP

# include "Window.hpp"
# include "Input.hpp"

class GameInterface
{
public:
	GameInterface() : input(nullptr), window(nullptr) {}
	GameInterface(InputManager *i, Window *w) : input(i), window(w) {}
	~GameInterface() {}
	
	virtual void render() = 0;
	virtual void update(float deltatime) = 0;
	virtual void resize(int w, int h) = 0;
	virtual bool end() = 0;

protected:
	InputManager *input;
	Window *window;
};

#endif