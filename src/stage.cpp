/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#include "./stage.h"

#include <glm/gtc/matrix_transform.hpp>

#include <memory>
#include <string>
#include <utility>

Stage::Stage(LoopController* controller, const std::string& name, unsigned width, unsigned height) :
     controller(controller), render_thread(controller), update_thread(controller) {
    this->name = name;
    this->width = width;
    this->height = height;

    Stage* stage = this;

    render_thread.SetOnInitialization([stage]() {
        if (!glfwInit()) {
            std::cerr << "[RenderThread] Failed to initialize GLFW.\n";
            return 1;
        }

        WindowConfiguration config;

        config.title = stage->GetName();
        config.width = stage->GetWidth();
        config.height = stage->GetHeight();
        config.opengl_profile = GLFW_OPENGL_ANY_PROFILE;
        config.opengl_major = 4;
        config.opengl_minor = 0;
        config.antialiasing = 16;
        config.vsync = false;

        stage->window.SetConfiguration(config);

        stage->window.Create();
        stage->window.BindContext();

        if (glewInit() != GLEW_OK) {
            std::cerr << "[RenderThread] Failed to initialize GLEW.\n";
            return 1;
        }

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glClearColor(0, 105/255.f, 249/255.f, 1);
        stage->renderer.SetProjection(glm::ortho(0.f,
                                                 static_cast<float>(stage->window.GetWidth()),
                                                 0.f,
                                                 static_cast<float>(stage->window.GetHeight()),
                                                 0.f,
                                                 1000.f));
        return 0;
    });
    render_thread.SetOnLoop([stage]() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        if (stage->current_scene) {
            stage->current_scene->Render(&(stage->renderer));
            stage->renderer.RenderBatches();
        }
        stage->window.SwapBuffers();
    });
    render_thread.SetOnStop([stage]() {
        // NOTE(filippocrocchini): Case 1: The controller stopped this thread
        // NOTE(filippocrocchini): Case 2: The Thread wasn't able to initialize either GLEW or GLFW or both, so the engine must shut down.
        stage->controller->Stop();  // FIXME(filippocrocchini): Should the engine stop here?
    });

    update_thread.SetOnLoop([stage]() {
        if (stage->window.status == WINDOW_OK) {
            stage->window.PollEvents();
            if (stage->window.ShouldClose())
                stage->controller->Stop();
        }

        if (stage->current_scene)
            stage->current_scene->Update(stage->update_thread.GetDelta());
    });
}

void Stage::Start() {
    render_thread.Start();
    update_thread.Start();
}

void Stage::Join() {
    render_thread.Join();
    update_thread.Join();
}

Scene* Stage::CreateScene(const std::string& name) {
    Scene* s = new Scene(name);
    scenes.insert(std::make_pair(name, std::unique_ptr<Scene>(s)));
    return s;
}

void Stage::DeleteScene(const std::string& name) {
    scenes.erase(name);
}

Scene* Stage::GetScene(const std::string& name) {
    auto s_itr = scenes.find(name);
    if (s_itr == scenes.end()) return nullptr;
    return s_itr->second.get();
}

void Stage::SetCurrentScene(const std::string& name) {
    current_scene = GetScene(name);
    if (current_scene == nullptr)
        std::cout << "[Stage][Warning] The current scene has been set to nullptr, ignore if this behaviour is expected.\n";
}
