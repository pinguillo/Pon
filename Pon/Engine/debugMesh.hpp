#pragma once
#include "Types\Math.hpp"
#include "ResourcePack.hpp"

#include <string>
#include <vector>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include <Glad\glad\glad.h>

class DebugMesh {
public:
	DebugMesh() {
		shader = ResourcePack::GetResourcePack()->GetShader("Assets/Shaders/debug.vert", "Assets/Shaders/debug.frag");

		verts = {
			glm::vec3(-1.0f, -1.0f, 1.0f),
			glm::vec3(1.0f, -1.0f, 1.0f),
			glm::vec3(1.0f, 1.0f, 1.0f),
			glm::vec3(-1.0f, 1.0f, 1.0f),

			glm::vec3(-1.0f, -1.0f, -1.0f),
			glm::vec3(1.0f, -1.0f, -1.0f),
			glm::vec3(1.0f, 1.0f, -1.0f),
			glm::vec3(-1.0f, 1.0f, -1.0f)
		};

		ind = { 
			// front
			0, 1, 2,
			2, 3, 0,
			// right
			1, 5, 6,
			6, 2, 1,
			// back
			7, 6, 5,
			5, 4, 7,
			// left
			4, 0, 3,
			3, 7, 4,
			// bottom
			4, 5, 1,
			1, 0, 4,
			// top
			3, 2, 6,
			6, 7, 3
		};

		// Create and bind vertex buffer
		glGenVertexArrays(1, &vertexArrayID);
		glBindVertexArray(vertexArrayID);

		// Create vertices vertex buffer
		glGenBuffers(1, &vertexBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
		glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(glm::vec3), &verts[0], GL_STATIC_DRAW);

		// Attrib pointers
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

		// Create indices buffer
		glGenBuffers(1, &indexBufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, ind.size() * sizeof(ui32), &ind[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);	//Unbind buffer after usage
		glBindVertexArray(0);				//Unbind vertex array after usage



	}

	~DebugMesh() {
		glDeleteVertexArrays(1, &vertexArrayID);
		glDeleteBuffers(1, &vertexBufferID);
		glDeleteBuffers(1, &indexBufferID);
	}

	void Draw(glm::mat4& proj, glm::mat4& view) {
		
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//Make a section in engine to draw all the wireframes to not set this in every box

		shader->Bind();

		UpdateTransform();
		shader->setMat4("projection", proj);
		shader->setMat4("view", view);
		shader->setMat4("model", transformMatrix);

		glBindVertexArray(vertexArrayID);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
		
		//glDrawArrays(GL_TRIANGLES, 0, ind.size());
		glDrawElements(GL_TRIANGLES, ind.size(), GL_UNSIGNED_INT, 0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void setScale(Vec3 _scale) {
		scale = _scale;
	}

	void setRotation(Vec3 rot) {
		rotation = rot;
	}

	void setPosition(Vec3 pos) {
		position = pos;
	}

	void UpdateTransform() {
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

	Shader* getShader() { return shader; }
	glm::vec3 getPosition() { return glm::vec3(position.x,position.y,position.z); }
private:
	glm::mat4 transformMatrix = glm::mat4(1.0f);
	Vec3 position{};
	Vec3 scale = Vec3().identity();
	Vec3 rotation{};

	std::vector<glm::vec3> verts;
	std::vector<ui32> ind;

	Shader* shader;

	ui32 vertexArrayID;
	ui32 vertexBufferID;
	ui32 indexBufferID;
};