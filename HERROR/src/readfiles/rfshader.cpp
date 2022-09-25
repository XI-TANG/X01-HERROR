#include "rfshader.h"
#include <fstream>
#include <sstream>
#include <iostream>

/*
* c++中的文件流：
*	file in disk -> file buffer -> string buffer -> string -> char*
*/
rfshader::rfshader(const char* vertexPath, const char* fragmentPath) 
{
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.open(vertexPath);
	fShaderFile.open(fragmentPath);

	// 保证ifstream对象可以抛出异常：
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		//1. 打开文件
		if (!vShaderFile.is_open()) {
			throw std::exception("open vertex file err");
		}
		if (!fShaderFile.is_open()) {
			throw std::exception("open fragment file err");
		}

		std::stringstream vShaderStream, fShaderStream;
		// 读取文件的缓冲内容到数据流中
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		// 关闭文件处理器
		vShaderFile.close();
		fShaderFile.close();

		// 转换数据流到string
		vertexCodeString = vShaderStream.str();
		fragmentCodeString = fShaderStream.str();

		//string to char*
		vShaderCode = vertexCodeString.c_str();
		fShaderCode = fragmentCodeString.c_str();

		//printf(vShaderCode);
		//printf(fShaderCode);

		//2. compile shaders
		unsigned int vertex, fragment;
		// vertex shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		checkCompileErrors(vertex, SHADER_CHECK_TYPE_Enum::SHADER_CHECK_TYPE_VERTEX);
		// fragment Shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		checkCompileErrors(fragment, SHADER_CHECK_TYPE_Enum::SHADER_CHECK_TYPE_FRAGMENT);
		//Program Shader
		sahderProgramID = glCreateProgram();
		glAttachShader(sahderProgramID, vertex);
		glAttachShader(sahderProgramID, fragment);
		glLinkProgram(sahderProgramID);
		checkCompileErrors(sahderProgramID, SHADER_CHECK_TYPE_Enum::SHADER_CHECK_TYPE_PROGRAM);
		// delete the shaders as they're linked into our program now and no longer necessary
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}
	catch (const std::exception& ex)
	{
		printf(ex.what());
		printf("\t\n");
		printf("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\t\n");
	}
}

// activate the shader
void rfshader::use()
{
	glUseProgram(sahderProgramID);
}

// utility function for checking shader compilation/linking errors.
void rfshader::checkCompileErrors(unsigned int id, SHADER_CHECK_TYPE_Enum type)
{
	int success;
	char infoLog[512];

	const char* typeStr[3] = {
		"VERTEX",
		"FRAGMENT",
		"PROGRAM"
	};
	//printf(typeStr[(int)type]);
	switch (type)
	{
	case SHADER_CHECK_TYPE_Enum::SHADER_CHECK_TYPE_VERTEX:
	case SHADER_CHECK_TYPE_Enum::SHADER_CHECK_TYPE_FRAGMENT:
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(id, 512, NULL, infoLog);
			std::cout << "\t\nERROR::PROGRAM_LINKING_ERROR of type: " 
				<< typeStr[(int)type] << "\n" << infoLog << std::endl;
		}
		break;
	case SHADER_CHECK_TYPE_Enum::SHADER_CHECK_TYPE_PROGRAM:
		glGetProgramiv(id, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(id, 512, NULL, infoLog);
			std::cout << "\t\nERROR::SHADER_COMPILATION_ERROR of type: " 
				<< typeStr[(int)type] << "\n" << infoLog << std::endl;
		}
		break;
	default:
		printf("SHADER_CHECK: ERROR TYPE\t\n");
		break;
	}
}