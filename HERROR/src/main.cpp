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

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
	};

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//vs与fs文件不要转码
	rfshader* testshader = new rfshader("./shaders/shadertest1.vs", "./shaders/fragmenttest1.fs");

	while (!glfwWindowShouldClose(window)) {

		key_info(window);

		//render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// render the triangle
		testshader->use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		glfwSwapBuffers(window);
		glfwSwapInterval(1);

		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
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