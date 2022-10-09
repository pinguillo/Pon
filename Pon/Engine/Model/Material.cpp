#include "Material.hpp"

Material::Material()
{
	shader = ResourcePack::GetResourcePack()->GetShader("Assets/Shaders/Shoder.vert", "Assets/Shaders/Shoder.frag");
}

Material::Material(Shader* s) : shader(s)
{
}

Material::~Material()
{
}

void Material::LoadShader(const char* VSpath, const char* FSpath)
{
	shader = ResourcePack::GetResourcePack()->GetShader(VSpath, FSpath);

	shader->setInt("material.diffuse", 0);
	shader->setInt("material.specular", 1);
	shader->setInt("shadowMap", 2);
}

void Material::LoadShader(Shader* &sh)
{
	shader = sh;

	shader->setInt("material.diffuse", 0);
	shader->setInt("material.specular", 1);
	shader->setInt("shadowMap", 2);
}
