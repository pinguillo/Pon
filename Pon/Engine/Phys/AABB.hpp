#pragma once
#include "boxCollider.hpp"

#include <vector>

class AABB {
public:
	AABB();
	~AABB();

	void AddCollider(BoxCollider bc);

	void Step();

	std::vector<BoxCollider> colliders;
private:
};