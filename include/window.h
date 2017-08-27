/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#ifndef WINDOW_H  // NOLINT()
#define WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <map>
#include <string>
#include <functional>

enum WindowStatus {
    WINDOW_NULL,
    WINDOW_OK,
    WINDOW_CREATION_FAILED,
    WINDOW_DESTROYED
};

class Window;

typedef std::function<void(Window*, int, int)> ResizeCallback;
typedef std::function<void(Window*, int, int, int, int)> KeyCallback;
typedef std::function<void(Window*, uint)> CharacterCallback;
typedef std::function<void(Window*, uint, int)> CharacterWithModifierCallback;
typedef std::function<void(Window*, double, double)> CursorPositionCallback;
typedef std::function<void(Window*, int, int, int)> MouseButtonCallback;
typedef std::function<void(Window*, double, double)> ScrollCallback;

struct WindowConfiguration {
    std::string title = "Default window name";
    uint width = 1280;
    uint height = 720;
    uint opengl_profile = GLFW_OPENGL_ANY_PROFILE;
    uint antialiasing = 0;
    uint opengl_major = 1;
    uint opengl_minor = 1;
    uint monitor = 0;
    uint x_position = 0;
    uint y_position = 0;

    bool vsync = true;
    bool resizable = true;
    bool fullscreen = false;
    bool opengl_forward_compatible = false;
};

// TODO(filippocrocchini): add support for custom cursor
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
    explicit Window(const WindowConfiguration& config);

    void SetConfiguration(const WindowConfiguration& config);

    void BindContext();
    void ReleaseContext();

    void PollEvents();
    void SwapBuffers();

    void SetTitle(const std::string& title);
    void SetSize(uint width, uint height);
    void SetPosition(uint x, uint y);

    void Iconify();
    void Restore();
    void Hide();
    void Show();

    bool ShouldClose();

    void Create();  // creates window
    void Recreate();  // destroys the window and creates a new one
    void Destroy();  // deletes this window (glfwDestroyWindow)

    int GetWidth() { return config.width; }
    int GetHeight() { return config.height; }

 private:
    static std::map<GLFWwindow*, Window*> handle_to_ptr;

    static Window* GetWindow(GLFWwindow*);
    static void Resize(GLFWwindow* handle, int width, int height);
    static void Key(GLFWwindow* handle, int key, int scancode, int action, int mods);
    static void Character(GLFWwindow* handle, uint codepoint);
    static void CharacterMod(GLFWwindow* handle, uint codepoint, int mods);
    static void CursorPos(GLFWwindow* handle, double x, double y);
    static void MouseButton(GLFWwindow* handle, int button, int action, int mods);
    static void Scroll(GLFWwindow* handle, double xoffset, double yoffset);
};

#endif  // NOLINT() WINDOW_H
