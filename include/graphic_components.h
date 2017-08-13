/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#ifndef GRAPHIC_COMPONENTS_H
#define GRAPHIC_COMPONENTS_H

#include "component.h"
#include <iostream>

class RectangleMesh : public Component {
public:
    float x, y, width, height;
    float r, g, b;

    RectangleMesh(float x, float y, float width, float height, float r, float g, float b) : x(x), y(y), width(width), height(height), r(r), g(g), b(b){}
    virtual ~RectangleMesh() = default;
};

#endif //  GRAPHIC_COMPONENTS_H
