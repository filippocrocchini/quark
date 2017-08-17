/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#include "sprite.h"

#include <GL/glew.h>
#include <vector>

unsigned Sprite::vao, Sprite::vertex_buffer, Sprite::element_buffer;
int Sprite::elements;

unsigned Sprite::GetVAO(){
    if(vao == 0){
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &vertex_buffer);
        std::vector<float> vertex_data{0,0,0, 1,0,0, 1,1,0, 0,1,0};

        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	    glBufferData(GL_ARRAY_BUFFER, vertex_data.size() * sizeof(float), &vertex_data[0], GL_STATIC_DRAW);
	    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
        glEnableVertexAttribArray(0);

        glGenBuffers(1, &element_buffer);
        std::vector<unsigned short> element_data{0,1,2,0,2,3};

        elements = element_data.size();

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements * sizeof(unsigned short), &element_data[0], GL_STATIC_DRAW);
    }
    return vao;
}

int Sprite::GetElementCount(){
    return elements;
}
