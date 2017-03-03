#pragma once
#include <GLFW/glfw3.h>

#include <iostream>

#define WINDOW_CREATION_FAILED 1
#define WINDOW_DESTROYED 2

struct WindowConfiguration {
	std::string title = "Default window name";
	uint32_t width = 1280;
	uint32_t height = 720;
	uint32_t openglProfile = GLFW_OPENGL_ANY_PROFILE;
	uint16_t antialiasing = 0;
	uint16_t openglMajorVersion = 1;
	uint16_t openglMinorVersion = 1;
	uint16_t monitor = 0;
	uint16_t xPosition = 0;
	uint16_t yPosition = 0;

	bool vsync = true;
	bool resizable = true;
	bool fullscreen = false;
	bool openglForwardCompatible = false;
};

class Window {
public:
	WindowConfiguration config;
	GLFWwindow* windowHandle;
	uint16_t status;

	Window(WindowConfiguration);
	~Window(); //calls destroy

	void bindContext();
	void releaseContext();

	void pollEvents();

	void setTitle(std::string);
	void setSize(uint32_t width, uint32_t height);
	void setPosition(uint32_t x, uint32_t y);

	void iconify();
	void restore();
	void hide();
	void show();

	bool shouldClose();

	void create(); //creates window
	void destroy();//deletes this window (glfwDestroyWindow)

private:
	static void resize(GLFWwindow* handle, int width, int height);
};
