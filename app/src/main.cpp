/*
* Copyright (C) 2017 Filippo Crocchini.
*/
#include <quark.h>

#include "./loading_screen.h"
#include "./menu_screen.h"

const int WIDTH = 1080, HEIGHT = 720;
int main() {
    Quark::Setup("The best title ever goes here.", WIDTH, HEIGHT);
    Quark::Start();
    if (initLoadingScreen(WIDTH, HEIGHT)) {
        Quark::stage.SetCurrentScene(LOADING_SCREEN_SCENE);
        loadMenuScreenResources();
        // loadGameResources();
        Quark::WaitForResources();
        if (initMenuScreen(WIDTH, HEIGHT)) {
            Quark::stage.SetCurrentScene(MENU_SCREEN_SCENE);
        }
    }
    Quark::Join();
    return 0;
}
