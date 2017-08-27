/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#ifndef STAGE_H  // NOLINT()
#define STAGE_H

#include <type_traits>
#include <memory>
#include <map>
#include <string>

#include "./window.h"
#include "./looping_thread.h"
#include "./scene.h"
#include "./renderer.h"

class Stage {
 public:
    Stage(LoopController* controller, const std::string& name, unsigned width, unsigned height);
    Stage() = default;

    void Start();
    void Join();

    Scene* CreateScene(const std::string& name);
    void DeleteScene(const std::string& name);
    Scene* GetScene(const std::string& name);

    void SetCurrentScene(const std::string& name);
    void SetTitle(const std::string& title) { name = title; }
    void SetSize(unsigned width, unsigned height) { this->width = width; this->height = height; }

    const std::string& GetName() const { return name; }
    unsigned GetWidth() { return width; }
    unsigned GetHeight() { return height; }

    float GetFPS() { return 1.0/render_thread.GetDelta(); }

    Window* GetWindow() { return &window; }

 private:
    Window window;

    LoopController* controller;
    LoopingThread render_thread;
    LoopingThread update_thread;

    std::map<std::string, std::unique_ptr<Scene>> scenes;
    Renderer renderer;
    Scene* current_scene;

    std::string name;
    unsigned width, height;
};

#endif  // NOLINT() STAGE_H
