#include "Window.hpp"
#include <string>

Window::Window() : _with(800), height(600), fullscreen(false), _window(nullptr)
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

void Window::fenetre_key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	std::cout << "appuyer sur " << key << std::endl;
	Window* obj = (Window*)glfwGetWindowUserPointer(window);
	//input.keyUpdate(key, scancode, action, mode);
}

void Window::fenetre_mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	// input.mouseUpdate(button, action, mods);
	// std::cout << "appuyer sur " << button << std::endl;
}

void Window::fenetre_scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	// std::cout << "Scrolling : " << xoffset << ":" << yoffset << std::endl;
}

void Window::fenetre_cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	// input.posMouseUpdate(xpos, ypos);
	//std::cout << "Sourie : " << xpos << ":" << ypos << std::endl;
}

void Window::fenetre_window_pos_callback(GLFWwindow* window, int xpos, int ypos)
{
	// std::cout << "Fenetre : " << xpos << ":" << ypos << std::endl;
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
	// if (focused)
	// 	input.setFocus(true);
	// else
	// 	input.setFocus(false);

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

	//glfwSwapBuffers(window);
}

void Window::fenetre_resize_callback(GLFWwindow* window, int width, int height)
{
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
	std::cout << "Test: " << UnicodeToUTF8(codepoint) << std::endl;
	// std::cout << "Clipboard test..." << std::endl;
	// glfwSetClipboardString(window, "test"); // presspapier
}

GLFWwindow* Window::init_glfw(const char *title, int width, int height)
{
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
	GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);

	// glfwSetWindowUserPointer(window, this);

	if (window == nullptr) {
		std::cerr << "Fail pour ouvrir la fenetre GLFW, votre systeme ne doit pas etre compatible OpenGL 3.3" << std::endl;
		glfwTerminate();
		return nullptr;
	}

	// Creer le contexte de la fenetre courant
	glfwMakeContextCurrent(window);
	glfwSetWindowUserPointer(window, this); // passer le pointer de la classe a la function

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

	glfwSetKeyCallback(window, fenetre_key_callback); // on appuye sur une touche
	glfwSetMouseButtonCallback(window, fenetre_mouse_button_callback); // Sourie Touche
	glfwSetScrollCallback(window, fenetre_scroll_callback); // scolling
	glfwSetCursorPosCallback(window, fenetre_cursor_position_callback); // position souries

	glfwSetWindowFocusCallback(window, fenetre_focus_callback); // focus
	glfwSetWindowRefreshCallback(window, fenetre_refresh_callback); // rafrechire
	glfwSetWindowSizeCallback(window, fenetre_resize_callback); // redimentionement
	glfwSetWindowPosCallback(window, fenetre_window_pos_callback); // deplacement de la fenetre
	// glfwSetFramebufferSizeCallback(_window, WindowResizeCallback);
	glfwSetDropCallback(window, drop_callback); // drop file
	glfwSetCharCallback(window, character_callback); // detection de touche
	
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

	_window = window;
	return window;
}