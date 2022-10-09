#include "boxCollider.hpp"

BoxCollider::BoxCollider(float sizeX, float sizeY, float sizeZ)
{
	float halfX = sizeX / 2.0f;
	float halfY = sizeY / 2.0f;
	float halfZ = sizeZ / 2.0f;

	bBox.minX = halfX * -1;
	bBox.maxX = halfX;

	bBox.minY = halfY * -1;
	bBox.maxY = halfY;

	bBox.minZ = halfZ * -1;
	bBox.maxZ = halfZ;
}
