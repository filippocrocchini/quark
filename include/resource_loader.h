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

#include <iostream>

class Resource {
public:
    virtual bool Load() = 0;
    virtual void onLoad() = 0;
    virtual void onFail() = 0;
    virtual ~Resource() = default;
};

class ResourceLoader : public LoopingThread {
public:
    ResourceLoader(LoopController* controller) : LoopingThread(controller) {}

    template<typename T, typename... Args>
    void Load(std::string name, Args&&... args){
        finished_loading = false;

       //NOTE: I had to do this ugly thing because the compiler doesn't compile this:
       /*
       std::function<void(void)> func = [=](){
          cache.insert(std::make_pair(name, std::make_shared<T>(args...)));
       }
       */

        load_functions_queue.push(std::bind([=](Args... args2){
            auto res = std::make_shared<T>(std::forward<Args>(args2)...);
            if(res->Load())
                res->onLoad();
            else
                res->onFail();
            cache.emplace(name, res);
       }, args...));
    }

    template<typename T>
    std::shared_ptr<T> Get(std::string name){
        auto res = cache.find(name);
        if(res == cache.end()) return nullptr;
        return std::dynamic_pointer_cast<T>(res->second);
    }

    void Release(std::string name);
    void Clear();

    bool Done(){
        return load_functions_queue.empty() && finished_loading;
    }

    int cacheSize(){
        return cache.size();
    }

    void WaitUntilDone();
    void WaitUntilDone(const int timeout);
protected:
    virtual void Loop() override;
private:
    bool finished_loading = true;
    std::unordered_map<std::string, std::shared_ptr<Resource>> cache;
    std::queue<std::function<void(void)>> load_functions_queue;
};

#endif  // RESOURCE_LOADER_H
