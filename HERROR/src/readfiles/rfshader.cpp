#include "rfshader.h"
#include <fstream>


rfshader::rfshader(const char* vertexPath, const char* fragmentPath) 
{
	std::ifstream vertexFile;
	std::ifstream fragmentFile;

	vertexFile.open(vertexPath);
	fragmentFile.open(fragmentPath);

	try
	{
		if (!vertexFile.is_open()) {
			throw std::exception("open vertex file err");
		}
		if (!fragmentFile.is_open()) {
			throw std::exception("open fragment file err");
		}
	}
	catch (const std::exception& ex)
	{
		printf(ex.what());
		printf("\t\n");
	}
}