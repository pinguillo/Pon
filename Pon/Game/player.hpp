#pragma once

#include "../Engine/Model/Model.hpp"
#include "../Engine/Model/Shader.hpp"
//#include "../Engine/Components/MeshedObject.hpp"
#include "../Engine/Components/Camera.hpp"
#include "../Engine/Input.hpp"
#include <glm\glm.hpp>

#define MAX_SPEED 0.1f

class Player {
public:
	Player(Input* inp) : input(inp) {
		//Material mat = Material(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.5f, 0.5f, 0.5f), 12.8f);

		//Model* mdl = new Model("Assets/Models/cor.obj");
		//Shader* sh = new Shader("Assets/Shaders/Shoder.vert", "Assets/Shaders/Shoder.frag");

		//model.LoadModel("Assets/Models/cor.obj"); Loading directly causes error for some reason
		//model.LoadModel(mdl);
		//model.LoadShader(sh);
		//model.getModel()->SetMaterial(mat);
		//model.getModel()->LoadDiffuse("Assets/Textures/cor.png");
		//model.getModel()->LoadSpecular("Assets/Textures/cor_s.png");
		//model.getModel()->PassToShader("shadowMap", 2);

	}
	~Player(){}

	void Draw() {
		//model.Draw();
	}

	void Step(float deltaTime) {
		
		/*
		if (input->GetKey(GLFW_KEY_W)) {
			MoveUp(1.0f, deltaTime);
		}
		if (input->GetKey(GLFW_KEY_S)) {
			MoveDown(1.0f, deltaTime);
		}
		if (input->GetKey(GLFW_KEY_A)) {
			MoveLeft(1.0f, deltaTime);
		}
		if (input->GetKey(GLFW_KEY_D)) {
			MoveRight(1.0f, deltaTime);
		}*/

		if (input->GetKey(GLFW_KEY_UP)) {
			if(abs(velocity) < MAX_SPEED)
				Move(0.5f, deltaTime);
		}
		if (input->GetKey(GLFW_KEY_DOWN)) {
			if (abs(velocity) < MAX_SPEED)
				Move(-0.5f, deltaTime);
		}
		if (input->GetKey(GLFW_KEY_LEFT)) {
			rotation.y += 2.0f * deltaTime;
		}
		if (input->GetKey(GLFW_KEY_RIGHT)) {
			rotation.y -= 2.0f * deltaTime;
		}
		

		position.x += xSpeed / 10.0f;
		position.z += zSpeed / 10.0f;
		//model.transform.position = { position.x, position.y, position.z };
		//model.transform.rotation = { rotation.x, rotation.y, rotation.z };

		velocity = sqrt(pow(xSpeed, 2) + pow(zSpeed, 2));

		SpeedManagement(
			deltaTime,
			input->GetKey(GLFW_KEY_A) || input->GetKey(GLFW_KEY_D) || input->GetKey(GLFW_KEY_UP) || input->GetKey(GLFW_KEY_DOWN),
			input->GetKey(GLFW_KEY_W) || input->GetKey(GLFW_KEY_S) || input->GetKey(GLFW_KEY_UP) || input->GetKey(GLFW_KEY_DOWN)
		);
	}

	void SpeedManagement(float deltaTime, bool X, bool Z) {
		zSpeed = linearInterpolation(zSpeed, 0, 10.0 * deltaTime);
		xSpeed = linearInterpolation(xSpeed, 0, 10.0 * deltaTime);
		
		if (!X) {
			if (abs(velocity) < 0.01f) {
				xSpeed = 0.0f;
				zSpeed = 0.0f;
			}
		}
	}

	float linearInterpolation(float a, float b, float f) {
		return (a * (1.0f - f)) + (b * f);
	}

	void Move(float vel, float deltaTime) {
		xSpeed += (deltaTime * vel) * sin(rotation.y - glm::radians(90.0f));
		zSpeed += (deltaTime * vel) * cos(rotation.y - glm::radians(90.0f));
		//PIN_INFO(deltaTime * (vel * cos(rotation.y)));
	}

	void MoveUp(float z, float deltaTime) {
		zSpeed -= z * deltaTime;
	}

	void MoveDown(float z, float deltaTime) {
		zSpeed += z * deltaTime;
	}

	void MoveLeft(float x, float deltaTime) {
		xSpeed -= x * deltaTime;
	}

	void MoveRight(float x, float deltaTime) {
		xSpeed += x * deltaTime;
	}

	glm::vec3 getPosition() { return position; }
	//MeshedObject* getMeshedObject() { return &model; }

private:
	glm::vec3 position = glm::vec3(0.0f);
	glm::vec3 rotation = glm::vec3(0.0f);
	float xSpeed = 0.0f;
	float zSpeed = 0.0f;
	float velocity = 0.0f;

	Input* input;
	//MeshedObject model{};
	//Camera cam;
};