#include "core/resources/texture.h"

#include <GLEW\glew.h>
#include <SOIL2\SOIL2.h>

bool Texture::bind(int texture_unit) {
    if (loading_failed)
        return false;
    if (!loaded)
        loaded = reload();

    glActiveTexture(GL_TEXTURE0 + texture_unit);
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

bool Texture::reload() {
    if (raw_data == nullptr)
        return false;
        
    id = SOIL_create_OGL_texture(raw_data, &width, &height, SOIL_channels, id, SOIL_flags);

    if (id == 0) {
        loading_failed = true;
        return false;
    }

    return true;
}

bool Texture::freeData() {
    if (raw_data == nullptr)
        return false;
    
    SOIL_free_image_data(raw_data);
    raw_data = nullptr;

    return true;
}

std::shared_ptr<Texture> Texture::load(std::string filepath) {
    std::shared_ptr<Texture> texture = std::make_shared<Texture>();

    texture->raw_data = SOIL_load_image(filepath.c_str(), &(texture->width), &(texture->height), &(texture->SOIL_channels), SOIL_LOAD_AUTO);
    
    if (texture->raw_data == nullptr)
        return nullptr;

    return texture;
}
