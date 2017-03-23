#pragma once
#include <iostream>
#include <unordered_map>
#include <typeinfo>

#include <GL/glcorearb.h>

#define SHADER_UNINITIALIZED 0
#define SHADER_COMPILED 1
#define SHADER_LINKED 2
#define SHADER_LOADING_FAILED 3

#define UNIFORM_NOT_FOUND 4
#define INVALID_UNIFORM_TYPE 5

using std::string;

struct UniformBase {
	std::type_info type;
	int location;
	bool active;
};

template<typename T>
class Uniform : public UniformBase {
	void set(T value);
private:
	T value;
	Uniform() = default;
	~Uniform() = default;
};

class Uniform<int> : public UniformBase{
public:
	void set(int value) {
		glUniformi(0,0);
	}
private:
	Uniform();
	Uniform(int shaderHandle, string name);
	~Uniform();
};

class Shader {
public:
	int state = SHADER_UNINITIALIZED;
	int glHandle = 0;
	
	~Shader();

	void use();

	template<typename T>
	void setUniform(string name, T value) {
		auto uniformItr = uniforms.find(name);
		if (uniformItr == uniforms.end()) {
			throw std::runtime_error("Uniform " + name + " not found!");
			return;
		}
		Uniform<T>* uniform = dynamic_cast<Uniform<T>*>(*uniformItr);
		if (uniform == nullptr) {
			throw std::runtime_error("Uniform type mismatch, uniform " + name + " is " + uniformItr->second->type.name() + " you passed " + typeid(T).name() + ".");
			return;
		}
		uniform->set(value);
	}

	static Shader load(string filepath);
private:
	Shader() = default;

	string vertex;
	string geometry;
	string fragment;
	string debuglog;

	std::unordered_map < string, UniformBase* > uniforms;
};