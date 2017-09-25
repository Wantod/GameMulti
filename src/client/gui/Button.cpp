#include "Button.hpp"

Button::Button(std::string &str, glm::ivec2 position, glm::ivec2 boxsize) : _position(position), _box(boxsize)
{
	_text = str;
	_texture = ResourceManager::get().getTexture("btn.png", true);
	_texture.setPixel(true);
	// _box = glm::ivec2(284, 44);
	// resize(window.getWidth(), window.getHeight);
}

Button::~Button() {

}

void Button::setPosition(glm::ivec2 position, bool center) {
	_position.x = position.x - (_box.x >> 1);
	_position.y = position.y;
}

void Button::setText(std::string &str) {

}

bool Button::onClick() {
	glm::vec2 posCursor = Input::getCursorPos();
	if (posCursor.x > _position.x && posCursor.y > _position.y && posCursor.x < _position.x + _box.x && posCursor.y < _position.y + _box.y)
		return true;
	return false;
}

void Button::resize(int x, int y) {
	_position.x = (x / 2) - (int)(_box.x / 2);
}

void Button::render() {
	glm::ivec2 boxText = ResourceManager::get().text.size(_text, 1);


	glm::vec2 posCursor = Input::getCursorPos();
	glm::vec3 color(1.0f, 1.0f, 1.0f);

	if (onClick()) {
		color = glm::vec3(0.0f, 1.0f, 0.0f);
	}

	glDisable(GL_DEPTH_TEST);
	ResourceManager::get().sprit.DrawSprite(_texture, _position, _box, 0.0f, color);
	ResourceManager::get().text.RenderText(_text, _position.x + (_box.x >> 1) - (boxText.x >> 1), _position.y + (_box.y >> 1) - (boxText.y >> 1), 1);
}