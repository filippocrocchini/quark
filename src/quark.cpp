/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#include "./quark.h"

#include <string>

Registry<std::string, Resource> Quark::resource_reg;
LoopController Quark::thread_controller;
ResourceLoader Quark::resource_loader(&thread_controller);
Stage Quark::stage(&thread_controller, "Quark Engine", 1080, 720);
bool Quark::threads_started = false;

void Quark::Setup(const std::string& title, int width, int height) {
    stage.SetTitle(title);
    stage.SetSize(width, height);
}

void Quark::Start() {
    if (!threads_started) {
        threads_started = true;
        resource_loader.Start();
        stage.Start();
    }
    LoadResource<Shader>("sprite_shader", "assets/shaders/sprite.vs", "assets/shaders/sprite.fs");
    LoadResource<Material>("sprite_material", glm::vec4(1, 1, 1, 1), "", "sprite_shader");
    Quark::WaitForResources();
}

void Quark::Stop() {
    thread_controller.Stop();
    Join();
}

void Quark::Join() {
    resource_loader.Join();
    stage.Join();
}

void Quark::WaitForResources() {
    resource_loader.WaitUntilDone();
}

// Registry<std::string, Resource>* GetResourceRegistry() { return &resource_reg;}
// ResourceLoader* GetResourceLoader() { return &resource_loader;}
// Stage* GetStage() { return &stage; }
