/*
* Copyright (C) 2017 Filippo Crocchini.
*/
#include <quark.h>

#include "./loading_screen.h"

int main() {
    Quark::Setup("The best title ever geos here.", 1080, 720);
    Quark::Start();
    initLoadingScreen();
    Quark::stage.SetCurrentScene(LOADING_SCREEN_SCENE);
    Quark::Join();
    return 0;
}
