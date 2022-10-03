#pragma once

#include <memory>

class GLFWwindow;
class Input;
class Window {
public:
	Window(int width, int height, const char* windowName);
	~Window();

	

	GLFWwindow* getWindow() { return window; }
	Input* getInput() { return input; }
	int getWidth() { return WIDTH; }
	int getHeight() { return HEIGHT; }
private:
	GLFWwindow* window;
	Input* input;

	int WIDTH, HEIGHT;
};