/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#ifndef STAGE_H
#define STAGE_H

#include <type_traits>
#include <memory>

#include "window.h"
#include "looping_thread.h"
#include "scene.h"
#include "renderer.h"

class Stage {
public:
    Stage(LoopController* controller);
    Stage() = default;

    void Start();
    void Join();

    Scene* CreateScene(const std::string& name);
    void DeleteScene(const std::string& name);
    Scene* GetScene(const std::string& name);

    void SetCurrentScene(const std::string& name);
private:
    Window window;

    LoopController* controller;
    LoopingThread render_thread;
    LoopingThread update_thread;

    std::map<std::string, std::unique_ptr<Scene>> scenes;
    Renderer renderer;
    Scene* current_scene;
};

#endif //  STAGE_H
