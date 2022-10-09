#pragma once
#include "Types\varTypes.hpp"

#include <glm\glm.hpp>

#include <string>

enum class ShaderType {
	VERTEX = 0,
	FRAGMENT
};

class Shader {
public:
	Shader();
	Shader(const char* VSpath, const char* FSpath);
	Shader(const Shader&) = delete;
	Shader& operator = (const Shader&) = delete;
	~Shader();

	void Bind();

	void setInt(const std::string& name, int value);
	void setFloat(const std::string& name, float value);
	void setMat4(const std::string& name, const glm::mat4& mat) const;
	void setVec3(const std::string& name, const glm::vec3& vec) const;

	ui32 shaderID();

private:
	void attach(const char* path, const ShaderType& type);
	void link();

	ui32 shaderProgramId = 0;
	ui32 attachedShaders[2]{};
};