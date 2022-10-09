#include "Input.hpp"

#include <GLFW\glfw3.h>

Input* Input::inputInstance = 0;

bool Input::firstMouse;
float Input::lastX, Input::lastY;
float Input::xoffset, Input::yoffset;

Input::Input()
{
	firstMouse = true;
}

Input::~Input()
{
}

void Input::SetWindow(GLFWwindow* _window)
{
	window = _window;
}

Input* Input::GetInputInstance()
{
	if (inputInstance == nullptr)
	{
		inputInstance = new Input();
	}

	return inputInstance;
}

void Input::processInput()
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

void Input::mouse_position_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	xoffset = xpos - lastX;
	yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;
}

void Input::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{

}

bool Input::GetKey(int key)
{
	return glfwGetKey(window, key) == GLFW_PRESS;
}

bool Input::GetMouseButton(int button)
{
	return glfwGetMouseButton(window, button) == GLFW_PRESS;
}

float Input::getMouseOffsetX()
{
	float tmp = xoffset;
	xoffset = 0;
	return tmp;
}

float Input::getMouseOffsetY()
{
	float tmp = yoffset;
	yoffset = 0;
	return tmp;
}
