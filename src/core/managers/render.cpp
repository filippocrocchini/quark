#include <GLEW\glew.h>

#include "core/managers/render.h"
#include "core/engine.h"


void RenderManager::init(WindowConfiguration config) {
	window.setConfiguration(config);
}

void RenderManager::start() {
    window.create();

    //@Unsafe, if there is more than one window the context needs to be bound in the while loop
    window.bindContext();
    
    if (!glewInit()) {
		std::fprintf(stderr, "Engine: Failed to initialize GLEW.\n");
    }
}

void RenderManager::stop() {
	window.releaseContext();
	window.destroy();
}

void RenderManager::loop() {
	start();

	while (eng::isRunning.load() && window.status == WINDOW_OK) {
        window.pollEvents();

		if (window.shouldClose()) {
			eng::engineMtx.lock();
			eng::isRunning.store(false);
			eng::engineMtx.unlock();
            break;
		}
		if (eng::_currentScene != nullptr) {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			if (eng::_currentScene->renderables.size() > 0) {
				for (auto rend = eng::_currentScene->renderables.begin(); rend != eng::_currentScene->renderables.end(); rend++) {
					if ((*rend)->isEnabled())
						(*rend)->render();
				}
			}
		}

		window.swapBuffers();
		window.releaseContext();
	}

	stop();
}



/*

std::thread* eng::render_manager::thread;
Window eng::render_manager::window;


void eng::render_manager::init(WindowConfiguration config) {
	window.setConfiguration(config);
}

void eng::render_manager::start() {
	thread = new std::thread(renderThreadMain);
}

void eng::render_manager::join() {
	thread->join();
	delete thread;
}

void eng::render_manager::renderThreadMain() {
	window.create();

	window.bindContext();
	while (eng::isRunning.load()) {
		window.pollEvents();
		
		if (window.shouldClose()) {
			eng::engineMtx.lock();
			eng::isRunning.store(false);
			eng::engineMtx.unlock();
		}
		if (eng::_currentScene != nullptr) {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			if (eng::_currentScene->renderables.size() > 0) {
				for (auto rend = eng::_currentScene->renderables.begin(); rend != eng::_currentScene->renderables.end(); rend++) {
					if ((*rend)->isEnabled())
						(*rend)->render();
				}
			}
		}

		window.swapBuffers();
	}
	window.releaseContext();

	window.destroy();
}

*/