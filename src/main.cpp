#include "../include/core/graphics/window.h"

void render();

void resize(Window* window, int width, int height) {
	std::fprintf(stdout, "%s, It worked!\n", window->config.title.c_str());
}

int main() {
	if (!glfwInit()) {
		std::fprintf(stderr, "Failed to initialize GLFW.\n");
		return -1;
	} else {
		WindowConfiguration windowConfig;
		windowConfig.title = "Window test";

		Window window(windowConfig);
		window.create();
		
		if (window.status == WINDOW_CREATION_FAILED) {
			std::fprintf(stderr, "Failed to open the window.\n");
			return -1;
		}

		window.resizeCallback = resize;

		window.bindContext();

		while (!window.shouldClose()) {
			window.pollEvents();
			if (glfwGetKey(window.windowHandle, GLFW_KEY_ESCAPE) == GLFW_PRESS) 
				break;
		}
		
		window.releaseContext();
	}

	glfwTerminate();
	return 0;
}

//void render() {	
//	glClear(GL_COLOR_BUFFER_BIT);
//
//	glColor3f(1, 1, 1);
//	glBegin(GL_TRIANGLES);
//	{
//		glVertex2f(-1, -1);
//		glVertex2f( 1, -1);
//		glVertex2f( 1,  1);
//	}
//	glEnd();
//
//	glfwSwapBuffers(window);
//	glfwPollEvents();
//}
