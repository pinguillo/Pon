#pragma once
#include "Types\varTypes.hpp"

#include <Glad\glad\glad.h>
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

	void setInt(const std::string& name, int value) {
		glUniform1i(glGetUniformLocation(shaderProgramId, name.c_str()), value);
	}

	void setFloat(const std::string& name, float value) {
		glUniform1f(glGetUniformLocation(shaderProgramId, name.c_str()), value);
	}

	void setMat4(const std::string& name, const glm::mat4& mat) const {
		glUniformMatrix4fv(glGetUniformLocation(shaderProgramId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	void setVec3(const std::string& name, const glm::vec3& vec) const	{
		glUniform3fv(glGetUniformLocation(shaderProgramId, name.c_str()), 1, &vec[0]);
	}

	ui32 shaderID() { return shaderProgramId; }

private:
	void attach(const char* path, const ShaderType& type);

	void link();


	ui32 shaderProgramId = 0;
	ui32 attachedShaders[2]{};
};