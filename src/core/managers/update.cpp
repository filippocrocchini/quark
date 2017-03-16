#include <chrono>

#include "core/managers/update.h"
#include "core/engine.h"


void UpdateManager::loop() {
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

/*

std::thread* eng::update_manager::thread;

void eng::update_manager::start() {
	thread = new std::thread(updateThreadMain);
}

void eng::update_manager::join() {
	thread->join();
	delete thread;
}

void eng::update_manager::updateThreadMain() {
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

*/