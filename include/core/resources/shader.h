#pragma once

#include <GLEW/glew.h>
#include <glm/glm.hpp>

#include <memory>
#include <iostream>
#include <unordered_map>
#include <type_traits>


class IUniform {
public:
    IUniform(const GLuint& location, const GLint& size, const std::string& name) :
        location(location), size(size), name(name) {};

    virtual ~IUniform() = default;

    const GLuint& getLocation() const { return location; }
    const std::string& getName() const { return name; }

protected:
    IUniform() = default;

	GLuint location;
    GLint size;

	std::string name;
};

template <typename T>
class Uniform : public IUniform {
    static_assert(
        std::is_same<T, int>::value         ||
        std::is_same<T, float>::value       ||
        std::is_same<T, glm::vec2>::value   ||
        std::is_same<T, glm::vec3>::value   ||
        std::is_same<T, glm::vec4>::value   ||
        std::is_same<T, glm::mat2>::value   ||
        std::is_same<T, glm::mat3>::value   ||
        std::is_same<T, glm::mat4>::value,
        "T is not a valid type of uniform, it's either not supported by this library or not a valid GLSL type."
    );

public:
    Uniform(const GLuint& location, const GLint& size, const std::string& name) : IUniform(location, size, name) {}

    virtual ~Uniform() = default;

    virtual const T& get() const { return value; };
    virtual void set(const T& value) {};
private:
    T value;
};

template<>
void Uniform<int>::set(const int& value){
    this->value = value;
    glUniform1i(location, value);
}

template<>
void Uniform<float>::set(const float& value){
    this->value = value;
    glUniform1f(location, value);
}

template<>
void Uniform<glm::vec2>::set(const glm::vec2& value){
    this->value = value;
    glUniform2f(location, value.x, value.y);
}

template<>
void Uniform<glm::vec3>::set(const glm::vec3& value){
    this->value = value;
    glUniform3f(location, value.x, value.y, value.z);
}

template<>
void Uniform<glm::vec4>::set(const glm::vec4& value){
    this->value = value;
    glUniform4f(location, value.x, value.y, value.z, value.w);
}

template<>
void Uniform<glm::mat2>::set(const glm::mat2& value){
    this->value = value;
    glUniformMatrix2fv(location, 1, false, &(this->value)[0][0]);
}

template<>
void Uniform<glm::mat3>::set(const glm::mat3& value){
    this->value = value;
    glUniformMatrix3fv(location, 1, false, &(this->value)[0][0]);
}

template<>
void Uniform<glm::mat4>::set(const glm::mat4& value){
    this->value = value;
    glUniformMatrix4fv(location, 1, false, &(this->value)[0][0]);
}

class Shader {
public:
	int glHandle = 0;

	Shader() = default;
	//delete the shader program and the shaders and also the uniforms
	~Shader() {
		for (auto i = uniforms.begin(); i != uniforms.end(); i++) {
			delete i->second;
		}

        if(glHandle != 0)
            glDeleteProgram(glHandle);
	}

	void use();

	template<typename T>
	bool setUniform(std::string name, T value) {
        if (!built) return false;

		auto uniformItr = uniforms.find(name);
		if (uniformItr == uniforms.end()) {
			std::cerr << "Uniform " << name << " not found!\n";
			return false;
		}
        Uniform<T>* uniform = dynamic_cast<Uniform<T>*>(uniformItr->second);
        if (uniform == nullptr) {
            std::cerr << "Uniform " << name << " is not of type " << typeid(T).name() << std::endl;
            return false;
        }

        if(uniform->get() != value)
		    uniform->set(value);

        return true;
	}

	static std::shared_ptr<Shader> load(std::string filepath);
	std::unordered_map < std::string, IUniform* > uniforms;
private:
    bool built = false;
    bool compilation_failed = false;
    bool linkage_failed = false;
    bool validation_failed = false;

	std::string vertex;
	std::string geometry;
	std::string fragment;
	std::string compileLogs[3];
    std::string linkLog;

    GLuint vertexHandle;
    GLuint fragmentHandle;
    GLuint geometryHandle;
    
    bool compile();
    bool link();
    bool validate();
    void fetchUniforms();

    bool build();
};
