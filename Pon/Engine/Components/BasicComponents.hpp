#pragma once
#include "../Types/varTypes.hpp"
#include "../Types/3D.hpp"

struct Transform {
	Vec3 position{};
	Vec3 scale = Vec3().identity();
	Vec3 rotation{};
};