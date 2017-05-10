/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#ifndef RESOURCE_LOADER_H
#define RESOURCE_LOADER_H

#include "looping_thread.h"

#include <memory>
#include <string>
#include <unordered_map>
#include <queue>
#include <functional>

class Resource {
public:
    virtual ~Resource() = default;
};

class ResourceLoader : public LoopingThread {
public:
    ResourceLoader(LoopController* controller) : LoopingThread(controller) {}

    template<typename T, typename... Args>
    void Load(std::string name, Args... args){

        std::function<void(void)> func = std::bind([&](Args... args2){
           cache.insert(std::make_pair(name, std::make_shared<T>(args2...)));
        }, args...);

       //NOTE: I had to do this ugly thing because the compile does't compile this:
       /*
       std::function<void(void)> func = [&](){
          cache.insert(std::make_pair(name, std::make_shared<T>(args...)));
       }
       */

        load_functions_queue.push(func);
    }

    template<typename T>
    std::shared_ptr<T> Get(std::string name){
        auto res = cache.find(name);
        if(res == cache.end()) return nullptr;
        return std::dynamic_pointer_cast<T>(res);
    }

    void Release(std::string name);
    void Clear();
protected:
    virtual void Loop() override;
private:
    std::unordered_map<std::string, std::shared_ptr<Resource>> cache;
    std::queue<std::function<void(void)>> load_functions_queue;
};

#endif  // RESOURCE_LOADER_H
