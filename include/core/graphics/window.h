#pragma once
#include <glfw/include/GLFW/glfw3.h>

#include <iostream>
#include <map>

enum WindowStatus {
    WINDOW_OK,
	WINDOW_CREATION_FAILED,
	WINDOW_DESTROYED
};

class Window;

typedef void(*ResizeCallback)(Window*, int,int);
typedef void(*KeyCallback)(Window*, int, int, int, int);
typedef void(*CharacterCallback)(Window*, unsigned int);
typedef void(*CharacterWithModifierCallback)(Window*, unsigned int, int);
typedef void(*CursorPositionCallback)(Window*, double, double);
typedef void(*MouseButtonCallback)(Window*, int, int, int);
typedef void(*ScrollCallback)(Window*, double, double);

struct WindowConfiguration {
	std::string title = "Default window name";
	unsigned width = 1280;
	unsigned height = 720;
	unsigned openglProfile = GLFW_OPENGL_ANY_PROFILE;
	unsigned antialiasing = 0;
	unsigned openglMajorVersion = 1;
	unsigned openglMinorVersion = 1;
	unsigned monitor = 0;
	unsigned xPosition = 0;
	unsigned yPosition = 0;

	bool vsync = true;
	bool resizable = true;
	bool fullscreen = false;
	bool openglForwardCompatible = false;
};

//TODO add support for custom cursor
class Window {
public:
	WindowConfiguration config;
	GLFWwindow* windowHandle;
	WindowStatus status;

	ResizeCallback resizeCallback = nullptr;
	KeyCallback keyCallback = nullptr;
	CharacterCallback characterCallback = nullptr;
	CharacterWithModifierCallback characterWithModifierCallback = nullptr;
	CursorPositionCallback cursorCallback = nullptr;
	MouseButtonCallback mouseButtonCallback = nullptr;
	ScrollCallback scrollCallback = nullptr;

	Window() = default;
	Window(WindowConfiguration&);
	
	void setConfiguration(WindowConfiguration&);

	void bindContext();
	void releaseContext();

	void pollEvents();
	void swapBuffers();

	void setTitle(std::string);
	void setSize(unsigned width, unsigned height);
	void setPosition(unsigned x, unsigned y);

	void iconify();
	void restore();
	void hide();
	void show();

	bool shouldClose();

	void create(); //creates window
	void recreate(); // destroys the window and creates a new one
	void destroy(); // deletes this window (glfwDestroyWindow)

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

