#include "shader.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/gtc/type_ptr.hpp>

std::string Shader::getShaderCode(const std::string& path)
{
	std::string result;
	std::ifstream shaderFile{ path };

	if (!shaderFile) {
		std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n" << path << "\n\n";
	}

	std::ostringstream shaderStream;
	shaderStream << shaderFile.rdbuf();

	shaderFile.close();

	result = shaderStream.str();

	return result;
}

unsigned int Shader::compileShader(GLenum type, const std::string& path)
{
	auto shaderCode = getShaderCode(path);
	auto cstrShaderCode = shaderCode.c_str();

	auto shader = glCreateShader(type);
	glShaderSource(shader, 1, &cstrShaderCode, nullptr);
	glCompileShader(shader);

	int success;
	char infoLog[512];
	auto shaderType = type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT";
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);
		std::cerr << "ERROR::SHADER:" << shaderType << ":COMPILATION_FAILED\n" << path << '\n' << infoLog;
	}

	return shader;
}

void Shader::createProgram(unsigned int vShader, unsigned int fShader)
{
	mProgram = glCreateProgram();
	glAttachShader(mProgram, vShader);
	glAttachShader(mProgram, fShader);
	glLinkProgram(mProgram);

	int success;
	char infoLog[512];
	glGetProgramiv(mProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(mProgram, 512, nullptr, infoLog);
		std::cerr << "ERROR::SHADER::SHADER_PROGRAM::LINKING_FAILED\n" << infoLog;
	}
}

Shader::Shader(const std::string& vertPath, const std::string& fragPath)
{
	auto vShader = compileShader(GL_VERTEX_SHADER, vertPath);
	auto fShader = compileShader(GL_FRAGMENT_SHADER, fragPath);

	createProgram(vShader, fShader);

	glDeleteShader(vShader);
	glDeleteShader(fShader);
}

void Shader::use()
{
	glUseProgram(mProgram);
}

void Shader::setUniform(const std::string& name, bool value)
{
	glUniform1i(glGetUniformLocation(mProgram, name.c_str()), static_cast<int>(value));
}

void Shader::setUniform(const std::string& name, float value)
{
	glUniform1f(glGetUniformLocation(mProgram, name.c_str()), value);
}

void Shader::setUniform(const std::string& name, int value)
{
	glUniform1i(glGetUniformLocation(mProgram, name.c_str()), value);
}

void Shader::setUniform(const std::string& name, glm::mat4& value)
{
	glUniformMatrix4fv(glGetUniformLocation(mProgram, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
