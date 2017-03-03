#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <GL/GL.h>

#include "../include/threadpool.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#define NO_ERROR 0
#define FAILED_GLFW_INIT 1
#define FAILED_GLFW_WINDOW 2
#define FAILED_GLEW_INIT 3

int openWindow(GLFWwindow **window, bool vsync);
void closeWindow(GLFWwindow *window);
void render();
void update();

void renderLoop();


ThreadPool pool(4,20);
GLFWwindow* window;
Task updateTask(update);
Task renderLoopTask(renderLoop);

int main() {
	pool.submit(&renderLoopTask);
	while(pool.running)
		pool.submit(&updateTask);
	return 0;
}

int openWindow(GLFWwindow **window, bool vsync) {
	if (!glfwInit()) {
		std::fprintf(stderr, "Failed to initialize GLFW.\n");
		return FAILED_GLFW_INIT;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	*window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Window", 0, 0);

	if (*window == nullptr) {
		std::fprintf(stderr, "Failed to create GLFW Window.\n");
		return FAILED_GLFW_WINDOW;
	}

	glfwMakeContextCurrent(*window);

	if (vsync)
		glfwSwapInterval(-1);
	else
		glfwSwapInterval(0);

	glewExperimental = true;

	if (glewInit() != GLEW_OK) {
		std::fprintf(stderr, "Failed to initialize GLEW.\n");
		return FAILED_GLEW_INIT;
	}

	glClearColor(0, 0, 0, 0);

	return NO_ERROR;
}

void closeWindow(GLFWwindow *window) {
	glfwDestroyWindow(window);
	pool.running = false;
}

void renderLoop() {
	window = nullptr;
	int error = openWindow(&window, true);

	if (error != NO_ERROR) {
		glfwTerminate();
		system("pause");
		return;
	}

	while (!glfwWindowShouldClose(window)) {
		render();
	}

	closeWindow(window);
}

void render() {	
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1, 1, 1);
	glBegin(GL_TRIANGLES);
	{
		glVertex2f(-1, -1);
		glVertex2f( 1, -1);
		glVertex2f( 1,  1);
	}
	glEnd();

	glfwSwapBuffers(window);
	glfwPollEvents();
}

void update() {
	fprintf(stdout, "Update running\n");
}
