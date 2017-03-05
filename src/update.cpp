#include <chrono>

#include "../include/core/managers/update.h"
#include "../include/engine.h"

std::thread* eng::UpdateManager::thread;

void eng::UpdateManager::start() {
	thread = new std::thread(updateThreadMain);
}

void eng::UpdateManager::join() {
	thread->join();
	delete thread;
}

void eng::UpdateManager::updateThreadMain() {
	auto lastTime = std::chrono::high_resolution_clock::now();
	auto currentTime = std::chrono::high_resolution_clock::now();

	double deltaTime = 0;
	while (eng::isRunning.load()) {
		currentTime = std::chrono::high_resolution_clock::now();
		deltaTime = std::chrono::duration<double>(currentTime - lastTime).count();
		lastTime = currentTime;

		if (eng::_currentScene != nullptr) {
			if (eng::_currentScene->updatables.size() > 0) {
				for (auto upd = eng::_currentScene->updatables.begin(); upd != eng::_currentScene->updatables.end(); upd++) {
					if ((*upd)->isEnabled())
						(*upd)->update(deltaTime);
				}
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

