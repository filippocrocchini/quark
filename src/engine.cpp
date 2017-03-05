#include <GL\glew.h>

#include "../include/engine.h"

EngineConfiguration eng::configuration;

std::atomic_bool eng::isRunning;
std::mutex eng::engineMtx;

Scene* eng::_currentScene;

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

void eng::create() {
	RenderManager::init(configuration.windowConfiguration);
	Input::bindCallbacks(RenderManager::window);
}

void eng::start() {
	//Initialize all game objects;
	Input::registerMouseMoveHandler(test);
	
	isRunning.store(true);
	RenderManager::start();
	UpdateManager::start();
}

void eng::joinAll() {
	RenderManager::join();
	UpdateManager::join();
}

void eng::terminate() {
	glfwTerminate();
}

void eng::setCurrentScene(Scene& scene) {
	_currentScene = &scene;
	//@Implement
}

