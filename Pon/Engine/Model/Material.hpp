#pragma once
#include "Types\varTypes.hpp"
#include "../ResourcePack.hpp"

class Material
{
public:
	Material()
	{
		shader = ResourcePack::GetResourcePack()->GetShader("Assets/Shaders/Shoder.vert", "Assets/Shaders/Shoder.frag");
	}
	Material(Shader* s) : shader(s) {}
	~Material() {}

	void LoadShader(const char* VSpath, const char* FSpath)
	{
		shader = ResourcePack::GetResourcePack()->GetShader(VSpath, FSpath);

		shader->setInt("material.diffuse", 0);
		shader->setInt("material.specular", 1);
		shader->setInt("shadowMap", 2);
	}

	void LoadShader(Shader* &sh)
	{
		shader = sh;

		shader->setInt("material.diffuse", 0);
		shader->setInt("material.specular", 1);
		shader->setInt("shadowMap", 2);
	}

	Shader* shader;
	ui32 diffuseID = 0;
	ui32 specularID = 0;
	float shininess = 0.0f;
};