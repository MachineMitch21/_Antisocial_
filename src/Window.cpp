#include "Window.h"
#include "stb_image.h"

using antisocial::Window;

Window::Window(const std::string title, int width, int height)
	: 	_title(title),
		_width(width),
		_height(height),
		_originalWidth(_width),
		_originalHeight(_height),
		_minimized(false),
		_isFullScreen(false)
{
	//If glfw fails to initialize glfwTerminate will release any resources.
	if (!init())
		glfwTerminate();
}

/************************************************************************
* The Window class is defined as a friend class of Time in Time.h		*
* Giving it access to these private members								*
* IsClosed is called at the start of each frame making it an acceptable	*
* candidate for updating Time variables									*
************************************************************************/
bool Window::IsClosed()
{
	Time::update_time();
	return glfwWindowShouldClose(_window);
}

void Window::close()
{
	glfwSetWindowShouldClose(_window, GL_TRUE);
}

int Window::getWidth()
{
	return _width;
}

int Window::getHeight()
{
	return _height;
}

void Window::setCursor(bool show)
{
	if (!show) {
		glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		_cursorActive = false;
	}

	else if (show) {
		glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		_cursorActive = true;
	}
}

void Window::setIcon(const std::string path)
{

#ifndef __APPLE__
	if (path != "") {
		int width, height, numComponents;

		GLFWimage icon[1];
		//Loads pixel data from file into GLFWimage structure
		icon[0].pixels = stbi_load(path.c_str(), &width, &height, &numComponents, 4);

		if (icon[0].pixels == NULL) {
			std::cerr << "Failed to load icon image" << std::endl;
			return;
		}

		glfwSetWindowIcon(_window, 1, icon);

		stbi_image_free(icon[0].pixels);
	}
	else {
		glfwSetWindowIcon(_window, 0, NULL);
	}
#else
	std::cout << "Icon cannot be set on OS X" << std::endl;
#endif // __APPLE__
}

bool Window::isResized()
{
	return _isResized;
}

bool Window::isCursorActive()
{
	return _cursorActive;
}

bool Window::isMinimized()
{
	return _minimized;
}

void Window::enableVSYNC(bool enable)
{
	glfwSwapInterval(enable);
}

void Window::setFullScreen(bool doSet)
{
	GLFWvidmode* mode;
	GLFWmonitor* primary;

	primary = glfwGetPrimaryMonitor();
	mode = (GLFWvidmode*)glfwGetVideoMode(primary);

	if (doSet && !_isFullScreen)
	{
		glfwSetWindowMonitor(_window, primary, 0, 0, mode->width, mode->height, mode->refreshRate);
		_isFullScreen = true;
	}
	else if (!doSet && _isFullScreen)
	{
		glfwSetWindowMonitor(_window, NULL, 200, 200, _originalWidth, _originalHeight, mode->refreshRate);
		_isFullScreen = false;
	}
}

void Window::setResizable(bool resizable)
{
	glfwWindowHint(GLFW_RESIZABLE, resizable);
}

void Window::update()
{
	_isResized = false;
	glfwSwapBuffers(_window);
	glfwPollEvents();
}

void Window::clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool Window::init()
{

	bool isInitialized = true;
	GLenum status;

	glfwInit();

	std::cout << "Using GLFW VERSION: " << glfwGetVersionString() << std::endl;

	//specifies GLFW client API VERSION
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	setResizable(true);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	_window = glfwCreateWindow(_width, _height, _title.c_str(), NULL, NULL);

	if (_window == nullptr)
	{
		std::cerr << "Failed to create GLFW window!" << std::endl;
		isInitialized = false;
	}

	if (_window != nullptr)
	{
		glfwMakeContextCurrent(_window);
	}
	glewExperimental = GL_TRUE;

	status = glewInit();

	if (status != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW" << std::endl;
		isInitialized = false;
	}

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glfwGetFramebufferSize(_window, &_width, &_height);
	glViewport(0, 0, _width, _height);

	glfwSetWindowUserPointer(_window, this);

	glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);
	glfwSetScrollCallback(_window, scroll_callback);
	glfwSetWindowIconifyCallback(_window, window_iconify_callback);
	glfwSetErrorCallback(error_callback);

	return isInitialized;
}

Window::~Window()
{
	glfwTerminate();
}

//Callback functions
void antisocial::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	Window* win = (Window*)glfwGetWindowUserPointer(window);

	win->_isResized = true;

	win->_width = width;
	win->_height = height;
	glViewport(0, 0, width, height);
}

void antisocial::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Window* win = (Window*)glfwGetWindowUserPointer(window);
}

void antisocial::window_iconify_callback(GLFWwindow* window, int iconified)
{
	Window* win = (Window*)glfwGetWindowUserPointer(window);

	win->_minimized = iconified;
}

void antisocial::error_callback(int error, const char* description)
{
	//TODO: Create a logging system that can log these errors for future reference
	std::cerr << "ERROR::(" << error << ")::\n" << description << std::endl;
}
