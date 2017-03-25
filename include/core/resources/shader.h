#pragma once

#include <GLEW\glew.h>

#include <iostream>
#include <unordered_map>
#include <typeinfo>

enum ShaderState {
	SHADER_UNINITIALIZED,
	SHADER_COMPILED,
	SHADER_LINKED
};

enum UniformState {
	UNIFORM_NOT_FOUND,
	INVALID_UNIFORM_TYPE
};

using std::string;

struct UniformBase {
	std::type_info type;
	int location;
	bool active;
};

template<typename T>
class Uniform : public UniformBase {
	void set(T value) {
		this->value = value;
	}
private:
	T value;
	Uniform() = default;
	~Uniform() = default;
};

template<>
class Uniform<int> : public UniformBase{
public:
	void set(int value) {
		glUniform1i(0,0);
	}
private:
	Uniform();
	Uniform(int shaderHandle, string name);
	~Uniform() = default;
};

class Shader {
public:
	ShaderState state = SHADER_UNINITIALIZED;
	int glHandle = 0;

	~Shader() = default;

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
	string vertex;
private:
	Shader() = default;

	string geometry;
	string fragment;
	string debuglog;

	std::unordered_map < string, UniformBase* > uniforms;
};
