/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>

#include "shader.h"
#include "texture.h"

class Material {
public:
    Material(const glm::vec4& diffuse_color, Texture* texture, Shader* shader) : diffuse_color(diffuse_color), shader(shader), texture(texture) {}

    void SetDiffuseColor(const glm::vec4& color) { this->diffuse_color = color; }
    void SetTexture(Texture* texture) { this->texture = texture; }

    const glm::vec4& GetDiffuseColor() { return diffuse_color; }
    Shader* GetShader() { return shader; }
    Texture* GetTexture() { return texture; }
private:
    glm::vec4 diffuse_color;
    Shader* shader;
    Texture* texture;
};

#endif  // MATERIAL_H
