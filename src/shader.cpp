/*
 * Copyright (C) 2017 Filippo Crocchini.
 */

#include "shader.h"

#include <GL/glew.h>
#include <iostream>

unsigned Shader::current_shader = 0;

bool compileShader(GLuint type, GLuint& handle, const std::string& source, std::string& compile_log);

Shader::Shader(const std::string& vertex_code, const std::string& fragment_code, const std::string& geometry_code):
    vertex_code(vertex_code), fragment_code(fragment_code), geometry_code(geometry_code) {}

void Shader::Bind(){
    if(!is_built && !build_failed){
        build_failed = !Build();
        is_built = true;
    }
    if(!isBound())
        glUseProgram(gl_handle);
}

bool Shader::Build(){
    return Compile() && Link() && Validate();
}

bool Shader::Compile(){
    if (compileShader(  GL_VERTEX_SHADER,   vertex_handle,   vertex_code,   vertex_log) &&
        compileShader(GL_FRAGMENT_SHADER, fragment_handle, fragment_code, fragment_log)){
            if(!geometry_code.empty()){
                return compileShader(GL_GEOMETRY_SHADER, geometry_handle, geometry_code, geometry_log);
            }
            return true;
        }
    return false;
}

bool Shader::Link(){
    gl_handle = glCreateProgram();
    if (gl_handle == 0) {
        std::cerr << "Could not create the shader program. Probably the context in not valid." << std::endl;
        return false;
    }

    glAttachShader(gl_handle, vertex_handle);
    glAttachShader(gl_handle, fragment_handle);
    if(geometry_handle != 0)
        glAttachShader(gl_handle, geometry_handle);

    glLinkProgram(gl_handle);

    GLint link_status = 0;
    glGetProgramiv(gl_handle, GL_LINK_STATUS, &link_status);

    if(link_status == GL_FALSE) {
	    GLint log_size = 0;

        glGetProgramiv(gl_handle, GL_INFO_LOG_LENGTH, &log_size);

        GLchar* log = new GLchar[log_size]();

        glGetProgramInfoLog(gl_handle, log_size, &log_size, &log[0]);

        link_log = std::string(log);
        std::cerr << log << std::endl;

        delete[] log;

	    glDeleteProgram(gl_handle);
	    glDeleteShader(vertex_handle);
        glDeleteShader(fragment_handle);
        if(geometry_handle != 0)
	        glDeleteShader(geometry_handle);
	    return false;
    }

    glDetachShader(gl_handle, vertex_handle);
    glDetachShader(gl_handle, fragment_handle);
    if(geometry_handle != 0)
	    glDetachShader(gl_handle, geometry_handle);

    return true;
}

bool Shader::Validate(){
    glValidateProgram(gl_handle);

    GLint validated = 0;
    glGetProgramiv(gl_handle, GL_VALIDATE_STATUS, &validated);
    if(validated == GL_FALSE) {
	    GLint log_size = 0;
        glGetProgramiv(gl_handle, GL_INFO_LOG_LENGTH, &log_size);

        GLchar* log = new GLchar[log_size]();

        glGetProgramInfoLog(gl_handle, log_size, &log_size, &log[0]);
        std::cerr << &log[0] << std::endl;

        delete[] log;

	    return false;
    }
    return true;
}

bool Shader::SetUniform(const std::string& name, int value){
    int location = FindUniformLocation(name);
    if(location < 0) return false;

    glUniform1i(location, value);

    return true;
}

bool Shader::SetUniform(const std::string& name, float value){
    int location = FindUniformLocation(name);
    if(location < 0) return false;

    glUniform1f(location, value);

    return true;
}

bool Shader::SetUniform(const std::string& name, const glm::vec2& value){
    int location = FindUniformLocation(name);
    if(location < 0) return false;

    glUniform2f(location, value.x, value.y);

    return true;
}

bool Shader::SetUniform(const std::string& name, const glm::vec3& value){
    int location = FindUniformLocation(name);
    if(location < 0) return false;

    glUniform3f(location, value.x, value.y, value.z);

    return true;
}

bool Shader::SetUniform(const std::string& name, const glm::vec4& value){
    int location = FindUniformLocation(name);
    if(location < 0) return false;

    glUniform4f(location, value.x, value.y, value.z, value.w);

    return true;
}

bool Shader::SetUniform(const std::string& name, const glm::mat2& value){
    int location = FindUniformLocation(name);
    if(location < 0) return false;

    glUniformMatrix2fv(location, 1, false, &(value[0][0]));

    return true;
}

bool Shader::SetUniform(const std::string& name, const glm::mat3& value){
    int location = FindUniformLocation(name);
    if(location < 0) return false;

    glUniformMatrix3fv(location, 1, false, &(value[0][0]));

    return true;
}

bool Shader::SetUniform(const std::string& name, const glm::mat4& value){
    int location = FindUniformLocation(name);
    if(location < 0) return false;

    glUniformMatrix4fv(location, 1, false, &(value[0][0]));

    return true;
}

int Shader::FindUniformLocation(const std::string& name){
    if(!is_built) return -1;
    auto un_itr = uniform_locations.find(name);
    if(un_itr == uniform_locations.end()){
        int location = glGetUniformLocation(gl_handle, name.c_str());
        if(location >= 0){
            uniform_locations.insert(std::make_pair(name, location));
            return location;
        }
        return -1;
    }
    return un_itr->second;
}

bool compileShader(GLuint type, GLuint& handle, const std::string& source, std::string& compile_log){
    handle = glCreateShader(type);

    const char* c_src = source.c_str();
    glShaderSource(handle, 1, &c_src, nullptr);
    glCompileShader(handle);

    GLint compile_status;
    glGetShaderiv(handle, GL_COMPILE_STATUS, &compile_status);

    if(compile_status == GL_FALSE) {
        GLint log_size = 0;

        glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &log_size);

        GLchar* log = new GLchar[log_size]();

        glGetShaderInfoLog(handle, log_size, &log_size, log);

        compile_log = std::string(log);
        std::cerr << log << std::endl;

        delete[] log;

        glDeleteShader(handle);
        return false;
    }
    return true;
}
