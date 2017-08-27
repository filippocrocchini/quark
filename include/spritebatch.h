/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#ifndef SPRITEBATCH_H  // NOLINT()
#define SPRITEBATCH_H

#include <glm/glm.hpp>

#include <vector>

#include "./components.h"

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
    uint GetSpriteCount() { return sprite_count; }

 private:
    uint vao, matrix_buffer, color_buffer, sprite_count;
    uint element_buffer, vertex_buffer, uv_buffer;
    glm::mat3* matrix_buffer_mapping;
    glm::vec4* color_buffer_mapping;
};

#endif // NOLINT() SPRITEBATCH_H
