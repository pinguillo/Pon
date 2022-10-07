#pragma once
#include "Types\varTypes.hpp"

#include <memory>
#include <chrono>
#include <vector>

#include <glm\glm.hpp>

class Window;
class Input;
class GLFWwindow;
class MeshedObject;
class Camera;
class ResourcePack;

class Engine {
public:
	Engine();
	~Engine();

	void Run();
	void KillEngine();

	void CreateWindow(int width, int height, const char* windowName);


private:
	Window* windowClass;
	GLFWwindow* window;
	Input* input;
	ResourcePack* resourcePack;

	std::chrono::high_resolution_clock::time_point previousTime;
};