/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#ifndef QUARK_H  // NOLINT()
#define QUARK_H

#include <string>
#include <utility>
#include <SOIL2.h>

#include "./looping_thread.h"
#include "./resource_loader.h"
#include "./registry.h"
#include "./stage.h"

namespace Quark {

extern Registry<std::string, Resource> resource_reg;
extern LoopController thread_controller;
extern ResourceLoader resource_loader;
extern Stage stage;
extern bool threads_started;

extern void Setup(const std::string& title, int width, int height);
extern void Start();
extern void Stop();
extern void Join();

extern void WaitForResources();

template<typename T, typename... Args>
void LoadResource(const std::string& name, Args&&... args) {
    resource_loader.Load<T>(&resource_reg, name, std::forward<Args>(args)...);
}

template<typename T>
T* GetResource(const std::string& name) {
    return resource_reg.Get<T>(name);
}

// extern Registry<std::string, Resource>* GetResourceRegistry();
// extern ResourceLoader* GetResourceLoader();
// extern Stage* GetStage();
}  // namespace Quark

#endif  // NOLINT() QUARK_H
