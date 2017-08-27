/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#ifndef TEXTURE_H  // NOLINT()
#define TEXTURE_H

#include <array>
#include <string>
#include <iostream>

#include "./resource.h"

class Texture : public Resource{
 public:
    Texture(const std::string& filepath, unsigned soil_flags) : filepath(filepath), soil_flags(soil_flags) {}
    virtual ~Texture();

    bool Load() override;
    void onLoad() override{
        std::cout<< "Loaded texture " << filepath << "." << std::endl;
    };
    void onFail() override{
        std::cerr<< "Failed loading texture " << filepath << "." << std::endl;
    };

    void Bind(int texture_unit);
    void Unbind();

    void Create();
    void Delete();

    unsigned GetID() { return id; }

 private:
    unsigned char* raw_data;
    std::string filepath;
    int height;
    int width;
    unsigned id, soil_flags;
    int soil_channels;
    bool created = false;
};

#endif  // NOLINT() TEXTURE_H
