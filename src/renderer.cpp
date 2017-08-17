/*
* Copyright (C) 2017 Filippo Crocchini.
*/
#include <GL/glew.h>

#include "renderer.h"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

int Renderer::RectangleVao(){
    static unsigned rectangle_vao = 0;
    if(rectangle_vao == 0){
        glGenVertexArrays(1, &rectangle_vao);
        glBindVertexArray(rectangle_vao);

        unsigned vertex_buffer;
        glGenBuffers(1, &vertex_buffer);
        std::vector<float> vertex_data{-.5,-.5,0, .5,-.5,0, .5,.5,0, -.5,.5,0};

        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	    glBufferData(GL_ARRAY_BUFFER, vertex_data.size() * sizeof(float), &vertex_data[0], GL_STATIC_DRAW);
	    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
        glEnableVertexAttribArray(0);

        unsigned element_buffer;
        glGenBuffers(1, &element_buffer);
        std::vector<unsigned short> element_data{0,1,2,0,2,3};

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, element_data.size() * sizeof(unsigned short), &element_data[0], GL_STATIC_DRAW);
    }
    return rectangle_vao;
}

void Renderer::BindMaterial(Material* m){
}

void Renderer::drawSpriteRenderer(SpriteRenderer* sprite_renderer, Transform* transform){
    Shader* s = sprite_renderer->material->GetShader();
    s->Bind();
    s->SetUniform("u_color", sprite_renderer->material->GetDiffuseColor() * sprite_renderer->color);
    //FIXME: This should be part of the Camera class
    s->SetUniform("u_projection", glm::ortho(0.f, (float)window->GetWidth(), 0.f, (float)window->GetHeight(), 0.f, 1000.f));

    s->SetUniform("u_model", transform->GetMatrix());

    glBindVertexArray(Sprite::GetVAO());
    glDrawElements(GL_TRIANGLES, Sprite::GetElementCount(), GL_UNSIGNED_SHORT, 0);
}

void Renderer::drawRectangleMesh(RectangleMesh* mesh){
    mesh->shader->Bind();
    if(mesh->shader->SetUniform("u_color", glm::vec3(mesh->r, mesh->g, mesh->b))){
        glBindVertexArray(RectangleVao());
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
    }
}
