#include "../include/core/managers/render.h"
#include "../include/engine.h"

void RenderManager::init(WindowConfiguration config) {
	window.setConfiguration(config);
}

void RenderManager::start() {
	thread = new std::thread(renderThreadMain, this);
}

void RenderManager::join() {
	thread->join();
	delete thread;
}

void RenderManager::renderThreadMain(RenderManager* self) {
	self->window.create();

	self->window.bindContext();
	while (eng::isRunning.load()) {
		self->window.pollEvents();
		
		if (self->window.shouldClose()) {
			eng::engineMtx.lock();
			eng::isRunning.store(false);
			eng::engineMtx.unlock();
		}

		//render
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (self->renderables.size() > 0) {
			for (auto rend = self->renderables.begin(); rend != self->renderables.end(); rend++) {
				if((*rend)->enabled)
					(*rend)->render();
			}
		}

		self->window.swapBuffers();
	}
	self->window.releaseContext();

	self->window.destroy();
}