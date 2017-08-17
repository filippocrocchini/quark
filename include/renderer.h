/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#ifndef RENDERER_H
#define RENDERER_H

#include "window.h"
#include "components.h"
#include "material.h"

class Renderer {
public:
    Renderer(Window* window) : window(window) {}

    void drawRectangleMesh(RectangleMesh* rectangleMesh);
    void drawSpriteRenderer(SpriteRenderer* sprite_renderer, Transform* transform);

    void BindMaterial(Material* m);
private:
    static int RectangleVao();

    Window* window; //FIXME: Not too sure about this
};

#endif //  RENDERER_H
