#include "Input.hpp"


Input::Input() : _cursor(0),_cursorRel(0), _terminer(false), _window(nullptr), _focus(true), _width(0), _height(0), _resize(false), _firstPos(true), _razRel(false)
{
	for (size_t i = 0; i <= GLFW_KEY_LAST; i++)
		_key[i] = 0;

	for (size_t i = 0; i <= GLFW_MOUSE_BUTTON_LAST; i++)
		_mouse[i] = 0;
}


Input::~Input()
{
}

void Input::load(GLFWwindow* window, int height, int width)
{
	_window = window;
	_width = width;
	_height = height;
}

void Input::keyUpdate(int key, int scancode, int action, int mode)
{
	(void)mode;

	if (key < 0 || key > GLFW_KEY_LAST)
		return;

	if (action == GLFW_PRESS || action == GLFW_REPEAT)
		_key[key] = (_key[key] > 0) ? 2 : 1;
	else if (action == GLFW_RELEASE)
		_key[key] = (_key[key] == -1) ? 0 : -1;
}

void Input::mouseUpdate(int button, int action, int mods)
{
	if (button < 0 || button > GLFW_MOUSE_BUTTON_LAST)
		return;

	if (action == GLFW_PRESS || action == GLFW_REPEAT)
		_mouse[button] = (_mouse[button] > 0) ? 2 : 1;
	else if (action == GLFW_RELEASE)
		_mouse[button] = (_mouse[button] == - 1) ? 0 : -1;
}

void Input::posMouseUpdate(double xpos, double ypos)
{
	if (!_razRel) {
		_cursorRel.x += _cursor.x - xpos;
		_cursorRel.y += _cursor.y - ypos;
	}
	else
		_razRel = false;

	_cursor.x = xpos;
	_cursor.y = ypos;
}

void Input::winUpadate(int width, int height)
{
	if (width != _width || height != _height)
		_resize = true;

	_width = width;
	_height = height;

}

void Input::displayCursor(bool value)
{
	if (_window == nullptr)
		return;

	if (value)
		glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	else
		glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // GLFW_CURSOR_HIDDEN
	_razRel = true;
	this->cleanRel();
}

void Input::captureCursor(bool value) const
{

}

// get
bool Input::terminer() const
{
	if (_window != nullptr && glfwWindowShouldClose(_window))
		return true;
	//if (_key[GLFW_KEY_ESCAPE] == true)
	//	return true;
	return false;
}

void Input::cleanKey()
{
	for (int i = 0; i < GLFW_KEY_LAST; i++)
		if (_key[i] == 1)
			_key[i] = 2;
		else if (_key[i] == -1)
			_key[i] = 0;

	for (int i = 0; i < GLFW_MOUSE_BUTTON_LAST; i++)
		if (_mouse[i] == 1)
			_mouse[i] = 2;
		else if (_mouse[i] == -1)
			_mouse[i] = 0;
}

/*
** @param key: numero de la touche du clavier
** return (-1) relache (0) est relacher (1) appuy (2) est appuyer
*/
int8_t Input::getKey(int key) const
{
	if (key < 0 || key > GLFW_KEY_LAST)
		return 0;
	return _key[key];
}

/*
** @param key: numero du boutton de la sourie
** (false) relacher, (true) appuyer
*/
int8_t Input::getMouse(int key) const
{
	if (key < 0 || key > GLFW_MOUSE_BUTTON_LAST)
		return 0;
	return _mouse[key];
}



bool Input::isFocus() const
{
	return _focus;
}

bool Input::isResize()
{
	if (_resize) {
		_resize = false;
		return true;
	}

	return false;
}

// Position du Curseur
const glm::ivec2& Input::getCursorPos() const
{
	return _cursor;
}

const glm::ivec2& Input::getCursorRel() const
{
	return _cursorRel;
}

void Input::cleanRel()
{
	_cursorRel = glm::ivec2(0);
}

// SET
void Input::setWindow(GLFWwindow* window)
{
	_window = window;
}

void Input::setFocus(bool focus)
{
	if (!focus)
		displayCursor(true);
	_focus = focus;
}