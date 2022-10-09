#pragma once
#include "../Types/Math.hpp"
#include "Material.hpp"

#include <Glad\glad\glad.h>

#include <vector>
#include <string>

class Mesh {
public:
	Mesh();
	~Mesh();

	void Draw(glm::mat4& transformMatrix);

	void CreateGL();

	void SetMat4(const std::string& name, const glm::mat4& matrix);

	std::vector<ui32> indices;
	std::vector<Vertex> vertexList;
	Material mat;

	ui32 vertexArrayID;
	ui32 vertexBufferID;
	ui32 indexBufferID;
};