/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#include "./window.h"

#include <functional>
#include <map>
#include <string>
#include <utility>

std::map<GLFWwindow*, Window*> Window::handle_to_ptr;

Window::Window(const WindowConfiguration& config) : config(config) {}

void Window::SetConfiguration(const WindowConfiguration& config) {
    this->config = config;
}

void Window::BindContext() {
    glfwMakeContextCurrent(window_handle);
}

void Window::ReleaseContext() {
    glfwMakeContextCurrent(0L);
}

void Window::PollEvents() {
    glfwPollEvents();
}

void Window::SwapBuffers() {
    glfwSwapBuffers(window_handle);
}

void Window::SetTitle(const std::string& title) {
    config.title = title;
    glfwSetWindowTitle(window_handle, title.c_str());
}

void Window::SetSize(uint width, uint height) {
    config.width = width;
    config.height = height;
    Resize(window_handle, width, height);
}

void Window::SetPosition(uint x, uint y) {
    config.x_position = x;
    config.y_position = y;
    glfwSetWindowPos(window_handle, x, y);
}

void Window::Iconify() {
    glfwIconifyWindow(window_handle);
}

void Window::Restore() {
    glfwRestoreWindow(window_handle);
}

void Window::Hide() {
    glfwHideWindow(window_handle);
}

void Window::Show() {
    glfwShowWindow(window_handle);
}

bool Window::ShouldClose() {
    if (status != WINDOW_OK) return true;
    return glfwWindowShouldClose(window_handle);
}

void Window::Create() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, config.opengl_major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, config.opengl_minor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, config.opengl_profile);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, config.opengl_forward_compatible);
    glfwWindowHint(GLFW_RESIZABLE, config.resizable);

    if (config.antialiasing > 0)
        glfwWindowHint(GLFW_SAMPLES, config.antialiasing);

    GLFWmonitor* monitor = 0;

    if (config.fullscreen) {
        int count;
        GLFWmonitor** monitors = glfwGetMonitors(&count);
        if (config.monitor < (uint)count) {
            monitor = monitors[config.monitor];
        }
    }

    window_handle = glfwCreateWindow(config.width, config.height, config.title.c_str(), monitor, 0);

    if (window_handle == nullptr) {
        std::cerr << "Failed to create GLFW Window.\n";
        status = WINDOW_CREATION_FAILED;
        return;
    }

    glfwSetWindowSizeCallback(window_handle, Window::Resize);
    glfwSetKeyCallback(window_handle, Window::Key);
    glfwSetCharCallback(window_handle, Window::Character);
    glfwSetCharModsCallback(window_handle, Window::CharacterMod);
    glfwSetCursorPosCallback(window_handle, Window::CursorPos);
    glfwSetMouseButtonCallback(window_handle, Window::MouseButton);
    glfwSetScrollCallback(window_handle, Window::Scroll);

    BindContext();
    {
        if (config.vsync)
            glfwSwapInterval(-1);
        else
            glfwSwapInterval(0);
    }
    ReleaseContext();

    Window::handle_to_ptr.insert(std::pair<GLFWwindow*, Window*>(window_handle, this));

    status = WINDOW_OK;
}

void Window::Destroy() {
    glfwDestroyWindow(window_handle);

    if (Window::handle_to_ptr.size() > 0 && Window::handle_to_ptr.find(window_handle) != Window::handle_to_ptr.end())
        Window::handle_to_ptr.erase(window_handle);
    status = WINDOW_DESTROYED;
}

void Window::Recreate() {
    Destroy();
    Create();
}

Window* Window::GetWindow(GLFWwindow* handle) {
    Window* window = nullptr;
    try {
        window = Window::handle_to_ptr[handle];
    }
    catch (std::out_of_range e) {
        return nullptr;
    }
    return window;
}

void Window::Resize(GLFWwindow* handle, int width, int height) {
    Window* window = GetWindow(handle);

    if (window != nullptr) {
        if (window->resize_callback != nullptr)
            window->resize_callback(window, width, height);
    }
}

void Window::Key(GLFWwindow* handle, int key, int scancode, int action, int mods) {
    Window* window = GetWindow(handle);

    if (window != nullptr) {
        if (window->key_callback != nullptr)
            window->key_callback(window, key, scancode, action, mods);
    }
}

void Window::Character(GLFWwindow* handle, uint codepoint) {
    Window* window = GetWindow(handle);

    if (window != nullptr) {
        if (window->character_callback != nullptr)
            window->character_callback(window, codepoint);
    }
}

void Window::CharacterMod(GLFWwindow* handle, uint codepoint, int mods) {
    Window* window = GetWindow(handle);

    if (window != nullptr) {
        if (window->character_with_modifier_callback != nullptr)
            window->character_with_modifier_callback(window, codepoint, mods);
    }
}

void Window::CursorPos(GLFWwindow* handle, double x, double y) {
    Window* window = GetWindow(handle);

    if (window != nullptr) {
        if (window->cursor_callback != nullptr)
            window->cursor_callback(window, x, y);
    }
}

void Window::MouseButton(GLFWwindow* handle, int button, int action, int mods) {
    Window* window = GetWindow(handle);

    if (window != nullptr) {
        if (window->mouse_button_callback != nullptr)
            window->mouse_button_callback(window, button, action, mods);
    }
}

void Window::Scroll(GLFWwindow* handle, double xoffset, double yoffset) {
    Window* window = GetWindow(handle);

    if (window != nullptr) {
        if (window->scroll_callback != nullptr)
            window->scroll_callback(window, xoffset, yoffset);
    }
}
