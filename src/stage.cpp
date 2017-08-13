/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#include <GL/glew.h>
#include "stage.h"

#include <memory>

Stage::Stage(LoopController* controller) : controller(controller), render_thread(controller), update_thread(controller) {
    Stage* stage = this;

    render_thread.SetOnInitialization([stage](){
        if (!glfwInit()) {
    		std::cerr << "[RenderThread] Failed to initialize GLFW.\n";
    		return 1;
        }

        stage->window.Create();
        stage->window.BindContext();

        if (glewInit() != GLEW_OK) {
		    std::cerr << "[RenderThread] Failed to initialize GLEW.\n";
            return 1;
        }

        glMatrixMode(GL_MODELVIEW);
        glColor3f(1,1,1);

        return 0;
    });
    render_thread.SetOnLoop([stage](){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();//load identity matrix

        if(stage->current_scene)
            stage->current_scene->Render(&(stage->renderer));
        stage->window.SwapBuffers();
    });
    render_thread.SetOnStop([stage]() {
        //NOTE: Case 1: The controller stopped this thread
        //NOTE: Case 2: The Thread wasn't able to initialize either GLEW or GLFW or both, so the engine must shut down.
        stage->controller->Stop(); //FIXME: Should the engine stop here?
    });

    update_thread.SetOnLoop([stage](){
        if(stage->window.status == WINDOW_OK){
            stage->window.PollEvents();
            if(stage->window.ShouldClose())
                stage->controller->Stop();
        }

        if(stage->current_scene)
            stage->current_scene->Update(stage->update_thread.GetDelta());
    });
}

void Stage::Start(){
    render_thread.Start();
    update_thread.Start();
}

void Stage::Join(){
    render_thread.Join();
    update_thread.Join();
}

Scene* Stage::CreateScene(const std::string& name){
    Scene* s = new Scene(name);
    scenes.insert(std::make_pair(name, std::unique_ptr<Scene>(s)));
    return s;
}

void Stage::DeleteScene(const std::string& name){
    scenes.erase(name);
}

Scene* Stage::GetScene(const std::string& name){
    auto s_itr = scenes.find(name);
    if(s_itr == scenes.end()) return nullptr;
    return s_itr->second.get();
}

void Stage::SetCurrentScene(const std::string& name){
    current_scene = GetScene(name);
}
