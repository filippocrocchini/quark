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

#define RESOURCE_TEXT_FILE 0
#define RESOURCE_BINARY_FILE 1
#define RESOURCE_MODEL 2
#define RESOURCE_IMAGE 3

class CacheBase {
public:
	~CacheBase() = default;
};

//@Unsafe Not thread safe 
template <class T>
class ResourceCache : public CacheBase{
public:
	std::unordered_map<std::string,T> cache_data;
	ResourceCache() {

	}

	void add(std::string name,T &res) {
		cache_data.insert(std::make_pair(name,res));
	}

	T* get(std::string name) {
		auto dataItr = cache_data.find(name);
		if (dataItr == cache_data.end()) {
			return nullptr;
		}
		return &(dataItr->second);
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
	void cacheResource(std::string name,T &res) {
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
	T* getResource(std::string name) {
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
	std::function<T(std::string)> load;
};

class ResourceManager {
public:
	static std::unordered_map<std::type_index, LoaderBase*> loaders;

	template<typename T>
	static void registerLoader(std::function<T(std::string)> loaderFunction) {

		Loader<T> *loader = new Loader<T>();
		loader->load = loaderFunction;
		loaders.insert(std::pair<std::type_index, LoaderBase*>(typeid(T), loader));
	}

	template<typename T>
	T* loadResource(std::string name, std::string filepath) {
		T* resource = cache.getResource<T>(name);
		if (resource == nullptr) {
			if (!loadAndCache<T>(name, filepath)) return nullptr;
			else resource = cache.getResource<T>(name);
		}
		return resource;
	}

	template<typename T>
	T* getResource(std::string name) {
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

		Loader<T>* loader = dynamic_cast<Loader<T>*>(loaderItr->second);
		if (loader == nullptr) {
			std::cerr << "The loader associated with type: " << typeid(T).name() << " is not valid." << std::endl;
			return false;
		}

		try {
			T result = loader->load(filepath);
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
	bool addResourceToQueue(std::string name, std::string filepath, std::function<void(T&)> onLoad = [](T&) {}, std::function<void(void)> onFail = []() {}) {
		if (manager.getResource<T>(name) != nullptr) return true;
		return toload.push([this, name, filepath, onLoad, onFail]() {
			this->loadResource<T>(name, filepath, onLoad, onFail);
		});
	}

	template<typename T>
	T* getResource(std::string name) {
		return manager.getResource<T>(name);
	}
private:
	struct ResourceBase {
		std::string name;
		std::string filepath;
	};

	template<typename T>
	struct ResourceTemplate : public ResourceBase{
		std::function<void(T&)> onLoad = [](T&) {};
		std::function<void(void)> onFail = []() {};
	};

	typedef std::function<void(void)> ResourceLoadFunction;

	ResourceManager manager;
	SharedQueue<ResourceLoadFunction> toload;

	template <typename T>
	void loadResource(std::string name, std::string filepath, std::function<void(T&)> onLoad, std::function<void(void)> onFail) {
		T* resource = manager.loadResource<T>(name, filepath);
		if (resource != nullptr) {
			onLoad(*resource);
		}
		else {
			onFail();
		}
	}
};

