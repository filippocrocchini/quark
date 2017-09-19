/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#include "./stage.h"

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include <memory>
#include <string>
#include <utility>

Stage::Stage(LoopController* controller, const std::string& name, uint width, uint height) :
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
        return 0;
    });
    render_thread.SetOnLoop([stage]() {
        Scene* scene = stage->current_scene;
        if (scene) {
            if (scene->main_camera) {
                scene->main_camera->SetupContext();
                scene->Render(&(stage->renderer));
                stage->renderer.RenderBatches(scene->main_camera);
            }
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

        if (stage->mouse.released)
            stage->mouse.released = false;
    });

    /*
    ResizeCallback resize_callback = nullptr;
    KeyCallback key_callback = nullptr;
    CharacterCallback character_callback = nullptr;
    CharacterWithModifierCallback character_with_modifier_callback = nullptr;
    CursorPositionCallback cursor_callback = nullptr;
    MouseButtonCallback mouse_button_callback = nullptr;
    ScrollCallback scroll_callback = nullptr;

    typedef void(*CursorPositionCallback)(Window*, double, double);
    typedef void(*MouseButtonCallback)(Window*, int, int, int);
    */

    window.cursor_callback = [stage](Window* window, double x, double y) {
        stage->mouse.x = x;
        stage->mouse.y = y;
    };

    window.mouse_button_callback = [stage](Window* window, int button, int action, int mods) {
        stage->mouse.button = button;
        if (action == GLFW_PRESS) {
            stage->mouse.pressed = true;
            stage->mouse.released = false;
        }
        if (action == GLFW_RELEASE) {
            stage->mouse.pressed = false;
            stage->mouse.released = true;
        }
    };
}

void Stage::Start() {
    render_thread.Start();
    update_thread.Start();
}

void Stage::Join() {
    render_thread.Join();
    update_thread.Join();
}

Scene* Stage::CreateScene(const std::string& name, Camera* main_camera) {
    Scene* s = new Scene(name, main_camera);
    scenes.insert(std::make_pair(name, std::unique_ptr<Scene>(s)));
    return s;
}

Scene* Stage::CreateScene(const std::string& name) {
    return CreateScene(name,  nullptr);
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
