#pragma once
#include "Types\varTypes.hpp"

class Texture
{
public:
	Texture() = delete;
	Texture(const char* path);
	~Texture();

	ui32 textureID;
};