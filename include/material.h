/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#ifndef MATERIAL_H // NOLINT()
#define MATERIAL_H

#include <glm/glm.hpp>
#include <string>

#include "./shader.h"
#include "./texture.h"
#include "./resource.h"

class Material : public Resource {
 public:
    Material(const glm::vec4& diffuse_color, Texture* texture, Shader* shader);
    Material(const glm::vec4& diffuse_color, const std::string& texture_name, const std::string& shader_name);

    bool Load() override;
    void onLoad() override;
    void onFail() override;

    void SetDiffuseColor(const glm::vec4& color) { this->diffuse_color = color; }
    void SetTexture(Texture* texture) { this->texture = texture; }
    const glm::vec4& GetDiffuseColor() { return diffuse_color; }
    Shader* GetShader() { return shader; }
    Texture* GetTexture() { return texture; }

 private:
    glm::vec4 diffuse_color;
    Shader* shader;
    Texture* texture;

    std::string texture_name;
    std::string shader_name;
};

#endif  // NOLINT() MATERIAL_H
