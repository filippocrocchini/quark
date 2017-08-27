/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#ifndef LOOPING_THREAD_H  // NOLINT()
#define LOOPING_THREAD_H

#include <functional>
#include <atomic>
#include <thread>  // NOLINT()
#include <mutex>  // NOLINT()

class LoopController{
 public:
    LoopController() {
        running.store(true);
    }
    virtual ~LoopController() = default;

    bool isRunning() {
        return running.load();
    }
    virtual void Stop() {
        running.store(false);
    }
 private:
    std::atomic<bool> running;
};

class LoopingThread {
 public:
    LoopingThread(LoopController* controller, std::function<void(void)> loop);
    explicit LoopingThread(LoopController* controller);
    LoopingThread();

    virtual ~LoopingThread() = default;

    void Start();
    void Join();

    void SetOnInitialization(std::function<int(void)> on_initialize) {this->on_initialize = on_initialize;}
    void SetOnLoop(std::function<void(void)> on_loop) {this->on_loop = on_loop;}
    void SetOnStop(std::function<void(void)> on_stop) {this->on_stop = on_stop;}

    double GetDelta() { return delta_time; }

 protected:
    virtual int OnInitialize();
    virtual void Loop();
    virtual void OnStop();

 private:
    LoopController* controller;
    std::function<int(void)> on_initialize;
    std::function<void(void)> on_loop, on_stop;

    double delta_time;

    std::thread worker;
};

#endif  // NOLINT() LOOPING_THREAD_H
