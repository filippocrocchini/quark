#pragma once

#include <GLEW/glew.h>

#include <memory>
#include <iostream>
#include <unordered_map>
#include <typeindex>

class Shader;

struct Vec2 {
	float x, y;
};

struct Vec3 {
	float x, y, z;
};

struct Vec4 {
	float x, y, z, w;
};

enum UniformType {
	UNKNOWN,
	INT,
	FLOAT,
	VEC2,
	VEC3,
	VEC4
};

enum ShaderState {
	SHADER_UNINITIALIZED,
	SHADER_COMPILED,
	SHADER_LINKED
};

using std::string;

class UniformBase {
public:
    UniformBase(std::shared_ptr<Shader> parent, std::type_index type,const std::string name) : parent(parent), type(type), name(name){
        location = glGetUniformLocation(parent->glHandle, name.c_str());
    }
    virtual ~UniformBase() {};
    bool isActive() { return active; }
    std::type_index getType() { return type; }
    int getLocation() { return location; }
    const std::string& getName() { return name; }

protected:	
    std::type_index type;
	int location;
	bool active;
	std::string name;
    std::shared_ptr<Shader> parent;
};

template<typename T>
class Uniform{
private:
    Uniform() = default;
	~Uniform() = default;
};

//TODO: Uniform::set(T val) has to be implemented so that when invoked it sets the uniform in the parent shader program.

template<>
class Uniform<int> : public UniformBase{
public:
    Uniform(std::shared_ptr<Shader> parent,const string name) : UniformBase(parent, typeid(int), name){}

	~Uniform() = default;
    void set(int value) { this->value = value; }
private:
    int value;
};

template<>
class Uniform<float> : public UniformBase{
public:
	Uniform(std::shared_ptr<Shader> parent,const string name) : UniformBase(parent, typeid(float), name){}

	~Uniform() = default;
	void set(float value){ this->value = value; }
private:
    float value;
};

template<>
class Uniform<Vec2> : public UniformBase{
public:
	Uniform(std::shared_ptr<Shader> parent,const string name) : UniformBase(parent, typeid(Vec2), name){}

	~Uniform() = default;
	void set(Vec2 value){ this->value = value; }
private:
    Vec2 value;
};

template<>
class Uniform<Vec3> : public UniformBase{
public:
	Uniform(std::shared_ptr<Shader> parent,const string name) : UniformBase(parent, typeid(Vec3), name){}

	~Uniform() = default;
	void set(Vec3 value){
        this->value = value;
        glUniform3f(location, value.x, value.y, value.z);
    }
private:
    Vec3 value;
};

template<>
class Uniform<Vec4> : public UniformBase{
public:
	Uniform(std::shared_ptr<Shader> parent,const string name) : UniformBase(parent, typeid(Vec4), name){}

	~Uniform() = default;
	void set(Vec4 value){ this->value = value; }
private:
    Vec4 value;
};


class Shader {
public:
	ShaderState state = SHADER_UNINITIALIZED;
	int glHandle = 0;

	Shader() = default;
	//delete the shader program and the shaders and also the uniforms
	~Shader() {
		for (auto i = uniforms.begin(); i != uniforms.end(); i++) {
			delete i->second;
		}
	}

	void use();

	template<typename T>
	void setUniform(string name, T value) {
		auto uniformItr = uniforms.find(name);
		if (uniformItr == uniforms.end()) {
			std::cerr << "Uniform " << name << " not found!\n";
			return;
		}
		Uniform<T>* uniform = dynamic_cast<Uniform<T>*>(uniformItr->second);
		if (uniform == nullptr) {
            std::cerr << "Uniform type mismatch, uniform " << name << " is " << uniformItr->second->getType().name() << ", you passed " << typeid(T).name() << ".\n";
			return;
		}
		uniform->set(value);
	}

	static std::shared_ptr<Shader> load(string filepath);
	std::unordered_map < string, UniformBase* > uniforms;
private:
    bool built = false;
    bool compilation_failed = false;
    bool linkage_failed = false;

	string vertex;
	string geometry;
	string fragment;
	string compileLogs[3];
    string linkLog;

    GLuint vertexHandle;
    GLuint fragmentHandle;
    GLuint geometryHandle;

    bool build();
};
