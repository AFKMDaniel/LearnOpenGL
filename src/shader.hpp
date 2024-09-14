#pragma once
#include <glad/glad.h>
#include <string>

class Shader
{
private:
	unsigned int program;
private:
	std::string getShaderCode(const std::string& path);
	unsigned int compileShader(GLenum type, std::string sourceCode);
	void createProgram(unsigned int vShader, unsigned int fShader);
public:
	Shader(const std::string& vertPath, const std::string& fragPath);
	void use();
	void setUniform(const std::string& name, bool value);
	void setUniform(const std::string& name, float value);
	void setUniform(const std::string& name, int value);
};
