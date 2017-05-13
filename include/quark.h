/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#ifndef QUARK_H
#define QUARK_H

#include <string>

#include "looping_thread.h"

#include "resource_loader.h"
#include "registry.h"

class Quark{
public:
    Quark(){};
    virtual ~Quark(){
        if(thread_controller.isRunning()){
            Stop();
        }
    };

    void Start(){
        if(!threads_started){
            threads_started = true;
            resource_loader.Start();
        }
    }

    void Stop(){
        thread_controller.Stop();
        resource_loader.Join();
    }

    template<typename T, typename... Args>
    void LoadResource(const std::string& name, Args&&... args){
        resource_loader.Load<T>(&resource_reg, name, std::forward<Args>(args)...);
    }

    template<typename T>
    T* GetResource(const std::string& name){
        return resource_reg.Get<T>(name);
    }

    Registry<std::string, Resource>* resourceRegistry(){ return &resource_reg;}
    ResourceLoader* resourceLoader(){ return &resource_loader;}
private:
    Registry<std::string, Resource> resource_reg;
    LoopController thread_controller;
    ResourceLoader resource_loader{&thread_controller};
    bool threads_started = false;
};

#endif  // QUARK_H
