#ifndef BUTTON_HPP
# define BUTTON_HPP

#include <iostream>
#include "../core/ResourceManager.hpp"
#include "../core/Window.hpp"

class Button
{
public:
	Button(std::string &str, int x, int y);
	~Button();
	
	void setText(std::string &str);
	bool onClick(int x, int y);
	void render(Window &win);

	std::string _text;
	int _x;
	int _y;
	int _width;
	int _height;
	Texture _texture;
};


#endif // !BUTTON_HPP
