#ifndef WINDOW_HPP
# define WINDOW_HPP

# include <iostream>
# include <GL/glew.h>
# include <GLFW/glfw3.h>

// TEST
# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include <glm/gtc/type_ptr.hpp>
# include <map>
# include <thread>
# include <chrono>
# include <thread>
# include <cstdint> // pour uint8_t

# include "Input.hpp"

class Window
{
public:
	Window(Input *input);
	~Window();

	GLFWwindow* init_glfw(const char *title, int width, int height);

	// callback
	static void fenetre_key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void fenetre_mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void fenetre_scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	static void fenetre_cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

	static void fenetre_focus_callback(GLFWwindow* window, int focused);
	static void fenetre_refresh_callback(GLFWwindow* window);
	static void fenetre_resize_callback(GLFWwindow* window, int width, int height);

	static void drop_callback(GLFWwindow* window, int count, const char** paths);
	static void character_callback(GLFWwindow* window, unsigned int codepoint);
	static void fenetre_window_pos_callback(GLFWwindow* window, int xpos, int ypos);
	static void window_iconify_callback(GLFWwindow* window, int iconified);

	void setDimansion(int width, int height);
	bool closeButton();
	void displayCursor(bool value);

	Input *input;
protected:
	GLFWwindow* _window;
	int fullscreen;

	int _width;
	int _height;
};

#endif // !WINDOW_HPP