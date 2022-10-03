#include "Engine\Engine.hpp"


int main() {
	Engine* eng = new Engine();
	eng->CreateWindow(800, 600, "I don't like where this is going");
	eng->Run();

	return 0;
}