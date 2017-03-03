#include "../include/core/graphics/window.h"

std::map<GLFWwindow*, Window*> Window::handleToPtr;

Window::Window(WindowConfiguration config){
	this->config = config;
}

Window::~Window(){
	destroy();
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
		std::fprintf(stderr, "Failed to create GLFW Window.\n");
		status = WINDOW_CREATION_FAILED;
	}

	glfwSetWindowSizeCallback(windowHandle, Window::resize);
	
	bindContext();
	{
		if (config.vsync)
			glfwSwapInterval(-1);
		else
			glfwSwapInterval(0);
	}
	releaseContext();

	handleToPtr[windowHandle] = this;
}

void Window::destroy(){
	glfwDestroyWindow(windowHandle);
	handleToPtr.erase(windowHandle);
}

void Window::resize(GLFWwindow* handle, int width, int height){
	Window* window;
	try {
		window = handleToPtr[handle];
	}
	catch (std::out_of_range e) {
		return;
	}
	if (window != nullptr) {
		if(window->resizeCallback != nullptr)
			window->resizeCallback(window, width, height);
	}
}
