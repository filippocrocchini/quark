/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>
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
	unsigned opengl_profile = GLFW_OPENGL_ANY_PROFILE;
	unsigned antialiasing = 0;
	unsigned opengl_major = 1;
	unsigned opengl_minor = 1;
	unsigned monitor = 0;
	unsigned x_position = 0;
	unsigned y_position = 0;

	bool vsync = true;
	bool resizable = true;
	bool fullscreen = false;
	bool opengl_forward_compatible = false;
};

//TODO add support for custom cursor
class Window {
public:
	WindowConfiguration config;
	GLFWwindow* window_handle;
	WindowStatus status;

	ResizeCallback resize_callback = nullptr;
	KeyCallback key_callback = nullptr;
	CharacterCallback character_callback = nullptr;
	CharacterWithModifierCallback character_with_modifier_callback = nullptr;
	CursorPositionCallback cursor_callback = nullptr;
	MouseButtonCallback mouse_button_callback = nullptr;
	ScrollCallback scroll_callback = nullptr;

	Window() = default;
	Window(const WindowConfiguration& config);

	void SetConfiguration(const WindowConfiguration& config);

	void BindContext();
	void ReleaseContext();

	void PollEvents();
	void SwapBuffers();

	void SetTitle(const std::string& title);
	void SetSize(unsigned width, unsigned height);
	void SetPosition(unsigned x, unsigned y);

	void Iconify();
	void Restore();
	void Hide();
	void Show();

	bool ShouldClose();

	void Create(); // creates window
	void Recreate(); // destroys the window and creates a new one
	void Destroy(); // deletes this window (glfwDestroyWindow)

private:
	static std::map<GLFWwindow*, Window*> handle_to_ptr;

	static Window* GetWindow(GLFWwindow*);
	static void Resize(GLFWwindow* handle, int width, int height);
	static void Key(GLFWwindow* handle, int key, int scancode, int action, int mods);
	static void Character(GLFWwindow* handle, unsigned int codepoint);
	static void CharacterMod(GLFWwindow* handle, unsigned int codepoint, int mods);
	static void CursorPos(GLFWwindow* handle, double x, double y);
	static void MouseButton(GLFWwindow* handle, int button, int action, int mods);
	static void Scroll(GLFWwindow* handle, double xoffset, double yoffset);
};

#endif // WINDOW_H
