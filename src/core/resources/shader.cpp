#include <ios>
#include <fstream>
#include <sstream>

#include "core/resources/shader.h"
#include "core/utils.h"

bool compileShader(GLuint type, GLuint& handle, const std::string& source, std::string& compileLog) {
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

        compileLog = std::string(log);
        std::cerr << log << std::endl;

        delete[] log;
    
        glDeleteShader(handle);
        return false;
    }
    return true;
}

bool Shader::compile() {
    if (!compileShader(GL_VERTEX_SHADER, vertexHandle, vertex, compileLogs[0]) ||
        !compileShader(GL_FRAGMENT_SHADER, fragmentHandle, fragment, compileLogs[1]) ||
        (!geometry.empty() && !compileShader(GL_GEOMETRY_SHADER, geometryHandle, geometry, compileLogs[2]))
        )
        return false;
    else
        return true;
}

bool Shader::link() {
    glHandle = glCreateProgram();
    if (glHandle == 0) {
        std::cerr << "Could not create the shader program. Probably the context in not valid." << std::endl;
        return false;
    }
    glAttachShader(glHandle, vertexHandle);
    if(geometryHandle != 0)
        glAttachShader(glHandle, geometryHandle);
    glAttachShader(glHandle, fragmentHandle);

    glLinkProgram(glHandle);

    GLint isLinked = 0;
    glGetProgramiv(glHandle, GL_LINK_STATUS, &isLinked);

    if(isLinked == GL_FALSE) {
	    GLint log_size = 0;

        glGetProgramiv(glHandle, GL_INFO_LOG_LENGTH, &log_size);

        GLchar* log = new GLchar[log_size]();

        glGetProgramInfoLog(glHandle, log_size, &log_size, &log[0]);

        linkLog = std::string(log);
        std::cerr << log << std::endl;

        delete[] log;

	    glDeleteProgram(glHandle);
	    glDeleteShader(vertexHandle);
        if(geometryHandle != 0)
	        glDeleteShader(geometryHandle);
        glDeleteShader(fragmentHandle);
	    return false;
    }

    glDetachShader(glHandle, vertexHandle);
    if(geometryHandle != 0)
	    glDetachShader(glHandle, geometryHandle);
    glDetachShader(glHandle, fragmentHandle);

    return true;
}

bool Shader::validate() {
    glValidateProgram(glHandle);
    
    GLint validated = 0;
    glGetProgramiv(glHandle, GL_VALIDATE_STATUS, &validated);
    if(validated == GL_FALSE) {
	    GLint log_size = 0;
        glGetProgramiv(glHandle, GL_INFO_LOG_LENGTH, &log_size);

        GLchar* log = new GLchar[log_size]();

        glGetProgramInfoLog(glHandle, log_size, &log_size, &log[0]);
        std::cerr << &log[0] << std::endl;

        delete[] log;

	    return false;
    }
    return true;
}

void Shader::fetchUniforms() {
    GLint count;
    glGetProgramiv(glHandle, GL_ACTIVE_UNIFORMS, &count);
    
    GLint maxLength;
    glGetProgramiv(glHandle, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxLength);

    GLchar* name = new GLchar[maxLength]();
    GLint size;
    GLenum type;

    IUniform* uniform;

    for (GLuint i = 0; i < (unsigned)count; ++i) {
        glGetActiveUniform(glHandle, i, maxLength, nullptr, &size, &type, name);
        switch (type) {
        case GL_SAMPLER_2D:
        case GL_INT:
            uniform = new Uniform<int>(i, size, name);
            break;
        case GL_FLOAT:
            uniform = new Uniform<float>(i, size, name);
            break;
        case GL_FLOAT_VEC2:
            uniform = new Uniform<glm::vec2>(i, size, name);
            break;
        case GL_FLOAT_VEC3:
            uniform = new Uniform<glm::vec3>(i, size, name);
            break;
        case GL_FLOAT_VEC4:
            uniform = new Uniform<glm::vec4>(i, size, name);
            break;
        case GL_FLOAT_MAT2:
            uniform = new Uniform<glm::mat2>(i, size, name);
            break;
        case GL_FLOAT_MAT3:
            uniform = new Uniform<glm::mat3>(i, size, name);
            break;
        case GL_FLOAT_MAT4:
            uniform = new Uniform<glm::mat4>(i, size, name);
            break;
        default:
            std::cerr << "Uniform " << name << " has not been fetched." << std::endl;
            continue;
        }
        uniforms.insert(std::make_pair(std::string(name), uniform));
    }

    delete[] name;
}

bool Shader::build() {
    if (compilation_failed = !compile()) return false;
    if (linkage_failed = !link()) return false;
    if (validation_failed = !validate()) return false;

    fetchUniforms();

    return true;
}

std::shared_ptr<Shader> Shader::load(std::string filepath) {
	std::shared_ptr<Shader> s = std::make_shared<Shader>();

	std::string vertexPath = filepath + ".v";
	std::string geometryPath = filepath + ".g";
	std::string fragmentPath = filepath + ".f";

	{
		bool vertex, geometry, fragment;
		vertex = readFile(vertexPath, s->vertex);
		geometry = readFile(geometryPath, s->geometry);
		fragment = readFile(fragmentPath, s->fragment);

		if (!vertex)
			throw std::runtime_error("No vertex shader has been found.");
		if (!fragment)
			throw std::runtime_error("No fragment shader has been found.");
	}

	return s;
}


void Shader::use() {
    if (!built) {
        if ( compilation_failed || linkage_failed || validation_failed )
            return;
        else 
            built = build();
    }
    
    glUseProgram(glHandle);
}


