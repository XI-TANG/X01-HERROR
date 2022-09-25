#ifndef RFSHADER_H
#define RFSHADER_H

#pragma once
#include <string>
#include <glad/glad.h>

enum class SHADER_CHECK_TYPE_Enum
{
	SHADER_CHECK_TYPE_VERTEX,
	SHADER_CHECK_TYPE_FRAGMENT,
	SHADER_CHECK_TYPE_PROGRAM
};

/* read shader from files */
class rfshader
{
public:
	rfshader(const char* vertexPath, const char* fragmentPath);
	unsigned int sahderProgramID = 0; //shader program ID
	std::string vertexCodeString;
	std::string fragmentCodeString;
	const char* vShaderCode = "";//用于储存从文件读取的源码
	const char* fShaderCode = "";
	void use();
private:
	void checkCompileErrors(unsigned int id, SHADER_CHECK_TYPE_Enum type);
};

#endif