/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#include "./loading_screen.h"

#include "./loading_bar.h"


const char LOADING_SCREEN_SCENE[] = "loading_screen";

void initLoadingScreen() {
    Scene* loading_screen = Quark::stage.CreateScene(LOADING_SCREEN_SCENE);
    loading_screen->CreateGameObject("bar_foreground")->
        AddComponent<Transform>(glm::vec3(Quark::stage.GetWidth()/2-300, Quark::stage.GetHeight()/2-10, 0), glm::vec3(600, 20, 1), glm::quat())->
        AddComponent<Sprite>(glm::vec4(1, 1, 1, 1))->
        AddComponent<LoadingBar>();
    loading_screen->CreateGameObject("bar_background")->
        AddComponent<Transform>(glm::vec3(Quark::stage.GetWidth()/2-300, Quark::stage.GetHeight()/2-10, 0), glm::vec3(600, 20, 1), glm::quat())->
        AddComponent<Sprite>(glm::vec4(0, 0, 0, .3f));
}
