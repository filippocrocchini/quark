#include <GL\glew.h>

#include "../include/engine.h"

EngineConfiguration eng::configuration;
RenderManager eng::renderer;
UpdateManager eng::updater;

std::atomic_bool eng::isRunning;
std::mutex eng::engineMtx;

void test(eng::Input::MouseMoveEvent *e) {
	std::printf("Mouse deltax: %f, deltay: %f.\n", e->deltaX, e->deltaY);
}

bool eng::init() {
	if (!glfwInit()) {
		std::fprintf(stderr, "Engine: Failed to initialize GLFW.\n");
		return false;
	}

	if (!glewInit()) {
		std::fprintf(stderr, "Engine: Failed to initialize GLEW.\n");
		return false;
	}

	return true;
}

void eng::prepare() {
	isRunning.store(true);
	renderer.init(configuration.windowConfiguration);
	Input::bindCallbacks(&renderer.window);
}

void eng::start() {
	//Initialize all game objects;
	Input::registerMouseMoveHandler(test);
	
	renderer.start();
	updater.start();
}

void eng::joinAll() {
	renderer.join();
	updater.join();
}

void eng::terminate() {
	glfwTerminate();
}

