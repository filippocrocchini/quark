#include "../include/core/managers/render.h"
#include "../include/engine.h"

std::thread* eng::RenderManager::thread;
Window eng::RenderManager::window;

void eng::RenderManager::init(WindowConfiguration config) {
	window.setConfiguration(config);
}

void eng::RenderManager::start() {
	thread = new std::thread(renderThreadMain);
}

void eng::RenderManager::join() {
	thread->join();
	delete thread;
}

void eng::RenderManager::renderThreadMain() {
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