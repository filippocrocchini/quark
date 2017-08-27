/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#ifndef RESOURCE_LOADER_H  // NOLINT()
#define RESOURCE_LOADER_H

#include <string>
#include <queue>
#include <functional>
#include <utility>
#include <memory>

#include "./looping_thread.h"
#include "./resource.h"
#include "./registry.h"

class ResourceLoader : public LoopingThread{
 public:
    explicit ResourceLoader(LoopController* controller);

    template<typename T, typename... Args>
    void Load(Registry<std::string, Resource>* resource_reg, const std::string& name, Args&&... args) {
        finished_loading = false;
        resource_count++;
        load_functions_queue.push([=]() {
            std::unique_ptr<T> res = std::unique_ptr<T>{new T{args...}};
            if (res->Load()) {
                res->onLoad();
                resource_reg->Register(name, std::move(res));
            } else {
                res->onFail();
            }
       });
    }

    int GetResourceCount() { return resource_count; }
    void ResetCount() { resource_count = 0; }
    bool Done() {
        return load_functions_queue.empty() && finished_loading;
    }

    int GetQueueSize() { return load_functions_queue.size(); }

    void WaitUntilDone();
    void WaitUntilDone(const int timeout);

 protected:
    void Loop() override;

 private:
    std::queue<std::function<void(void)>> load_functions_queue;
    bool finished_loading = true;
    int resource_count;
};

#endif  // NOLINT() RESOURCE_LOADER_H
