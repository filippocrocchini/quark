/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#ifndef RESOURCE_LOADER_H
#define RESOURCE_LOADER_H

#include "looping_thread.h"

#include <memory>
#include <string>
#include <unordered_map>
#include <functional>

class Resource {
public:
    virtual ~Resource() = default;
}

class ResourceLoader : public LoopingThread {
public:
    ResourceLoader(LoopController* controller) : LoopingThread(controller) {}

    template<typename... Args>
    void Load(std::string name, Args... args){
    }

    template<typename T>
    std::shared_ptr<T> Get(std::string name){
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
