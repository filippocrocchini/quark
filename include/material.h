/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>

#include "shader.h"

class Material {
public:
    Material(const glm::vec3& diffuse_color, Shader* shader) : diffuse_color(diffuse_color), shader(shader) {}
    const glm::vec3& GetDiffuseColor() { return diffuse_color; }
    void SetDiffuseColor(const glm::vec3& color) { this->diffuse_color = color; }
    Shader* GetShader() { return shader; }
private:
    glm::vec3 diffuse_color;
    Shader* shader;
    //Texture* texture;
};

#endif  // MATERIAL_H
