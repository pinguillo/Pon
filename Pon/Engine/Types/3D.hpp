#pragma once
#include <glm\glm.hpp>
#include <vector>

struct Vec3 {
	Vec3() {}
	Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
	float x = 0, y = 0, z = 0;

	Vec3 identity() { return Vec3(1.0f, 1.0f, 1.0f); }

	bool operator==(const Vec3& other) const {
		return x == other.x && y == other.y && z == other.z;
	}
};

struct Vec2 {
	Vec2() {}
	Vec2(float x, float y) : x(x), y(y) {}
	float x = 0, y = 0;

	bool operator==(const Vec2& other) const {
		return x == other.x && y == other.y ;
	}
};

struct Vertex {
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 normals;
	glm::vec2 texCoord;

	bool operator==(const Vertex& other) const {
		return position == other.position && color == other.color && normals == other.normals && texCoord == other.texCoord;
	}
};

struct ModelVectors {
	std::vector<Vertex> vertex;
	std::vector<ui32> indices;
};