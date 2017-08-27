/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#ifndef MENU_SCREEN_H  //NOLINT()
#define MENU_SCREEN_H

#include <quark.h>

extern const char MENU_SCREEN_SCENE[];

extern Camera menu_screen_camera;

extern void loadMenuScreenResources();
extern bool initMenuScreen(int width, int height);

#endif  //NOLINT() MENU_SCREEN_H
