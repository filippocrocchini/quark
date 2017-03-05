#include "core\managers\resource.h"
#include "core\engine.h"

std::thread* eng::resource_manager::thread;
SharedQueue<ResourceTemplate> eng::resource_manager::toLoad(100);
std::map<std::string, Resource> eng::resource_manager::loadedResources;

void eng::resource_manager::loadAll(ResourceList list) {
	for each(ResourceTemplate tmp in list) {
		loadResource(tmp);
	}
}

void eng::resource_manager::loadResource(ResourceTemplate res) {
	toLoad.push(res);
}

void eng::resource_manager::start() {
	thread = new std::thread(resourceLoaderThreadMain);
}

void eng::resource_manager::join() {
		thread->join();
	delete thread;
}

void eng::resource_manager::resourceLoaderThreadMain() {
	while (eng::isRunning) {
		ResourceTemplate resTmp;
		if (toLoad.pop(&resTmp)) {
			switch (resTmp.resourceType) {
			case RESOURCE_TEXT_FILE:
				std::printf("Loaded resource file, TEXT.\n");
				break;
			}
		}
		else {
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	}
}