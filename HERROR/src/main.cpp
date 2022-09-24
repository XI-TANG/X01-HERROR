#include <stdio.h>
/* dependents lib */
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "tools/xilog4cpp/XI_LOG.h"
#include "readfiles/rfshader.h"

void error_callback(int error, const char* description);
void close_callback(GLFWwindow* window);
void set_frame_buffer_callback(GLFWwindow* window, int width, int height);
void key_info(GLFWwindow* window);

int main() {

	XI_LOG::XI_LOG(XI_LOG_TAG_Enum::XI_LOG_TAG_MAIN, XI_LOG_LVL_Enum::XI_LOG_LVL_INFO,"TEST LOG");
	
	rfshader::rfshader("./shaders/shadertest1.shader","./shaders/fragmenttest1.shader");

	glfwSetErrorCallback(error_callback);

	if (!glfwInit()) {
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(1080, 760, "hello", NULL, NULL);

	glfwSetWindowCloseCallback(window, close_callback);

	if (!window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glfwSetFramebufferSizeCallback(window, set_frame_buffer_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		return -1;
	}

	while (!glfwWindowShouldClose(window)) {

		key_info(window);

		//render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwSwapInterval(1);

		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}

void key_info(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

void error_callback(int error, const char* description) {
	fprintf(stderr, "error %d: %s\n", error, description);
}

void close_callback(GLFWwindow* window) {
}

void set_frame_buffer_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}