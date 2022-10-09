#pragma once
#include "Types\varTypes.hpp"
#include "../ResourcePack.hpp"

class Material
{
public:
	Material();
	Material(Shader* s);
	~Material();

	void LoadShader(const char* VSpath, const char* FSpath);

	void LoadShader(Shader* &sh);

	Shader* shader;
	ui32 diffuseID = 0;
	ui32 specularID = 0;
	float shininess = 0.0f;
};