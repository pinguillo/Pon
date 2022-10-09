#pragma once

class GLFWwindow;
class Input;

class Window
{
public:
	Window(int width, int height, const char* windowName);
	~Window();

	GLFWwindow* getWindow()
	{
		return window; //For some compile error needs to be in the header
	}
	int getWidth();
	int getHeight();
private:
	GLFWwindow* window;
	Input* input;

	int WIDTH, HEIGHT;
};