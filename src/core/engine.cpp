#include <GLEW/glew.h>
#include "core/engine.h"
#include "core/resources/textfile.h"
#include "core/resources/shader.h"
#include "core/resources/texture.h"
#include "core/resources/mesh.h"

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

bool eng::init() {
	if (!glfwInit()) {
		std::fprintf(stderr, "Engine: Failed to initialize GLFW.\n");
		return false;
	}
	return true;
}

void eng::create() {
	renderer.init(configuration.windowConfiguration);
	input::bindCallbacks(renderer.window);

	ResourceManager::registerLoader<TextFileResource>(TextFileResource::load);
	ResourceManager::registerLoader<Shader>(Shader::load);
    ResourceManager::registerLoader<Texture>(Texture::load);
}

void eng::startLoop() {
	isRunning.store(true);

	render_thread.start();
	update_thread.start();
	resource_thread.start();
}

void eng::joinAll() {

	render_thread.join();
	update_thread.join();
	resource_thread.join();

    std::cout << "Joined all threads.\n";
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
	// @Implement
    // (Filippo 28/04/17 ) I forgot what i wanted to implement
}

void eng::setWindowConfiguration(const WindowConfiguration& windowConfiguration) {
    configuration.windowConfiguration = windowConfiguration;
}

