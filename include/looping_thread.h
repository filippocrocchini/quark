/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#ifndef LOOPING_THREAD_H
#define LOOPING_THREAD_H

#include <thread>
#include <mutex>
#include <atomic>

class LoopController{
public:
    LoopController(){
        running.store(true);
    }
    bool isRunning(){
        return running.load();
    }
    virtual void Stop(){
        running.store(false);
    }
private:
    std::atomic<bool> running;
};

class LoopingThread {
public:
    LoopingThread(LoopController* controller) : controller(controller) {}
    void Start();
    void Join();
protected:
    virtual void Loop() = 0;
private:
    LoopController* controller;
    std::thread worker;
};

#endif  // LOOPING_THREAD_H
