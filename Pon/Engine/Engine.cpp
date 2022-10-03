#include "../Utils/ImGui.hpp"

#include "Engine.hpp"

#include "Window.hpp"
#include "Model/Model.hpp"
#include "debugMesh.hpp"
#include "Components\Camera.hpp"

#include "Phys\AABB.hpp"

#include "Input.hpp"

#include "Log.hpp"

#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>


Engine::Engine()
{

}

Engine::~Engine()
{

}

void Engine::Run()
{
	Camera* cam = new Camera(glm::vec3(0.0f, 0.0f, 5.0f));
	glm::vec3 camOffset = glm::vec3(-8.0f, 8.0f, 8.0f);
	cam->SetAngle(-45.0, -35.0f);
	//cam->Position = plr.getPosition() + camOffset;

	glm::mat4 projection = glm::perspective(glm::radians(cam->Zoom), (float)windowClass->getWidth() / (float)windowClass->getHeight(), 0.01f, 1000.0f);

	glm::vec3 directional = glm::vec3(-0.2f, -1.0f, -0.3f);

	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f,  0.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
	};

	
	DebugMesh debugBox = DebugMesh();
	debugBox.setScale({ 1.0f, 1.0f, 1.0f });
	DebugMesh debugBox2 = DebugMesh();
	debugBox2.setScale({ 1.0f, 1.0f, 1.0f });
	cam->Position = debugBox.getPosition() + camOffset;
	
	AABB ab = AABB();

	BoxCollider bx = BoxCollider(2.0f, 2.0f, 2.0f);

	ab.AddCollider(bx);
	bx.position = glm::vec3(0.0f, -5.0f, 0.0f);
	ab.AddCollider(bx);

	PIN_INFO("Load Model");
	Model mmm = Model();
	mmm.Loadmdl("Assets/Models/cor.obj");
	//mmm.setScale({ 0.1f, 0.1f, 0.1f });

	ImGuiLayer gui = ImGuiLayer(window);
	bool pause = true;
	while (!glfwWindowShouldClose(window)) {
		// Delta time
		auto currentTime = std::chrono::high_resolution_clock::now();
		auto frameTime = std::chrono::duration<double>();
		if (previousTime.time_since_epoch().count()) {
			frameTime = currentTime - previousTime;
		}

		previousTime = currentTime;
		auto deltaTime = (float)frameTime.count();

		// Input
		input->processInput();

		if (input->GetMouseButton(GLFW_MOUSE_BUTTON_RIGHT)) {
			if (input->GetKey(GLFW_KEY_W)) {
				cam->ProcessKeyboard(FORWARD, deltaTime);
			}
			if (input->GetKey(GLFW_KEY_S)) {
				cam->ProcessKeyboard(BACKWARD, deltaTime);
			}
			if (input->GetKey(GLFW_KEY_A)) {
				cam->ProcessKeyboard(LEFT, deltaTime);
			}
			if (input->GetKey(GLFW_KEY_D)) {
				cam->ProcessKeyboard(RIGHT, deltaTime);
			}

			cam->ProcessMouseMovement(input->getMouseOffsetX(), input->getMouseOffsetY());
		}else {
			//plr.Step(deltaTime);
			
			//cam->Position = plr.getPosition() + camOffset;
			//cam->SetAngle(-45.0, -35.0f);
		}
		if (input->GetKey(GLFW_KEY_F)) { pause = false; }

		ab.Step();
		if (!pause) {
			if (!ab.colliders[0].colliding) {
				ab.colliders[0].position = glm::vec3(
					ab.colliders[0].position.x,
					ab.colliders[0].position.y - (0.8 * deltaTime),
					ab.colliders[0].position.z
				);
			}
		}
		debugBox.setPosition({ ab.colliders[0].position.x,ab.colliders[0].position.y,ab.colliders[0].position.z });
		debugBox2.setPosition({ ab.colliders[1].position.x,ab.colliders[1].position.y,ab.colliders[1].position.z });

		// Clear screen
		glClearColor(0.9f, 0.7f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Draw
		//DrawScene(meshedObjects, cam, directional, pointLightPositions, projection);
		glm::mat4 vm = cam->GetViewMatrix();


		
		debugBox.Draw(projection, vm);

		debugBox2.Draw(projection, vm);

		mmm.Draw(projection, vm);
		

		float v3[] = { directional.x, directional.y, directional.z };
		float sb3[] = { ab.colliders[1].position.x, ab.colliders[1].position.y, ab.colliders[1].position.z };
		float b3[] = { ab.colliders[0].position.x, ab.colliders[0].position.y, ab.colliders[0].position.z };

		gui.Begin();
		{
			ImGuiIO& io = ImGui::GetIO(); (void)io;

			ImGui::Begin("Performance");
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
			ImGui::End();
			/*
			ImGui::Begin("Light properties");
			ImGui::SliderFloat3("Directional Light", v3, -255.0f, 255.0f);
			ImGui::End();
			*/
			ImGui::Begin("Bawx");
			ImGui::SliderFloat3("Static bawx position", sb3, -10.0f, 10.0f);
			ImGui::SliderFloat3("Moving bawx position", b3, -10.0f, 10.0f);
			ImGui::End();
		}
		gui.End();

		directional = glm::vec3(v3[0], v3[1], v3[2]);
		ab.colliders[1].position = glm::vec3(sb3[0], sb3[1], sb3[2]);
		ab.colliders[0].position = glm::vec3(b3[0], b3[1], b3[2]);

		// Events/Buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	KillEngine();
}

void Engine::KillEngine() {
	glfwTerminate();
}

void Engine::CreateWindow(int width, int height, const char* windowName) {
	windowClass = new Window(width, height, windowName);
	window = windowClass->getWindow();
	input = windowClass->getInput();
}
