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
#include "./camera.h"

class Renderer {
 public:
    void SubmitSprite(Sprite* sprite, Transform* transform);
    void RenderBatches(Camera* main_camera);
 private:
    std::map<Material*, SpriteBatch> sprite_batches;
};

#endif  // NOLINT() RENDERER_H
