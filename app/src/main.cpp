#include <iostream>

#include "quark.h"

Quark eng{"The best title ever.", 1080, 720};
Stage* stage = eng.GetStage();

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

void setupLoadingScreen(){
    eng.WaitForResources(); //Nothing to fetch
    Scene* loading_screen = stage->CreateScene("loading-screen");

    GameObject* bar_background = loading_screen->CreateGameObject("bar-background");
    GameObject* bar_foreground = loading_screen->CreateGameObject("bar-foreground");

    bar_background->AddComponent<RectangleMesh>(-.5f, -.05f, 1.f, .1f, .2f, .2f, .2f);
    bar_foreground->AddComponent<RectangleMesh>(-.5f, -.05f, 1.f, .1f, .8f, .8f, .8f);

    bar_foreground->AddComponent<LoadingBar>(bar_foreground->GetComponent<RectangleMesh>());
}

void setupMenuScreen(){
    eng.WaitForResources(); //Nothing to fetch
    Scene* loading_screen = stage->CreateScene("menu");
    GameObject* menu_background = loading_screen->CreateGameObject("menu-background");

    menu_background->AddComponent<RectangleMesh>(-.5f, -.5f, 1.f, 1.f, .8f, .8f, .8f);
}

int main(){
    eng.Start();

    setupLoadingScreen();
    setupMenuScreen();

    stage->SetCurrentScene("loading-screen");

    eng.Join();
    return 0;
}
