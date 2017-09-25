#ifndef BUTTON_HPP
# define BUTTON_HPP

#include <iostream>
#include "../core/ResourceManager.hpp"
#include "../core/Window.hpp"

class Button
{
public:
	Button(std::string &str, glm::ivec2 position, glm::ivec2 boxsize);
	~Button();
	
	void setText(std::string &str);
	bool onClick();
	void render();
	void resize(int x, int y);
	void setPosition(glm::ivec2 position, bool center = false);

private:
	std::string _text;
	Texture _texture;

	glm::ivec2 _position;
	glm::ivec2 _box;
	glm::ivec2 _textpositionTMP;	
};


#endif // !BUTTON_HPP
