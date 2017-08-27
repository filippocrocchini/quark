/*
* Copyright (C) 2017 Filippo Crocchini.
*/
#include <quark.h>

#include "./loading_screen.h"
#include "./menu_screen.h"

int main() {
    Quark::Setup("The best title ever geos here.", 1080, 720);
    Quark::Start();
    if (initLoadingScreen()) {
        Quark::stage.SetCurrentScene(LOADING_SCREEN_SCENE);
        loadMenuScreenResources();
        Quark::WaitForResources();
        if (initMenuScreen()) {
            Quark::stage.SetCurrentScene(MENU_SCREEN_SCENE);
        }
    }
    Quark::Join();
    return 0;
}
