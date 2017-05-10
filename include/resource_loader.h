/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#ifndef RESOURCE_LOADER_H
#define RESOURCE_LOADER_H

#include "looping_thread.h"

#include <string>
#include <queue>
#include <functional>

class Resource {
public:
    virtual bool Load() = 0;
    virtual void onLoad() = 0;
    virtual void onFail() = 0;
    virtual ~Resource() = default;
};

#include "registry.h"

class ResourceLoader : public LoopingThread, private Registry<std::string, Resource>{
public:
    ResourceLoader(LoopController* controller) : LoopingThread(controller) {}

    template<typename T, typename... Args>
    void LoadResource(std::string name, Args&&... args){
        finished_loading = false;

       //NOTE: I had to do this ugly thing because the compiler doesn't compile this:
       /*
       std::function<void(void)> func = [=](){
          cache.insert(std::make_pair(name, std::make_shared<T>(args...)));
       }
       */

        load_functions_queue.push(std::bind([=](Args... args2){
            T* res = new T{std::forward<Args>(args2)...};
            Register(name, static_cast<Resource*>(res));
       }, args...));
    }

    template<typename T>
    T* GetResource(std::string name){
        return static_cast<T*>(Get(name));
    }

    template<typename T>
    std::unique_ptr<T> ReleaseResource(std::string name){
        return std::move(std::unique_ptr<T>( static_cast<T*>(Detach(name).release()) ));
    }

    bool Done(){
        return load_functions_queue.empty() && finished_loading;
    }

    using Registry<std::string, Resource>::size;
    using Registry<std::string, Resource>::Clear;

    void WaitUntilDone();
    void WaitUntilDone(const int timeout);
protected:
    virtual void Loop() override;
private:
    bool finished_loading = true;
    std::queue<std::function<void(void)>> load_functions_queue;
};

#endif  // RESOURCE_LOADER_H
