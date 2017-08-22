/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#include <GL/glew.h>

#include "renderer.h"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

void Renderer::SubmitSprite(Sprite* sprite, Transform* transform){
    sprite_batches[sprite->material].AddSprite(sprite->color, transform);
}

void Renderer::RenderBatches(){
    for(auto batch_pair = sprite_batches.begin(); batch_pair != sprite_batches.end(); batch_pair++){
        if(!batch_pair->second.isEmpty()){
            Shader* s = batch_pair->first->GetShader();
            Texture* texture = batch_pair->first->GetTexture();
            s->Bind();
            s->SetUniform("u_projection", projection_matrix);
            s->SetUniform("u_color", batch_pair->first->GetDiffuseColor());
            if(texture){
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
void Renderer::drawSpriteRenderer(Sprite* sprite, Transform* transform){
    Shader* s = sprite->material->GetShader();
    s->Bind();
    s->SetUniform("u_color", sprite->material->GetDiffuseColor() * sprite->color);
    //FIXME: This should be part of the Camera class
    s->SetUniform("u_projection", projection_matrix);

    s->SetUniform("u_model", transform->GetMatrix());

    glBindVertexArray(Sprite::GetVAO());
    glDrawElements(GL_TRIANGLES, Sprite::GetElementCount(), GL_UNSIGNED_SHORT, 0);
}*/
