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

		printf(vShaderCode);
		printf(fShaderCode);

		//2. compile shaders
		unsigned int vertex, fragment;
		// vertex shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		// fragment Shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		sahderProgramID = glCreateProgram();
		glAttachShader(sahderProgramID, vertex);
		glAttachShader(sahderProgramID, fragment);
		glLinkProgram(sahderProgramID);
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