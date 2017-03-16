#include <string>
#include <fstream>
#include <sstream>
#include <ios>

#include "core/managers/resource.h"
#include "core/engine.h"

#include <assimp/scene.h>

std::unordered_map<std::type_index, LoaderBase*> ResourceManager::loaders;

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


std::string loadTextFile(std::string path) {
	std::stringstream text;
	std::ifstream file;
	
	try {
		file.open(path);
	}
	catch (std::ios::failure exc) {
		std::cout << exc.what() << std::endl;
		file.close();
		return "";
	}

	text << file.rdbuf();
	file.close();

	return text.str();
}
