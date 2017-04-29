#include "core/managers/resource.h"
#include "core/engine.h"


std::unordered_map<std::type_index, std::shared_ptr<LoaderBase>> ResourceManager::loaders;

AsyncResourceManager::AsyncResourceManager(uint32_t queueSize) {
	toload.setMaxSize(queueSize);
}

void AsyncResourceManager::loop() {
	while (eng::isRunning.load()) {
		if (toload.size() > 0) {
			ResourceLoadFunction func;
			toload.pop(&func);
			func();
		}
		else {
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	}
}
