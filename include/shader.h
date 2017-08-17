/*
 * Copyright (C) 2017 Filippo Crocchini.
 */

#ifndef SHADER_H
#define SHADER_H

#include <glm/glm.hpp>
#include <string>
#include <map>

class Shader {
public:
    //IDEA: custom shader file so that you can do something like:
    //      Shader(const std::string& shader_path)

    Shader(const std::string& vertex_code, const std::string& fragment_code, const std::string& geometry_code);
    Shader(const std::string& vertex_code, const std::string& fragment_code) : Shader(vertex_code, fragment_code, "") {}

    bool SetUniform(const std::string& name, int value);
    bool SetUniform(const std::string& name, float value);
    bool SetUniform(const std::string& name, const glm::vec2& value);
    bool SetUniform(const std::string& name, const glm::vec3& value);
    bool SetUniform(const std::string& name, const glm::vec4& value);
    bool SetUniform(const std::string& name, const glm::mat2& value);
    bool SetUniform(const std::string& name, const glm::mat3& value);
    bool SetUniform(const std::string& name, const glm::mat4& value);

    void Bind();

    bool isBound() { return gl_handle == current_shader;}
private:
    static unsigned current_shader;

    std::map<std::string, unsigned> uniform_locations;
    std::string vertex_code, fragment_code, geometry_code;
    std::string vertex_log, fragment_log, geometry_log, link_log;
    unsigned gl_handle, vertex_handle, fragment_handle, geometry_handle;
    bool is_built = false;
    bool build_failed = false;

    bool Build();

    bool Compile();
    bool Link();
    bool Validate();

    int FindUniformLocation(const std::string& name);

};

#endif  // SHADER_H
