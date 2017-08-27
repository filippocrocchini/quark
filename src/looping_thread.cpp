/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#include "./looping_thread.h"

#include <chrono>  // NOLINT()

LoopingThread::LoopingThread(LoopController* controller, std::function<void(void)> on_loop) : controller(controller), on_loop(on_loop) {}
LoopingThread::LoopingThread(LoopController* controller) : LoopingThread(controller, nullptr) {}
LoopingThread::LoopingThread() : LoopingThread(nullptr, nullptr) {}

void LoopingThread::Start() {
    worker = std::thread{
        [this]() {
            if (OnInitialize() == 0) {
                auto last = std::chrono::high_resolution_clock::now();
                auto now = std::chrono::high_resolution_clock::now();

                while (this->controller->isRunning()) {
                    now = std::chrono::high_resolution_clock::now();
                    this->delta_time = std::chrono::duration<double>(now - last).count();
                    last = now;
                    this->Loop();
                }
            }
            OnStop();
        }
    };
}

int LoopingThread::OnInitialize() {
    if (this->on_initialize) {
        return this->on_initialize();
    }
    return 0;
}

void LoopingThread::Loop() {
    if (this->on_loop) {
        this->on_loop();
    }
}

void LoopingThread::OnStop() {
    if (this->on_stop) {
        this->on_stop();
    }
}

void LoopingThread::Join() {
    worker.join();
}
