#include "Window.hpp"
#include <string>
#include <SOIL.h>

Window::Window(InputManager *_input) : _width(800), _height(600), fullscreen(false), _window(nullptr), input(_input), _resize(false)
{

}

Window::~Window()
{
	if (_window != nullptr) {
		glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		// glfwSetWindowShouldClose(window, GL_TRUE);
		glfwTerminate();		
	}
}

bool Window::isResize() {
	if (_resize) {
		_resize = false;
		return true;
	}
	return false;
}

void Window::fenetre_key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	std::cout << "appuyer sur " << key << std::endl;
	Window* obj = (Window*)glfwGetWindowUserPointer(window);
	obj->input->keyUpdate(key, scancode, action, mode);
}

void Window::fenetre_mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	Window* obj = (Window*)glfwGetWindowUserPointer(window);
	obj->input->mouseUpdate(button, action, mods);
	// std::cout << "appuyer sur " << button << std::endl;
}

void Window::fenetre_scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	// std::cout << "Scrolling : " << xoffset << ":" << yoffset << std::endl;
}

void Window::fenetre_cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	Window* obj = (Window*)glfwGetWindowUserPointer(window);
	obj->input->posMouseUpdate(xpos, ypos);
	// std::cout << "Sourie : " << xpos << ":" << ypos << std::endl;
}

void Window::fenetre_window_pos_callback(GLFWwindow* window, int xpos, int ypos)
{
	// std::cout << "Fenetre : " << xpos << ":" << ypos << std::endl;
}

void Window::window_iconify_callback(GLFWwindow * window, int iconified)
{
	if (iconified)
	{
		// The window was iconified
	}
	else
	{
		// The window was restored
	}
}

void Window::drop_callback(GLFWwindow* window, int count, const char** paths)
{
	int i;
	for (i = 0; i < count; i++)
		std::cout << paths[i];
	std::cout << std::endl;
}
void Window::fenetre_focus_callback(GLFWwindow* window, int focused)
{
	Window* obj = (Window*)glfwGetWindowUserPointer(window);
	if (focused)
		obj->input->setFocus(true);
	else
		obj->input->setFocus(false);

	if (focused)
		std::cout << "is Focus" << std::endl;
	else
		std::cout << "pas Focus" << std::endl;
}

void Window::fenetre_refresh_callback(GLFWwindow* window)
{
	// std::cout << "rafrechire" << std::endl;
	//int _height, _width;
	//glfwGetFramebufferSize(window, &_width, &_height);
	//glViewport(0, 0, _width, _height);
	// Swap the buffers
	//glfwSwapBuffers(window);
}

void Window::fenetre_resize_callback(GLFWwindow* window, int width, int height)
{
	std::cout << "resize width " << width << ":" << height << std::endl;
	Window* obj = (Window*)glfwGetWindowUserPointer(window);
	obj->setDimansion(width, height);
	glViewport(0, 0, width, height); // Definir l'affichage
	// input.winUpadate(width, height);
}

std::string UnicodeToUTF8(unsigned int codepoint)
{
	std::string out;

	if (codepoint <= 0x7f)
		out.append(1, static_cast<char>(codepoint));
	else if (codepoint <= 0x7ff)
	{
		out.append(1, static_cast<char>(0xc0 | ((codepoint >> 6) & 0x1f)));
		out.append(1, static_cast<char>(0x80 | (codepoint & 0x3f)));
	}
	else if (codepoint <= 0xffff)
	{
		out.append(1, static_cast<char>(0xe0 | ((codepoint >> 12) & 0x0f)));
		out.append(1, static_cast<char>(0x80 | ((codepoint >> 6) & 0x3f)));
		out.append(1, static_cast<char>(0x80 | (codepoint & 0x3f)));
	}
	else
	{
		out.append(1, static_cast<char>(0xf0 | ((codepoint >> 18) & 0x07)));
		out.append(1, static_cast<char>(0x80 | ((codepoint >> 12) & 0x3f)));
		out.append(1, static_cast<char>(0x80 | ((codepoint >> 6) & 0x3f)));
		out.append(1, static_cast<char>(0x80 | (codepoint & 0x3f)));
	}
	return out;
}

void Window::character_callback(GLFWwindow* window, unsigned int codepoint)
{
	Window* obj = (Window*)glfwGetWindowUserPointer(window);
	std::cout << "Test: " << UnicodeToUTF8(codepoint) << std::endl;
	// std::cout << "Clipboard test..." << std::endl;
	// glfwSetClipboardString(window, "test"); // presspapier
}

