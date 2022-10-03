#pragma once
#include "../Types/3D.hpp"
#include "Material.hpp"

#include <Glad\glad\glad.h>

#include <vector>

class Mesh {
public:
	Mesh()
	{
	}
	~Mesh(){}

	void Draw(glm::mat4& transformMatrix) {
		mat.shader->Bind();

		mat.shader->setMat4("transform", transformMatrix);

		mat.shader->setFloat("material.shininess", mat.shininess);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mat.diffuseID);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, mat.specularID);
		//glActiveTexture(GL_TEXTURE2);
		//glBindTexture(GL_TEXTURE_2D, depthMapID);

		glBindVertexArray(vertexArrayID);
		//glDrawArrays(GL_TRIANGLES, 0, vertexList.size());
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	void CreateGL() {
		// Create and bind vertex buffer
		glGenVertexArrays(1, &vertexArrayID);
		glBindVertexArray(vertexArrayID);

		// Create vertices vertex buffer
		glGenBuffers(1, &vertexBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
		glBufferData(GL_ARRAY_BUFFER, vertexList.size() * sizeof(Vertex), &vertexList[0], GL_STATIC_DRAW);

		// Attrib pointers
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normals));
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));

		// Create indices buffer
		glGenBuffers(1, &indexBufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(ui32), &indices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);	//Unbind buffer after usage
		glBindVertexArray(0);				//Unbind vertex array after usage
	}

	void SetMat4(const std::string& name, const glm::mat4& matrix)
	{
		mat.shader->setMat4(name, matrix);
	}

	std::vector<ui32> indices;
	std::vector<Vertex> vertexList;
	Material mat;

	ui32 vertexArrayID;
	ui32 vertexBufferID;
	ui32 indexBufferID;
};