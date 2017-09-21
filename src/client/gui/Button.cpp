#include "Button.hpp"

Button::Button(std::string &str, int x, int y) {
	_text = str;
	_x = x;
	_y = y;
	_texture = ResourceManager::get().getTexture("btn.png", true);
}

Button::~Button() {

}

void Button::setText(std::string &str) {

}

bool Button::onClick(int x, int y) {
	return true;
}

void Button::render(Window &window) {
	glm::vec2 posF(window.getWidth() / 2, 24);
	glm::vec2 pos = ResourceManager::get().text.size(_text, 1);
	glDisable(GL_DEPTH_TEST);
	ResourceManager::get().sprit.DrawSprite(_texture, glm::vec2(posF.x - 100, posF.y), glm::vec2(200, 40), 0.0f, glm::vec3(0.0f, 1.0f, 1.0f));
	ResourceManager::get().text.RenderText(_text, posF.x - (pos.x / 2), 50, 1);
}