void Window::setDimansion(int width, int height)
{
	_resize = true;
	_width = width;
	_height = height;
}


GLFWwindow* Window::init_glfw(const char *title, int width, int height)
{
	_width = width;
	_height = height;

	// Init GLFW
	if (!glfwInit())
	{
		std::cerr << "Erreur initialisation GLFW" << std::endl;
		return nullptr;
	}

	//  les option dont a besoin GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE); // mettre a GL_FALSE pour enlever le resize

	// Creation de la fenetre
	_window = glfwCreateWindow(_width, _height, title, nullptr, nullptr);

	// glfwSetWindowUserPointer(window, this);

	if (_window == nullptr) {
		std::cerr << "Fail pour ouvrir la fenetre GLFW, votre systeme ne doit pas etre compatible OpenGL 3.3" << std::endl;
		glfwTerminate();
		return nullptr;
	}

	// Creer le contexte de la fenetre courant
	glfwMakeContextCurrent(_window);
	glfwSetWindowUserPointer(_window, this); // passer le pointer de la classe a la function

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;

	// Initialize GLEW to setup the OpenGL Function pointers
	if (glewInit() != GLEW_OK) {
		std::cerr << "Erreur Initialisation de GLEW" << std::endl;
		glfwTerminate();
		return nullptr;
	}
	glGetError();
	// Set the required callback functions

	glfwSetKeyCallback(_window, fenetre_key_callback); // on appuye sur une touche
	glfwSetMouseButtonCallback(_window, fenetre_mouse_button_callback); // Sourie Touche
	glfwSetScrollCallback(_window, fenetre_scroll_callback); // scolling
	glfwSetCursorPosCallback(_window, fenetre_cursor_position_callback); // position souries

	glfwSetWindowFocusCallback(_window, fenetre_focus_callback); // focus
	glfwSetWindowRefreshCallback(_window, fenetre_refresh_callback); // rafrechire
	glfwSetWindowSizeCallback(_window, fenetre_resize_callback); // redimentionement
	glfwSetWindowPosCallback(_window, fenetre_window_pos_callback); // deplacement de la fenetre
	// glfwSetFramebufferSizeCallback(_window, WindowResizeCallback);
	glfwSetDropCallback(_window, drop_callback); // drop file
	glfwSetCharCallback(_window, character_callback); // detection de touche
	glfwSetWindowIconifyCallback(_window, window_iconify_callback);
	
	glfwSwapInterval(0); // Disable vsync

	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST); // test de profondeur
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	// info Window
	GLint nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
	// nombre fenetre
	int count;
	GLFWmonitor** monitors = glfwGetMonitors(&count);
	std::cout << "vous avez " << count << " ecran" << std::endl;


	GLFWimage icons[1];
	icons[0].pixels = SOIL_load_image("icon.png", &icons[0].width, &icons[0].height, 0, SOIL_LOAD_RGBA);
	std::cout << "ee" << icons[0].width << icons[0].height << std::endl;
	if (!icons[0].pixels) {
		std::cout << "Failed to load texture: " << sizeof(icons[0].pixels) << std::endl;
	}
	glfwSetWindowIcon(_window, 1, icons);

	// GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	// int w, h;
	// glfwGetMonitorPhysicalSize(monitor, &w, &h);
	//glfwSetWindowSize(window, w, h);
	//glfwSetWindowMonitor(window, monitor, 0, 0, w, h, 0);

	// const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	// glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, 0);

	// glfwSetWindowSize(window, w, h);
	// Move window to the upper left corner.
	// glfwSetWindowPos(window, 0, 0);

	glfwGetFramebufferSize(_window, &_width, &_height);	// Detecter la modification du rize
	glViewport(0, 0, _width, _height); // Definir l'affichage

	glfwSetCursorPos(_window, _width / 2, _height / 2);
	glDepthFunc(GL_LESS);


	return _window;
}

bool Window::closeButton()
{
	return glfwWindowShouldClose(_window) ? true : false;
}

void Window::displayCursor(bool value)
{
	if (value)
		glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	else
		glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // GLFW_CURSOR_HIDDEN
}

int Window::getWidth() const
{
	return _width;
}

int Window::getHeight() const
{
	return _height;
}
