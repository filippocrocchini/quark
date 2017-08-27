/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#ifndef RENDERER_H // NOLINT()
#define RENDERER_H

#include <glm/glm.hpp>

#include <map>

#include "./components.h"
#include "./material.h"
#include "./spritebatch.h"

class Renderer {
 public:
    explicit Renderer(const glm::mat4& projection_matrix) : projection_matrix(projection_matrix) {}
    Renderer() : Renderer(glm::mat4(1)) {}

    void SubmitSprite(Sprite* sprite, Transform* transform);
    void SetProjection(const glm::mat4& projection_matrix) { this->projection_matrix = projection_matrix; }

    void RenderBatches();
 private:
    std::map<Material*, SpriteBatch> sprite_batches;
    glm::mat4 projection_matrix;
};

#endif  // NOLINT() RENDERER_H
