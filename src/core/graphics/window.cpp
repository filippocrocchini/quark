#include "core/graphics/window.h"

std::map<GLFWwindow*, Window*> Window::handleToPtr;

Window::Window(WindowConfiguration config){
	setConfiguration(config);
}


void Window::setConfiguration(WindowConfiguration config) {
	this->config = config;
}

void Window::bindContext(){
	glfwMakeContextCurrent(windowHandle);
}

void Window::releaseContext(){
	glfwMakeContextCurrent(0L);
}

void Window::pollEvents(){
	glfwPollEvents();
}

void Window::swapBuffers() {
	glfwSwapBuffers(windowHandle);
}

void Window::setTitle(std::string title){
	config.title = title;
	glfwSetWindowTitle(windowHandle, title.c_str());
}

void Window::setSize(uint32_t width, uint32_t height){
	config.width = width;
	config.height = height;
	resize(windowHandle, width, height);
}

void Window::setPosition(uint32_t x, uint32_t y){
	config.xPosition = x;
	config.yPosition = y;
	glfwSetWindowPos(windowHandle, x, y);
}

void Window::iconify(){
	glfwIconifyWindow(windowHandle);
}

void Window::restore(){
	glfwRestoreWindow(windowHandle);
}

void Window::hide(){
	glfwHideWindow(windowHandle);
}

void Window::show(){
	glfwShowWindow(windowHandle);
}

bool Window::shouldClose(){
	return glfwWindowShouldClose(windowHandle);
}

void Window::create() {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, config.openglMajorVersion);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, config.openglMinorVersion);
	glfwWindowHint(GLFW_OPENGL_PROFILE, config.openglProfile);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, config.openglForwardCompatible);
	glfwWindowHint(GLFW_RESIZABLE, config.resizable);
	
	if(config.antialiasing > 0)
		glfwWindowHint(GLFW_SAMPLES, config.antialiasing);	

	GLFWmonitor* monitor = 0;

	if (config.fullscreen) {
		int count;
		GLFWmonitor** monitors = glfwGetMonitors(&count);
		if (config.monitor < count) {
			monitor = monitors[config.monitor];
		}
	}

	windowHandle = glfwCreateWindow(config.width, config.height, config.title.c_str(), monitor, 0);

	if (windowHandle == nullptr) {
		std::cerr << "Failed to create GLFW Window.\n";
		status = WINDOW_CREATION_FAILED;
		return;
	}

	glfwSetWindowSizeCallback(windowHandle, Window::resize);
	glfwSetKeyCallback(windowHandle, Window::key);
	glfwSetCharCallback(windowHandle, Window::character);
	glfwSetCharModsCallback(windowHandle, Window::character_mod);
	glfwSetCursorPosCallback(windowHandle, Window::cursor_pos);
	glfwSetMouseButtonCallback(windowHandle, Window::mouse_button);
	glfwSetScrollCallback(windowHandle, Window::scroll);

	bindContext();
	{
		if (config.vsync)
			glfwSwapInterval(-1);
		else
			glfwSwapInterval(0);
	}
	releaseContext();

	Window::handleToPtr.insert(std::pair<GLFWwindow*, Window*>(windowHandle, this));
}

void Window::destroy(){
	glfwDestroyWindow(windowHandle);

	if(Window::handleToPtr.size() > 0 && Window::handleToPtr.find(windowHandle) != Window::handleToPtr.end())
		Window::handleToPtr.erase(windowHandle);
}

void Window::recreate(){
	destroy();
	create();
}

Window* Window::getWindow(GLFWwindow* handle) {
	Window* window = nullptr;
	try {
		window = Window::handleToPtr[handle];
	}
	catch (std::out_of_range e) {
		return nullptr;
	}
	return window;
}

void Window::resize(GLFWwindow* handle, int width, int height){
	Window* window = getWindow(handle);

	if (window != nullptr) {
		if(window->resizeCallback != nullptr)
			window->resizeCallback(window, width, height);
	}
}

void Window::key(GLFWwindow* handle, int key, int scancode, int action, int mods) {
	Window* window = getWindow(handle);

	if (window != nullptr) {
		if (window->keyCallback != nullptr)
			window->keyCallback(window, key, scancode, action, mods);
	}
}

void Window::character(GLFWwindow* handle, unsigned int codepoint) {
	Window* window = getWindow(handle);

	if (window != nullptr) {
		if (window->characterCallback != nullptr)
			window->characterCallback(window, codepoint);
	}
}

void Window::character_mod(GLFWwindow* handle, unsigned int codepoint, int mods) {
	Window* window = getWindow(handle);

	if (window != nullptr) {
		if (window->characterWithModifierCallback != nullptr)
			window->characterWithModifierCallback(window, codepoint, mods);
	}
}

void Window::cursor_pos(GLFWwindow* handle, double x, double y) {
	Window* window = getWindow(handle);

	if (window != nullptr) {
		if (window->cursorCallback != nullptr)
			window->cursorCallback(window, x, y);
	}
}

void Window::mouse_button(GLFWwindow* handle, int button, int action, int mods) {
	Window* window = getWindow(handle);

	if (window != nullptr) {
		if (window->mouseButtonCallback != nullptr)
			window->mouseButtonCallback(window, button, action, mods);
	}
}

void Window::scroll(GLFWwindow* handle, double xoffset, double yoffset) {
	Window* window = getWindow(handle);

	if (window != nullptr) {
		if (window->scrollCallback != nullptr)
			window->scrollCallback(window, xoffset, yoffset);
	}
}