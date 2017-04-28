#pragma once
#include <iostream>
#include <thread>
#include <unordered_set>
#include <unordered_map>
#include <typeindex>
#include <functional>
#include <exception>

#include "core/threads/thread_safe_container.h"
#include "core/threads/mythread.h"

class CacheBase {
public:
	~CacheBase() = default;
};

//@Unsafe Not thread safe
template <class T>
class ResourceCache : public CacheBase{
public:
	std::unordered_map<std::string,std::shared_ptr<T>> cache_data;
	ResourceCache() {

	}

	void add(std::string name,std::shared_ptr<T> res) {
		cache_data.insert(std::make_pair(name,res));
	}

	std::shared_ptr<T> get(std::string name) {
		auto dataItr = cache_data.find(name);
		if (dataItr == cache_data.end()) {
			return nullptr;
		}
		return dataItr->second;
	}
};
class TypeIndependentCache {
public:
	std::unordered_map<std::type_index, CacheBase*> caches;

	~TypeIndependentCache() {
		for (auto cacheItr = caches.begin(); cacheItr != caches.end(); cacheItr++) {
			delete cacheItr->second;
		}
	}

	template<typename T>
	void cacheResource(std::string name,std::shared_ptr<T> res) {
		auto cacheItr = caches.find(typeid(T));
		ResourceCache<T>* cache;

		if(cacheItr == caches.end())
			caches.insert(std::pair<std::type_index, CacheBase*>(typeid(T), cache = new ResourceCache<T>()));
		else {
			cache = static_cast<ResourceCache<T>*>(cacheItr->second);
		}

		cache->add(name,res);
	}

	template<typename T>
	std::shared_ptr<T> getResource(std::string name) {
		auto cacheItr = caches.find(typeid(T));
		ResourceCache<T>* cache;

		if (cacheItr == caches.end())
			return nullptr;

		cache = static_cast<ResourceCache<T>*>(cacheItr->second);
		return cache->get(name);
	}
};

class LoaderBase {
public:
	virtual ~LoaderBase() = default;
};

template<typename T>
class Loader : public LoaderBase{
public:
	std::function<std::shared_ptr<T>(std::string)> load;
};

class ResourceManager {
public:
	static std::unordered_map<std::type_index, std::shared_ptr<LoaderBase>> loaders;

	template<typename T>
	static void registerLoader(std::function<std::shared_ptr<T>(std::string)> loaderFunction) {
		std::shared_ptr<Loader<T>> loader = std::make_shared<Loader<T>>();
		loader->load = loaderFunction;
		loaders.insert(std::pair<std::type_index, std::shared_ptr<LoaderBase>>(typeid(T),loader));
	}

	template<typename T>
	std::shared_ptr<T> loadResource(std::string name, std::string filepath) {
		std::shared_ptr<T> resource = cache.getResource<T>(name);
		if (resource == nullptr) {
			if (!loadAndCache<T>(name, filepath)) return nullptr;
			else resource = cache.getResource<T>(name);
		}
		return resource;
	}

	template<typename T>
	std::shared_ptr<T> getResource(std::string name) {
		return cache.getResource<T>(name);
	}

private:
	TypeIndependentCache cache;

	template<typename T>
	bool loadAndCache(std::string name, std::string filepath) {

		auto loaderItr = loaders.find(typeid(T));
		if (loaderItr == loaders.end()) {
			std::cerr << "No loader is associated with type: " << typeid(T).name() << std::endl;
			return false;
		}

		std::shared_ptr<Loader<T>> loader = std::dynamic_pointer_cast<Loader<T>>(loaderItr->second);
		if (loader == nullptr) {
			std::cerr << "The loader associated with type: " << typeid(T).name() << " is not valid." << std::endl;
			return false;
		}

		try {
			std::shared_ptr<T> result = loader->load(filepath);
			cache.cacheResource(name, result);
		}
		catch (std::exception e) {
			std::cerr << e.what() << std::endl;
			return false;
		}

		return true;
	}
};


//Delete the ResourceTemplate* after loading
class AsyncResourceManager : public ThreadLoop{
public:
	AsyncResourceManager(uint32_t);

	void loop();

    template<typename T>
	bool addResourceToQueue(std::string name, std::string filepath, std::function<void(std::shared_ptr<T>)> onLoad) {
        return addResourceToQueue(name, filepath, onLoad, []() {});
	}

	template<typename T>
	bool addResourceToQueue(std::string name, std::string filepath, std::function<void(std::shared_ptr<T>)> onLoad, std::function<void(void)> onFail) {
		if (manager.getResource<T>(name) != nullptr) return true;
		return toload.push([this, name, filepath, onLoad, onFail]() {
			this->loadResource<T>(name, filepath, onLoad, onFail);
		});
	}

	template<typename T>
	std::shared_ptr<T> getResource(std::string name) {
		return manager.getResource<T>(name);
	}
private:
	struct ResourceBase {
		std::string name;
		std::string filepath;
	};

	typedef std::function<void(void)> ResourceLoadFunction;

	ResourceManager manager;
	SharedQueue<ResourceLoadFunction> toload;

	template <typename T>
	void loadResource(std::string name, std::string filepath, std::function<void(std::shared_ptr<T>)> onLoad, std::function<void(void)> onFail) {
		std::shared_ptr<T> resource = manager.loadResource<T>(name, filepath);
		if (resource != nullptr) {
			onLoad(resource);
		}
		else {
			onFail();
		}
	}
};
