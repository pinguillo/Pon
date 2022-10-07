#pragma once
#include "../Types/Math.hpp"

struct Transform {
	Vec3 position{};
	Vec3 scale = Vec3().identity();
	Vec3 rotation{};
};