#include "ResourcePack.hpp"

#include "../Utils/Utils.hpp"

ResourcePack* ResourcePack::resourcePackInstance = 0;

ResourcePack::ResourcePack() {
	Shader2D = new Shader("Assets/Shaders/sprite.vert", "Assets/Shaders/sprite.frag");
}

ResourcePack::~ResourcePack()
{
	for(auto& sh : Shaders)
	{
		delete sh.second;
	}
	for (auto& tx : Textures)
	{
		delete tx.second;
	}
	delete Shader2D;
}

ResourcePack* ResourcePack::GetResourcePack()
{
	if (resourcePackInstance == nullptr)
	{
		resourcePackInstance = new ResourcePack();
	}
	
	return resourcePackInstance;
}

Shader* ResourcePack::GetShader(const std::string& VSpath, const std::string& FSpath)
{
	std::string shaderName = GetFileName(VSpath) + GetFileName(FSpath);
	auto search = Shaders.find(shaderName);

	if (search == Shaders.end())
	{//If no shader, create it
		auto s = new Shader(VSpath.c_str(), FSpath.c_str());
		Shaders.insert({ shaderName, s });
		return s;
	}
	else
	{
		return search->second;
	}
}

Shader* ResourcePack::FindShader(const std::string& name)
{
	return Shaders[name];
}

Shader* ResourcePack::Get2DShader()
{
	return Shader2D;
}

Texture* ResourcePack::GetTexture(const std::string& texPath)
{
	std::string textureName = GetFileName(texPath);
	auto search = Textures.find(textureName);

	if (search == Textures.end())
	{//If no texture, create it
		auto t = new Texture(texPath.c_str());
		Textures.insert({ textureName, t });
		return t;
	}
	else
	{
		return search->second;
	}
}

Texture* ResourcePack::FindTexture(const std::string& name)
{
	return Textures[name];
}
