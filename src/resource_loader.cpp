#include "resource_loader.h"

#include <thread>
#include <chrono>

void ResourceLoader::Loop(){
    if(load_functions_queue.size() > 0){
        auto func = load_functions_queue.front();
        load_functions_queue.pop();
        func();
    } else {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void ResourceLoader::Release(std::string name){
    cache.erase(name);
}

void ResourceLoader::Clear(){
    cache.clear();
}
