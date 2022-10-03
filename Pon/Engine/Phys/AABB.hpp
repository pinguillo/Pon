#pragma once

#include "boxCollider.hpp"
#include "../Log.hpp"

#include <vector>

class AABB {
public:
	AABB() {

	}

	void AddCollider(BoxCollider bc) { colliders.push_back(bc); }

	void Step() {
		for (int i = 0; i < colliders.size(); ++i) {
			std::vector<BoxCollider> tempPop = colliders;
			tempPop.erase(tempPop.begin() + i);

			bool colliding = false;
			for (BoxCollider col : tempPop) {
				bool collid =
					(colliders[i].bBox.minX + colliders[i].position.x) <= (col.bBox.maxX + col.position.x) &&
					(colliders[i].bBox.maxX + colliders[i].position.x) >= (col.bBox.minX + col.position.x) &&

					(colliders[i].bBox.minY + colliders[i].position.y) <= (col.bBox.maxY + col.position.y) &&
					(colliders[i].bBox.maxY + colliders[i].position.y) >= (col.bBox.minY + col.position.y) &&

					(colliders[i].bBox.minZ + colliders[i].position.z) <= (col.bBox.maxZ + col.position.z) &&
					(colliders[i].bBox.maxZ + colliders[i].position.z) >= (col.bBox.minZ + col.position.z);

				if (collid) { colliding = true; }
			}
			colliders[i].colliding = colliding;
		}
	}
	std::vector<BoxCollider> colliders;
private:
};