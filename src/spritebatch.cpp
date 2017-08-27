/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#include "./spritebatch.h"

#include <GL/glew.h>
#include <glm/gtx/component_wise.hpp>
#include <iostream>
#include <vector>

const int SpriteBatch::max_sprites = 10000;
const int SpriteBatch::elements_per_sprite = 4;
const int SpriteBatch::sprite_vertices_size = elements_per_sprite * 2 * sizeof(float);
const int SpriteBatch::sprite_color_size = 4 * sizeof(float);

void SpriteBatch::Create() {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    std::vector<float> sprite_vertices{0, 0, 1, 0, 1, 1, 0, 1};
    glBufferData(GL_ARRAY_BUFFER, sprite_vertices.size() * 2 * sizeof(float), &sprite_vertices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, 0);
    glGenBuffers(1, &matrix_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, matrix_buffer);
    glBufferData(GL_ARRAY_BUFFER, max_sprites *  sizeof(glm::mat3), nullptr, GL_STREAM_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(glm::mat3), (const void*)  0);
    glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(glm::mat3), (const void*) (3 * 4));
    glVertexAttribPointer(3, 3, GL_FLOAT, false, sizeof(glm::mat3), (const void*) (6 * 4));
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    glVertexAttribDivisor(1, 1);
    glVertexAttribDivisor(2, 1);
    glVertexAttribDivisor(3, 1);
    glGenBuffers(1, &color_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
    glBufferData(GL_ARRAY_BUFFER, max_sprites *  sizeof(glm::vec4), nullptr, GL_STREAM_DRAW);
    glVertexAttribPointer(4, 4, GL_FLOAT, false, sizeof(glm::vec4), 0);
    glEnableVertexAttribArray(4);
    glVertexAttribDivisor(4, 1);
    glGenBuffers(1, &uv_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
    std::vector<float> sprite_uv{0, 0, 1, 0, 1, 1, 0, 1};
    glBufferData(GL_ARRAY_BUFFER, sprite_uv.size() * 2 * sizeof(float), &sprite_uv[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 2, GL_FLOAT, false, 0, 0);
    glGenBuffers(1, &element_buffer);
    std::vector<uint16_t> element_data{0, 1, 2, 3};
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, element_data.size() * sizeof(uint16_t), &element_data[0], GL_STATIC_DRAW);
}

void SpriteBatch::Delete() {
    // TODO(filippocrocchini): Implement
}

void SpriteBatch::AddSprite(const glm::vec4& color, Transform* transform) {
    if (sprite_count >= max_sprites)
        return;
    if (vao == 0)
        Create();
    if (sprite_count == 0) {
        glBindBuffer(GL_ARRAY_BUFFER, matrix_buffer);
        matrix_buffer_mapping = (glm::mat3*) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
        glUnmapBuffer(GL_ARRAY_BUFFER);
        glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
        color_buffer_mapping = (glm::vec4*) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
        glUnmapBuffer(GL_ARRAY_BUFFER);
    }
    if (!matrix_buffer_mapping || !color_buffer_mapping)
        return;
    matrix_buffer_mapping[sprite_count] = transform->GetMatrix2D();

    glm::mat3 mat = transform->GetMatrix2D();
    color_buffer_mapping[sprite_count] = color;
    sprite_count++;
}

void SpriteBatch::Flush() {
    glBindVertexArray(vao);
    glDrawElementsInstanced(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_SHORT, 0, sprite_count);
    sprite_count = 0;
}
