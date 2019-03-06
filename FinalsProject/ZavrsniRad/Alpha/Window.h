#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <string>
#include <GL\glew.h>
#include <GLFW\glfw3.h>

class Window
{
public:
	Window();
	void InitializeKeyboardKeys();
	Window(GLfloat windowWidth, GLfloat windowHeight);

	~Window();

	int InitialiseWindow();

	GLuint GetBufferWidth() { return _bufferWidth; }
	GLuint GetBufferHeight() { return _bufferHeigth; }


	GLfloat GetXChange();
	GLfloat GetYChange();

	bool *GetKeyboardKeys() { return _keyboardKeys; }
	const int TOTAL_KEYS = 1024;

	bool GetWindowShouldClose() { return glfwWindowShouldClose(_window); }
	void SwapBuffers() { glfwSwapBuffers(_window); }

	//fps
	GLFWwindow* GetWindow() { return _window; }

private:
	GLFWwindow * _window;
	GLint _windowWidth;
	GLint _windowHeigth;
	GLint _bufferWidth;
	GLint _bufferHeigth;

	// camera
	GLfloat _previousX;
	GLfloat _previousY;
	GLfloat _xChange;
	GLfloat _yChange;
	bool _mouseFirstMoved;

	// input
	bool _keyboardKeys[1024];

	void CreateEnableCallbacks();
	static void GetKeyboardInput(GLFWwindow *window, int keyPressed, int keyCode, int action, int mode);
	static void GetMouseInput(GLFWwindow *window, double xPosition, double yPosition);

	void GlfwStandardConfiguration();

};
#endif // !WINDOW_H