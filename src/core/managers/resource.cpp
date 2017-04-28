#include <string>
#include <fstream>
#include <sstream>
#include <ios>

#include "core/managers/resource.h"
#include "core/engine.h"

#include <assimp/scene.h>

std::unordered_map<std::type_index, std::shared_ptr<LoaderBase>> ResourceManager::loaders;

AsyncResourceManager::AsyncResourceManager(uint32_t queueSize) {
	toload.setMaxSize(queueSize);
}

void AsyncResourceManager::loop() {
	while (eng::isRunning.load()) {
		if (toload.size() > 0) {
			std::cout << toload.size() << std::endl;
			ResourceLoadFunction func;
			toload.pop(&func);
			func();
		}
		else {
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	}
}

/*
SharedQueue<ResourceTemplate> eng::resource_manager::toLoad(100);
std::map<std::string, Resource&> eng::resource_manager::loadedResources;

void eng::resource_manager::loadAll(ResourceList list) {
	for(auto itr = list.begin(); itr != list.end(); itr++)
	{
		loadResource(**itr);
	}
}

void eng::resource_manager::loadResource(ResourceTemplate res) {
	toLoad.push(res);
}*/

