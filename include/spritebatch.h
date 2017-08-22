/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H

#include <vector>
#include <glm/glm.hpp>

#include "components.h"

class SpriteBatch {
public:
    static const int max_sprites;
    static const int elements_per_sprite;
    static const int sprite_vertices_size;
    static const int sprite_color_size;
    void Create();
    void Delete();

    void AddSprite(const glm::vec4& color, Transform* transform);
    void Flush();

    bool isEmpty() { return sprite_count == 0; }
    unsigned GetSpriteCount() { return sprite_count; }
private:
    unsigned vao, matrix_buffer, color_buffer, sprite_count;
    unsigned element_buffer, vertex_buffer, uv_buffer;
    glm::mat3* matrix_buffer_mapping;
    glm::vec4* color_buffer_mapping;
};

#endif // SPRITEBATCH_H
