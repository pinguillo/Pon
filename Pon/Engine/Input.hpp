#pragma once

class GLFWwindow;
class Input {
public:
	Input();
	Input(const Input& other) = delete;
	Input& operator=(const Input& other) = delete;
	~Input();

	void SetWindow(GLFWwindow* window);

	static Input* GetInputInstance();

	void processInput();

	static void mouse_position_callback(GLFWwindow* window, double xposIn, double yposIn);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

	bool GetKey(int key);
	bool GetMouseButton(int button);

	float getMouseOffsetX();
	float getMouseOffsetY();


private:
	GLFWwindow* window;
	static Input* inputInstance;

	static bool firstMouse;

	static float lastX;
	static float lastY;

	static float xoffset, yoffset;
};