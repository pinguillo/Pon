#pragma once
#include "Types\Math.hpp"

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include <string>
#include <vector>

class Shader;

class Sprite {
public:
	Sprite();
	Sprite(const char* sprPath);
	~Sprite();

	void setSprite(const char* sprPath);


	void setScale(Vec2 scale);
	void setRotation(Vec2 rot);
	void setPosition(Vec2 pos);
	void UpdateTransform();


	void Draw(glm::mat4& proj, glm::mat4& view);

private:
	void CreateQuad();

	glm::mat4 transformMatrix = glm::mat4(1.0f);
	Vec3 position{};
	Vec3 scale = Vec3().identity();
	Vec3 rotation{};

	Shader* shader;
	ui32 texture;

	std::vector<float> vertices;
	ui32 vertexArrayID;
	ui32 vertexBufferID;
};