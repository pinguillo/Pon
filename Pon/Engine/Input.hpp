#pragma once

class GLFWwindow;
class Input {
public:
	Input(GLFWwindow* window);
	~Input() {}

	void processInput();

	static void mouse_position_callback(GLFWwindow* window, double xposIn, double yposIn);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

	bool GetKey(int key);
	bool GetMouseButton(int button);

	float getMouseOffsetX() {
		float tmp = xoffset;
		xoffset = 0;
		return tmp;
	}
	float getMouseOffsetY() {
		float tmp = yoffset;
		yoffset = 0;
		return tmp;
	}

private:
	GLFWwindow* window;

	static bool firstMouse;

	static float lastX;
	static float lastY;

	static float xoffset, yoffset;
};