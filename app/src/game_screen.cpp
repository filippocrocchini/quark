/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#include "./game_screen.h"

#include "./player.h"
#include "./level.h"

const char GAME_SCREEN_SCENE[] = "game_screen";

Camera game_camera;

void loadGameResources() {
    loadPlayerResources();
    loadLevelResources();
}

bool initGameScreen(int width, int height) {
    game_camera = Camera {glm::ortho(0.f, static_cast<float>(width), 0.f,
                                            static_cast<float>(height), 0.f, 1000.f),
                            glm::vec3(.1f, .1f, .2f)};
    Scene* game_screen = Quark::stage.CreateScene(GAME_SCREEN_SCENE, &game_camera);
    initLevel(game_screen);
    initPlayer(game_screen);
    return true;
}
