/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#ifndef GAME_SCREEN_H  //NOLINT()
#define GAME_SCREEN_H

#include <quark.h>

extern const char GAME_SCREEN_SCENE[];
extern Camera game_camera;

void loadGameResources();
bool initGameScreen(int width, int height);

#endif  //NOLINT() GAME_SCREEN_H
