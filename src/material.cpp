/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#include "./material.h"

#include <string>

#include "./quark.h"

Material::Material(const glm::vec4& diffuse_color, Texture* texture, Shader* shader): diffuse_color(diffuse_color), shader(shader), texture(texture) {}

Material::Material(const glm::vec4& diffuse_color, const std::string& texture_name, const std::string& shader_name):
     diffuse_color(diffuse_color), texture_name(texture_name), shader_name(shader_name) {
    shader = nullptr;
    texture = nullptr;
}

bool Material::Load() {
    shader = Quark::GetResource<Shader>(shader_name);
    if (shader == nullptr) return false;
    texture = Quark::GetResource<Texture>(texture_name);
    return true;
}

void Material::onLoad() {}

void Material::onFail() {}
