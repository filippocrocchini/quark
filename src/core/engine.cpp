#include <GL/glew.h>

#include "core/engine.h"

EngineConfiguration eng::configuration;

std::atomic_bool eng::isRunning;
std::mutex eng::engineMtx;

Scene* eng::_currentScene;

void test(eng::input::MouseMoveEvent *e) {
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
	render_manager::init(configuration.windowConfiguration);
	input::bindCallbacks(render_manager::window);
}

void eng::start() {
	//Initialize all game objects;
	input::registerMouseMoveHandler(test);
	
	isRunning.store(true);
	resource_manager::start();
	render_manager::start();
	update_manager::start();
}

void eng::joinAll() {
	resource_manager::join();
	render_manager::join();
	update_manager::join();
}

void eng::terminate() {
	glfwTerminate();
}

void eng::setCurrentScene(Scene& scene) {
	_currentScene = &scene;
	//@Implement
}

