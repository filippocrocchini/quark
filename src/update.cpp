#include "../include/core/managers/update.h"
#include "../include/engine.h"

void UpdateManager::start() {
	thread = new std::thread(updateThreadMain, this);
}

void UpdateManager::join() {
	thread->join();
	delete thread;
}

void UpdateManager::updateThreadMain(UpdateManager* self) {
	while (eng::isRunning.load()) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}