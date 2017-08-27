/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#include "./renderer.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>

#include "./quark.h"

void Renderer::SubmitSprite(Sprite* sprite, Transform* transform) {
    Material* material = sprite->material;
    if (material == nullptr) {
        material = Quark::GetResource<Material>("sprite_material");
    }
    if (material == nullptr) {
        return;
    }
    sprite_batches[material].AddSprite(sprite->color, transform);
}

void Renderer::RenderBatches(Camera* main_camera) {
    if (main_camera == nullptr)
        return;
    for (auto batch_pair = sprite_batches.begin(); batch_pair != sprite_batches.end(); batch_pair++) {
        if (!batch_pair->second.isEmpty()) {
            Shader* s = batch_pair->first->GetShader();
            Texture* texture = batch_pair->first->GetTexture();
            s->Bind();
            s->SetUniform("u_projection", main_camera->GetProjectionMatrix());
            s->SetUniform("u_color", batch_pair->first->GetDiffuseColor());
            if (texture != nullptr) {
                texture->Bind(0);
                s->SetUniform("u_texture", 0);
                s->SetUniform("u_has_texture", 1);
                batch_pair->second.Flush();
                texture->Unbind();
            } else {
                s->SetUniform("u_has_texture", 0);
                batch_pair->second.Flush();
            }
        }
    }
}

/*
void Renderer::drawSpriteRenderer(Sprite* sprite, Transform* transform) {
    Shader* s = sprite->material->GetShader();
    s->Bind();
    s->SetUniform("u_color", sprite->material->GetDiffuseColor() * sprite->color);
    //FIXME(filippocrocchini): This should be part of the Camera class
    s->SetUniform("u_projection", projection_matrix);

    s->SetUniform("u_model", transform->GetMatrix());

    glBindVertexArray(Sprite::GetVAO());
    glDrawElements(GL_TRIANGLES, Sprite::GetElementCount(), GL_UNSIGNED_SHORT, 0);
}*/
