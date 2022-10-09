#pragma once
#include <glm\glm.hpp>

struct BoundingBox {
	float minX, maxX;
	float minY, maxY;
	float minZ, maxZ;
};

class BoxCollider {
public:
	BoxCollider(float sizeX, float sizeY, float sizeZ);

	BoundingBox bBox;
	glm::vec3 position = glm::vec3(0.0f);
	bool colliding = false;
};