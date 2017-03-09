#pragma once
#include <thread>
#include <vector>
#include <map>
#include "core/threads/thread_safe_queue.h"

#define RESOURCE_TEXT_FILE 0
#define RESOURCE_BINARY_FILE 1
#define RESOURCE_MODEL 2
#define RESOURCE_IMAGE 3

struct ResourceTemplate {
	std::string file;
	std::string name;
	int resourceType;
};

typedef std::vector<ResourceTemplate> ResourceList;

class Resource {
public:
	virtual ~Resource() {}
};
class TextFileResource : public Resource{

};

namespace eng {
	namespace resource_manager {
		extern std::thread* thread;
		extern SharedQueue<ResourceTemplate> toLoad;
		extern std::map<std::string, Resource> loadedResources;

		extern void loadAll(ResourceList);
		extern void loadResource(ResourceTemplate);

		template<typename T, typename std::enable_if<std::is_base_of<Resource, T>::value>::type* = nullptr>
		bool getResource(std::string name, T* resource) {
			std::map<std::string, Resource>::const_iterator id = loadedResources.find(name);
			if (id == loadedResources.end()) return false;
			*resource = id->second;
			return true;
			/*
			@Unsafe, i'm assuming that if i have the name of the resource in the
			name_to_id map the corresponding resource has been succesfully loaded.
			*/
		}

		extern void start();
		extern void join();
		extern void resourceLoaderThreadMain();
	}
}