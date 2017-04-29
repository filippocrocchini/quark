#pragma once
#include <GLEW\glew.h>

#include <memory>
#include <string>

class Texture{
public:
    Texture() = default;
    ~Texture() {
        freeData();
    }

    const GLuint& getID() const { return id; }
    
    // \return true if successfully loaded and bound to opengl
    bool bind(int texture_unit);
    void unbind();
    
    bool reload();
    bool freeData();
    
    void setSOIL_flags(unsigned flags) {
        SOIL_flags = flags;
    }

    static std::shared_ptr<Texture> load(std::string filepath);
private:
    GLuint id;
    int width;
    int height;
    int SOIL_channels;
    unsigned SOIL_flags;

    unsigned char* raw_data;

    bool loaded;
    bool loading_failed;

};