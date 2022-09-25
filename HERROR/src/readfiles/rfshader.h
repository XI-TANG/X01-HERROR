#pragma once
#include <string>

/* read shader from files */
class rfshader
{
public:
	rfshader(const char* vertexPath, const char* fragmentPath);
	
	std::string vertexCodeString;
	std::string fragmentCodeString;
	const char* vShaderCode = "";//用于储存从文件读取的源码
	const char* fShaderCode = "";
private:
};

