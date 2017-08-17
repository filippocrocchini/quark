/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#ifndef SPRITE_H
#define SPRITE_H

class Sprite {
public:
    static unsigned GetVAO();
    static int GetElementCount();
private:
    static unsigned vao, vertex_buffer, element_buffer;
    static int elements;
};

#endif //  SPRITE_H
