/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#include <GL/glew.h>

#include "texture.h"

#include <SOIL2.h>

Texture::~Texture(){
    if(raw_data)
        SOIL_free_image_data(raw_data);
    //if(id != 0)
    //    Delete();
}

bool Texture::Load(){
    raw_data = SOIL_load_image(filepath.c_str(), &width, &height, &soil_channels, SOIL_LOAD_AUTO);
    return raw_data!=nullptr;
}

void Texture::Create(){
    if (raw_data == nullptr)
        return;
    id = SOIL_create_OGL_texture(raw_data, &width, &height, soil_channels, id, soil_flags);
    SOIL_free_image_data(raw_data);
    raw_data = nullptr;
    created = true;
}

void Texture::Bind(int texture_unit){
    if(!created)
        Create();
    glActiveTexture(GL_TEXTURE0 + texture_unit);
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::Unbind(){
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete(){
    glDeleteTextures(1, &id);
}
