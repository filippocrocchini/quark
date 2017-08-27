/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#include "./resource_loader.h"

#include <thread>  // NOLINT()
#include <chrono>  // NOLINT()
#include <iostream>

ResourceLoader::ResourceLoader(LoopController* controller) : LoopingThread(controller) {}

void ResourceLoader::Loop() {
    if (!load_functions_queue.empty()) {
        auto func = load_functions_queue.front();
        load_functions_queue.pop();
        func();
    } else {
        finished_loading = true;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void ResourceLoader::WaitUntilDone() {
    while (!Done()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    resource_count = 0;
}

void ResourceLoader::WaitUntilDone(const int timeout) {
    auto start = std::chrono::steady_clock::now();
    auto now = std::chrono::steady_clock::now();

    while (!Done()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        now = std::chrono::steady_clock::now();

        if (std::chrono::duration_cast<std::chrono::milliseconds>(now-start).count() >= timeout) break;
    }
    resource_count = 0;
}
