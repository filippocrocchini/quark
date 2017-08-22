/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#include "quark.h"

#include "loading_bar.h"


#include <chrono>
#include <thread>

class Dummy : public Resource {
public:
    Dummy(){
    }

    virtual bool Load() override {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return true;
    }

    virtual void onLoad() override {}

    virtual void onFail() override {}
};


const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;
const int PRELOADED_RESOURCE_COUNT = 10;

Quark eng{"The best title ever.", SCREEN_WIDTH, SCREEN_HEIGHT};
Stage* stage = eng.GetStage();

void loadStartupResources() {
    eng.LoadResource<Shader>("sprite_shader", "assets/shaders/sprite.vs","assets/shaders/sprite.fs");
}

void preloadResources() {
    for(int i=0;i<10;i++){
        eng.LoadResource<Dummy>(std::string("dummy") + std::to_string(i));
    }    
}

void setupLoadingScreen(Material* sprite_material){
    Scene* loading_screen = stage->CreateScene("loading_screen");

    loading_screen->CreateGameObject("bar_foreground")->
        AddComponent<Transform>(glm::vec3(SCREEN_WIDTH/2-300, SCREEN_HEIGHT/2-10, 0), glm::vec3(600,20,1), glm::quat())->
        AddComponent<Sprite>(sprite_material, glm::vec4(1,1,1,1))->
        AddComponent<LoadingBar>(eng.GetResourceLoader(), PRELOADED_RESOURCE_COUNT);

    loading_screen->CreateGameObject("bar_background")->
        AddComponent<Transform>(glm::vec3(SCREEN_WIDTH/2-300, SCREEN_HEIGHT/2-10, 0), glm::vec3(600,20,1), glm::quat())->
        AddComponent<Sprite>(sprite_material, glm::vec4(0,0,0,.3f));

}



int main(){
    eng.Start();

    loadStartupResources();
    eng.WaitForResources();

    //TODO: Materials should be resources
    Material sprite_material{glm::vec4(1,1,1,1), nullptr, eng.GetResource<Shader>("sprite_shader")};

    setupLoadingScreen(&sprite_material);
    stage->SetCurrentScene("loading_screen");
    preloadResources();

    eng.Join();
    return 0;
}
