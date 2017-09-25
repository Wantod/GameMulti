#ifndef INPUT_HPP_
# define INPUT_HPP_

# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include <glm/gtc/type_ptr.hpp>
# include <glfw3.h>
# include <cstdint>
# include <iostream>
class InputManager
{
public:
	InputManager();
	~InputManager();

	void load(GLFWwindow* window, int height, int width);

	void keyUpdate(int key, int scancode, int action, int mode);
	void mouseUpdate(int button, int action, int mods);
	//void joyUpdate();
	void winUpadate(int width, int height);
	void posMouseUpdate(double xpos, double ypos);

	bool terminer() const;
	void cleanRel();

	// modification cureseur
	void displayCursor(bool value);
	void captureCursor(bool value) const;

	// GET
	int8_t getKey(int key) const;
	int8_t getMouse(int key) const;
	void cleanKey();
	bool isFocus() const;
	bool isResize();

	const glm::ivec2& getCursorPos() const;
	const glm::ivec2& getCursorRel() const;

	// SET
	void setWindow(GLFWwindow* window);
	void setFocus(bool focus);


	void setTextInput(std::string text);
	std::string getTextInput();
	void activText(bool active);

private:
	GLFWwindow* _window;
	int8_t _key[GLFW_KEY_LAST + 1];
	int8_t _mouse[GLFW_MOUSE_BUTTON_LAST + 1];
	//bool _joystrick[GLFW_JOYSTICK_LAST + 1];

	// dimention fenetre
	int _height;
	int _width;

	// cursor
	glm::ivec2 _cursor;
	glm::ivec2 _cursorRel;
	bool _razRel;
	bool _firstPos;

	std::string _textInput;
	bool inputTextAccept;

	// autre
	bool _terminer;
	bool _focus;
	bool _resize;
};

class Input
{
public:
	Input();
	~Input();

	static InputManager& get();

	static 	int8_t getKey(int key);
	static 	int8_t getMouse(int key);
	static 	bool isFocus();

	static const glm::ivec2& getCursorPos();
	static const glm::ivec2& getCursorRel();

	static std::string getTextInput();
	static void activText(bool activ);
};

#endif // !INPUT_HPP_
