#include <iostream>

#include "quark.h"
#include <cstdlib>

int randInt(int range){
    return std::rand()/(float)RAND_MAX*range;
}

float randFloat(float range){
    return std::rand()/(float)RAND_MAX*range;
}


Quark eng{"The best title ever.", 1080, 720};
Stage* stage = eng.GetStage();

Shader flat_shader{
    R"(#version 400 core

     layout (location = 0) in vec3 v_pos;

     uniform mat4 u_projection = mat4(1);
     uniform mat4 u_model = mat4(1);

     void main(){
         gl_Position = u_projection * u_model * vec4(v_pos,1);
     })",
    R"(#version 400 core

     out vec4 color;

     uniform vec3 u_color = vec3(1,0,1);

     void main(){
         color = vec4(u_color,1);
     })"
};

Material sprite_material{glm::vec3(1,1,1), &flat_shader};

class LoadingBar : public Behaviour {
public:
    LoadingBar(RectangleMesh* mesh) : mesh(mesh) {
        max_width = mesh->width;
        mesh->width = 0;
    }

    virtual void Update(double delta) override {
        mesh->width += delta/2.f;
        if(mesh->width > max_width){
            mesh->width -= max_width;
            stage->SetCurrentScene("menu");
        }
    }

    virtual void LateUpdate(double delta) override {}
private:
    RectangleMesh* mesh;
    double max_width, fill_perc=0;
};

class Rotating : public Behaviour {
public:
    Rotating(double speed) : speed(speed) {}

    virtual void Update(double delta) override {
        if(t == nullptr){
            t = parent->GetComponent<Transform>();
            return;
        }

        z_angle += delta * speed;
        t->SetRotation(glm::quat(glm::vec3(0,0,z_angle)));
    }

    virtual void LateUpdate(double delta) override {}
private:
    double z_angle, speed;
    Transform* t = nullptr;
};

void setupLoadingScreen(){
    eng.WaitForResources(); //Nothing to fetch
    Scene* loading_screen = stage->CreateScene("loading-screen");

    GameObject* bar_background = loading_screen->CreateGameObject("bar-background");
    GameObject* bar_foreground = loading_screen->CreateGameObject("bar-foreground");

    bar_background->AddComponent<RectangleMesh>(-.5f, -.05f, 1.f, .1f, .2f, .2f, .2f, &flat_shader);
    bar_foreground->AddComponent<RectangleMesh>(-.5f, -.05f, 1.f, .1f, .8f, .8f, .8f, &flat_shader);

    bar_foreground->AddComponent<LoadingBar>(bar_foreground->GetComponent<RectangleMesh>());
}

void setupMenuScreen(){
    eng.WaitForResources(); //Nothing to fetch
    Scene* loading_screen = stage->CreateScene("menu");
    for(int i=0;i<200;++i){
        GameObject* spinner = loading_screen->CreateGameObject(std::string("spinner") + std::to_string(i));

        spinner->AddComponent<Transform>(glm::vec3(randInt(1080),randInt(720),0),
         glm::vec3(20,200,1), glm::quat(glm::vec3(0,0,0)), glm::vec3(-10,-100,0));
        spinner->AddComponent<SpriteRenderer>(nullptr, &sprite_material, glm::vec3(randFloat(1),randFloat(1),randFloat(1)));
        spinner->AddComponent<Rotating>(randFloat(20)-10.0);
    }

}

int main(){
    std::srand(std::time(0));

    eng.Start();

    setupLoadingScreen();
    setupMenuScreen();

    stage->SetCurrentScene("loading-screen");

    eng.Join();
    return 0;
}
