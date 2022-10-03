#include "Window.hpp"
#include "Log.hpp"

#include <Glad\glad\glad.h>
#include <GLFW\glfw3.h>

#include <stdexcept>
#include <functional>

#include "Input.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

Window::Window(int width, int height, const char* windowName) : WIDTH(width), HEIGHT(height){
	if (glfwInit() != GLFW_TRUE) {
		PIN_ERROR("Failed to init GLFW");
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	window = glfwCreateWindow(WIDTH, HEIGHT, windowName, nullptr, nullptr);

	if (window == nullptr) {
		glfwTerminate();
		PIN_ERROR("Failed to create window");
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		PIN_ERROR("Failed to initialize GLAD");
	}

	glfwSwapInterval(0);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CW);

	input = new Input(window);
	glfwSetCursorPosCallback(window, input->mouse_position_callback);
	glfwSetMouseButtonCallback(window, input->mouse_button_callback);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}
