#include "Window.h"

Window::Window()
{
	_windowWidth = 1600;
	_windowHeigth = 900;

	InitializeKeyboardKeys();
}

Window::Window(GLfloat windowWidth, GLfloat windowHeight)
{
	_windowWidth = windowWidth;
	_windowHeigth = windowHeight;

	InitializeKeyboardKeys();
}


Window::~Window()
{
	glfwDestroyWindow(_window);
	glfwTerminate();
}

int Window::InitialiseWindow()
{
	// GLFW
	bool initSuccess = glfwInit();
	if (!initSuccess)
	{
		std::cerr << "glfwInit() failed." << std::endl;
		return 1;
	}

	// setting up versions, disabling backward compatibility, enabling forward compatibility and new features
	GlfwStandardConfiguration();

	_window = glfwCreateWindow(_windowWidth, _windowHeigth, "Name:Alpha_REPLACE", NULL, NULL);
	if (!_window)
	{
		std::cerr << "GLFW window creation failed." << std::endl;
		glfwTerminate();
		return 1;
	}

	// getting and saving information of window size in pixels
	glfwGetFramebufferSize(_window, &_bufferWidth, &_bufferHeigth);
	// activating(drawing) window as main window - switching state context
	glfwMakeContextCurrent(_window);
	// locking mouse to screen, hiding cursor
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// 1st part camera pointer
	glfwSetWindowUserPointer(_window, this);

	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, _bufferWidth, _bufferHeigth);

	// GLEW
	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		std::cerr << "Error :" << glewGetErrorString(error) << std::endl;
		glfwDestroyWindow(_window);
		glfwTerminate();
		return 1;
	}

	CreateEnableCallbacks();
	return 0;
}

void Window::InitializeKeyboardKeys()
{
	for (size_t i = 0; i < TOTAL_KEYS; i++)
	{
		_keyboardKeys[i] = false;
	}
}

void Window::CreateEnableCallbacks()
{
	glfwSetKeyCallback(_window, GetKeyboardInput);
	glfwSetCursorPosCallback(_window, GetMouseInput);
}

void Window::GetKeyboardInput(GLFWwindow * window, int key, int code, int action, int mode)
{
	// 2nd part camera pointer
	Window * newWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			newWindow->_keyboardKeys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			newWindow->_keyboardKeys[key] = false;
		}
	}
}

void Window::GetMouseInput(GLFWwindow * window, double xPosition, double yPosition)
{
	// 2nd part camera pointer
	Window * newWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
	if (newWindow->_mouseFirstMoved)
	{
		newWindow->_previousX = xPosition;
		newWindow->_previousY = yPosition;
		newWindow->_mouseFirstMoved = false;
	}
	// cam left right?
	newWindow->_xChange = xPosition - newWindow->_previousX;
	//camera up/down, if I switch thing on right it will go in reverse
	newWindow->_yChange = newWindow->_previousY - yPosition;

	newWindow->_previousX = xPosition;
	newWindow->_previousY = yPosition;
}

void Window::GlfwStandardConfiguration()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glewExperimental = GL_TRUE;
}

GLfloat Window::GetXChange()
{
	GLfloat theChange = _xChange;
	_xChange = 0.0f;
	return theChange;
}

GLfloat Window::GetYChange()
{
	GLfloat theChange = _yChange;
	_yChange = 0.0f;
	return theChange;
}