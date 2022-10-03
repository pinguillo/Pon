#include "Shader.hpp"

#include "Log.hpp"

#include <fstream>
#include <sstream>
#include <vector>

Shader::Shader()
{
}

Shader::Shader(const char* VSpath, const char* FSpath)
{
	shaderProgramId = glCreateProgram();
	attach(VSpath, ShaderType::VERTEX);
	attach(FSpath, ShaderType::FRAGMENT);
	link();
}

Shader::~Shader()
{
	for (ui32 i = 0; i < 2; i++) {
		glDetachShader(shaderProgramId, attachedShaders[i]);
		glDeleteShader(attachedShaders[i]);
	}
	glDeleteProgram(shaderProgramId);
}

void Shader::attach(const char* path, const ShaderType& type)
{
	std::string code;

	// Open file and grab the code
	std::ifstream stream(path);
	if (stream.is_open()) {
		std::stringstream sstr;
		sstr << stream.rdbuf();
		code = sstr.str();

		stream.close();
	}
	else {
		PIN_WARNING("Shader -> \"" << path << "\" not found");
		return;
	}
	// Create shader
	ui32 sID = 0;
	if (type == ShaderType::VERTEX) {
		sID = glCreateShader(GL_VERTEX_SHADER);
	}
	else if (type == ShaderType::FRAGMENT) {
		sID = glCreateShader(GL_FRAGMENT_SHADER);
	}

	// Compile shader
	auto codePtr = code.c_str();
	glShaderSource(sID, 1, &codePtr, nullptr);
	glCompileShader(sID);

	int logLength = 0;
	glGetShaderiv(sID, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 0) {
		std::vector<char> errorMessage(logLength + 1);
		glGetShaderInfoLog(sID, logLength, nullptr, &errorMessage[0]);
		PIN_WARNING("Shader -> \"" << path << "\" compile error: " << std::endl << &errorMessage[0]);
		return;
	}

	glAttachShader(shaderProgramId, sID);
	attachedShaders[(ui32)type] = sID;

	PIN_INFO("Shader -> \"" << path << "\" compiled succesfully!");
}

void Shader::link()
{
	glLinkProgram(shaderProgramId);

	int logLength = 0;
	glGetShaderiv(shaderProgramId, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 0) {
		std::vector<char> errorMessage(logLength + 1);
		glGetShaderInfoLog(shaderProgramId, logLength, NULL, &errorMessage[0]);
		PIN_WARNING("Shader -> " << &errorMessage[0]);
		return;
	}
}
