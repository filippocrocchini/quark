#include <GL\glew.h>

#include "../include/engine.h"

EngineConfiguration eng::configuration;

RenderManager eng::renderer;
UpdateManager eng::updater;
Input eng::input;

std::atomic_bool eng::isRunning;
std::mutex eng::engineMtx;

bool eng::init() {
	if (!glfwInit()) {
		std::fprintf(stderr, "Failed to initialize GLFW.\n");
		return false;
	}

	if (!glewInit()) {
		std::fprintf(stderr, "Failed to initialize GLEW.\n");
		return false;
	}

	return true;
}

void eng::start() {
	isRunning.store(true);
	renderer.init(configuration.windowConfiguration);

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
