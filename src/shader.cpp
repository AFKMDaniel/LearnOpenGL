#include "shader.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

std::string Shader::getShaderCode(const std::string& path)
{
	std::string result;
	std::ifstream shaderFile;

	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		shaderFile.open(path);

		std::ostringstream shaderStream;
		shaderStream << shaderFile.rdbuf();

		shaderFile.close();

		result = shaderStream.str();
	}
	catch(std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n";
	}

	return result;
}

unsigned int Shader::compileShader(GLenum type, std::string sourceCode)
{
	auto shaderCode = sourceCode.c_str();

	auto shader = glCreateShader(type);
	glShaderSource(shader, 1, &shaderCode, nullptr);
	glCompileShader(shader);

	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << '\n';
	}

	return shader;
}

void Shader::createProgram(unsigned int vShader, unsigned int fShader)
{
	program = glCreateProgram();
	glAttachShader(program, vShader);
	glAttachShader(program, fShader);
	glLinkProgram(program);

	int success;
	char infoLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::SHADER_PROGRAM::LINKING_FAILED\n" << infoLog << '\n';
	}
}

Shader::Shader(const std::string& vertPath, const std::string& fragPath)
{
	auto vShaderCode = getShaderCode(vertPath);
	auto fShaderCode = getShaderCode(fragPath);

	auto vShader = compileShader(GL_VERTEX_SHADER, vShaderCode);
	auto fShader = compileShader(GL_FRAGMENT_SHADER, fShaderCode);

	createProgram(vShader, fShader);

	glDeleteShader(vShader);
	glDeleteShader(fShader);
}

void Shader::use()
{
	glUseProgram(program);
}

void Shader::setUniform(const std::string& name, bool value)
{
	glUniform1i(glGetUniformLocation(program, name.c_str()), static_cast<int>(value));
}

void Shader::setUniform(const std::string& name, float value)
{
	glUniform1f(glGetUniformLocation(program, name.c_str()), value);
}

void Shader::setUniform(const std::string& name, int value)
{
	glUniform1i(glGetUniformLocation(program, name.c_str()), value);
}
