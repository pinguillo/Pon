#pragma once
#include "Model/Texture.hpp"
#include "Model/Shader.hpp"

#include <unordered_map>
#include <string>

class ResourcePack
{
public:
	ResourcePack();
	ResourcePack(const ResourcePack& other) = delete;
	ResourcePack& operator=(const ResourcePack& other) = delete;
	~ResourcePack();

	static ResourcePack* GetResourcePack();

	Shader* GetShader(const std::string& VSpath, const std::string& FSpath);
	Shader* FindShader(const std::string& name);
	Shader* Get2DShader();

	Texture* GetTexture(const std::string& texPath);
	Texture* FindTexture(const std::string& name);

private:
	std::unordered_map<std::string, Shader*> Shaders;
	std::unordered_map<std::string, Texture*> Textures;

	Shader* Shader2D;

	static ResourcePack* resourcePackInstance;
};