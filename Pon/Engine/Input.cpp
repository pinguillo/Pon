#include "Input.hpp"

#include <GLFW\glfw3.h>

bool Input::firstMouse;
float Input::lastX, Input::lastY;
float Input::xoffset, Input::yoffset;

Input::Input(GLFWwindow* window) : window(window) {
	firstMouse = true;
}

void Input::processInput() {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

void Input::mouse_position_callback(GLFWwindow* window, double xposIn, double yposIn) {
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);
	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	xoffset = xpos - lastX;
	yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;
}

void Input::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {

}

bool Input::GetKey(int key) {
	return glfwGetKey(window, key) == GLFW_PRESS;
}

bool Input::GetMouseButton(int button) {
	return glfwGetMouseButton(window, button) == GLFW_PRESS;
}
