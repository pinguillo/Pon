#include "Sprite.hpp"
#include "Shader.hpp"
#include "../ResourcePack.hpp"

#include <Glad/glad/glad.h>

Sprite::Sprite()
{
	shader = ResourcePack::GetResourcePack()->Get2DShader();
	CreateQuad();
}

Sprite::Sprite(const char* sprPath)
{
	shader = ResourcePack::GetResourcePack()->Get2DShader();
	texture = ResourcePack::GetResourcePack()->GetTexture(sprPath)->textureID;
	CreateQuad();
}

Sprite::~Sprite()
{
	glDeleteVertexArrays(1, &vertexArrayID);
	glDeleteBuffers(1, &vertexBufferID);
}

void Sprite::setSprite(const char* sprPath)
{
	texture = ResourcePack::GetResourcePack()->GetTexture(sprPath)->textureID;
}

void Sprite::setScale(Vec2 _scale)
{
	scale = Vec3(_scale.x, _scale.y, 1.0f);
}

void Sprite::setRotation(Vec2 _rot)
{
	rotation = Vec3(_rot.x, _rot.y, 1.0f);
}

void Sprite::setPosition(Vec2 _pos)
{
	position = Vec3(_pos.x, _pos.y, 1.0f);
}

void Sprite::UpdateTransform()
{
	glm::mat4 temp, transform;
	temp = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, position.z));
	transform = temp;

	temp = glm::scale(glm::mat4(1.0f), glm::vec3(scale.x, scale.y, scale.z));
	transform *= temp;

	temp = glm::rotate(glm::mat4(1.0f), rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	temp = glm::rotate(temp, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	temp = glm::rotate(temp, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	transform *= temp;

	transformMatrix = transform;
}

void Sprite::Draw(glm::mat4& proj, glm::mat4& view)
{
	shader->Bind();
	shader->setMat4("transform", transformMatrix);
	shader->setMat4("view", view);
	shader->setMat4("projection", proj);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glBindVertexArray(vertexArrayID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Sprite::CreateQuad()
{
	/*
	vertices =
	{
		glm::vec3(-1.0f, 1.0f, 0.0f),
		glm::vec3(1.0f, 1.0f, 0.0f),
		glm::vec3(1.0f, -1.0f, 0.0f),
		glm::vec3(-1.0f, -1.0f, 0.0f)
	};*/

	vertices =
	{
		-1.0f, 1.0f, 0.0f,		0.0f, 1.0f,
		1.0f, 1.0f, 0.0f,		1.0f, 1.0f,
		1.0f, -1.0f, 0.0f,		1.0f, 0.0f,

		1.0f, -1.0f, 0.0f,		1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,		0.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,		0.0f, 1.0f,
	};

	// Create and bind vertex buffer
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	// Create vertices vertex buffer
	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

	// Attrib pointers
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);	//Unbind buffer after usage
	glBindVertexArray(0);				//Unbind vertex array after usage
}
