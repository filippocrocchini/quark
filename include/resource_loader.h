/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#ifndef RESOURCE_LOADER_H
#define RESOURCE_LOADER_H

#include <string>
#include <queue>
#include <functional>

#include "looping_thread.h"
#include "resource.h"
#include "registry.h"

class ResourceLoader : public LoopingThread{
public:
    ResourceLoader(LoopController* controller) : LoopingThread(controller) {}

    template<typename T, typename... Args>
    void Load(Registry<std::string, Resource>* resource_reg, const std::string& name, Args&&... args){
        finished_loading = false;

        load_functions_queue.push(std::bind([=](Args... args2){
            std::unique_ptr<T> res = std::unique_ptr<T>{new T{std::forward<Args>(args2)...}};
            if(res->Load()) {
                res->onLoad();
                resource_reg->Register(name, std::move(res));
            } else
                res->onFail();
       }, args...));
    }

    bool Done(){
        return load_functions_queue.empty() && finished_loading;
    }

    void WaitUntilDone();
    void WaitUntilDone(const int timeout);
protected:
    virtual void Loop() override;
private:
    std::queue<std::function<void(void)>> load_functions_queue;
    bool finished_loading = true;
};

#endif  // RESOURCE_LOADER_H
