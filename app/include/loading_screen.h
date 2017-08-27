/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#ifndef LOADING_SCREEN_H  //NOLINT()
#define LOADING_SCREEN_H

#include <quark.h>

extern const char LOADING_SCREEN_SCENE[];
extern Camera loading_screen_camera;

extern bool initLoadingScreen(int width, int height);

#endif  //NOLINT() LOADING_SCREEN_H
