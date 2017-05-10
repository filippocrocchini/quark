#include "resource_loader.h"

#include <thread>
#include <chrono>

void ResourceLoader::Loop(){
    std::cout << "Cycle\n";
    if(!load_functions_queue.empty()){
        std::cout << "Found resources to load.\n";
        auto func = load_functions_queue.front();
        load_functions_queue.pop();
        std::cout << "Popped load function.\n";
        func();
    } else {
        finished_loading = true;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void ResourceLoader::Release(std::string name){
    cache.erase(name);
}

void ResourceLoader::Clear(){
    cache.clear();
}

void ResourceLoader::WaitUntilDone(){
    while(!Done()){
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void ResourceLoader::WaitUntilDone(const int timeout){
    auto start = std::chrono::steady_clock::now();
    auto now = std::chrono::steady_clock::now();

    while(!Done()){
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        now = std::chrono::steady_clock::now();

        if(std::chrono::duration_cast<std::chrono::milliseconds>(now-start).count() >= timeout) break;
    }
}
