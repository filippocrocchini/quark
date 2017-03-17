#include <GL/glew.h>
#include "core/engine.h"
#include "core/resources/textfile.h"

EngineConfiguration eng::configuration;

RenderManager eng::renderer;
UpdateManager eng::updater;
AsyncResourceManager eng::resource_loader(100);

Thread eng::resource_thread(eng::resource_loader);
Thread eng::render_thread(eng::renderer);
Thread eng::update_thread(eng::updater);

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
	renderer.init(configuration.windowConfiguration);
	input::bindCallbacks(renderer.window);

	ResourceManager::registerLoader<TextFileResource>(TextFileResource::load);
}

void eng::startLoop() {
	//Initialize all game objects;
	input::registerMouseMoveHandler(test);
	
	isRunning.store(true);

	render_thread.start();
	update_thread.start();
	resource_thread.start();

	//resource_manager::start();
}

void eng::joinAll() {

	render_thread.join();
	update_thread.join();
	resource_thread.join();
	//resource_manager::join();
}

void eng::terminate() {
	glfwTerminate();
}

void eng::startLoopJoinAndTerminate(){
	startLoop();
	joinAll();
	terminate();
}

void eng::setCurrentScene(Scene& scene) {
	_currentScene = &scene;
	//@Implement
}

