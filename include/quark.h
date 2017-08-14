/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#ifndef QUARK_H
#define QUARK_H

#include <string>

#include "looping_thread.h"
#include "resource_loader.h"
#include "registry.h"
#include "stage.h"

class Quark{
public:
    Quark(const std::string& name, unsigned width, unsigned height) : resource_loader(&thread_controller), stage(&thread_controller, name, width, height) {}

    virtual ~Quark(){
        if(thread_controller.isRunning()){
            Stop();
        }
    };

    void Start(){
        if(!threads_started){
            threads_started = true;
            resource_loader.Start();
            stage.Start();
        }
    }

    void Stop(){
        thread_controller.Stop();
        Join();
    }

    void Join(){
        resource_loader.Join();
        stage.Join();
    }

    void WaitForResources(){
        resource_loader.WaitUntilDone();
    }

    template<typename T, typename... Args>
    void LoadResource(const std::string& name, Args&&... args){
        resource_loader.Load<T>(&resource_reg, name, std::forward<Args>(args)...);
    }

    template<typename T>
    T* GetResource(const std::string& name){
        return resource_reg.Get<T>(name);
    }

    Registry<std::string, Resource>* GetResourceRegistry(){ return &resource_reg;}
    ResourceLoader* GetResourceLoader(){ return &resource_loader;}
    Stage* GetStage() { return &stage; }
private:
    Registry<std::string, Resource> resource_reg;
    LoopController thread_controller;
    ResourceLoader resource_loader;
    Stage stage;

    bool threads_started = false;
};

#endif  // QUARK_H
