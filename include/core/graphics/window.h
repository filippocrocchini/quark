#pragma once
#include <GLFW/glfw3.h>

#include <iostream>
#include <map>

#define WINDOW_CREATION_FAILED 1
#define WINDOW_DESTROYED 2

class Window;

typedef void(*ResizeCallback)(Window*, int,int);
typedef void(*KeyCallback)(Window*, int, int, int, int);
typedef void(*CharacterCallback)(Window*, unsigned int);
typedef void(*CharacterWithModifierCallback)(Window*, unsigned, int);
typedef void(*CursorPositionCallback)(Window*, double, double);
typedef void(*MouseButtonCallback)(Window*, int, int, int);
typedef void(*ScrollCallback)(Window*, double, double);

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

//TODO: add support for custom cursor
class Window {
public:
	WindowConfiguration config;
	GLFWwindow* windowHandle;
	uint16_t status;

	ResizeCallback resizeCallback = nullptr;
	KeyCallback keyCallback = nullptr;
	CharacterCallback characterCallback = nullptr;
	CharacterWithModifierCallback characterWithModifierCallback = nullptr;
	CursorPositionCallback cursorCallback = nullptr;
	MouseButtonCallback mouseButtonCallback = nullptr;
	ScrollCallback scrollCallback = nullptr;

	Window() = default;
	Window(WindowConfiguration);
	
	void setConfiguration(WindowConfiguration);

	void bindContext();
	void releaseContext();

	void pollEvents();
	void swapBuffers();

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
	static std::map<GLFWwindow*, Window*> handleToPtr;

	static Window* getWindow(GLFWwindow*);
	static void resize(GLFWwindow* handle, int width, int height);
	static void key(GLFWwindow* handle, int key, int scancode, int action, int mods);
	static void character(GLFWwindow* handle, unsigned int codepoint);
	static void character_mod(GLFWwindow* handle, unsigned int codepoint, int mods);
	static void cursor_pos(GLFWwindow* handle, double x, double y);
	static void mouse_button(GLFWwindow* handle, int button, int action, int mods);
	static void scroll(GLFWwindow* handle, double xoffset, double yoffset);
};

