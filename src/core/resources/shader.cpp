#include <ios>
#include <fstream>
#include <sstream>

#include "core/resources/shader.h"
#include "core/utils.h"

void findUniforms(std::shared_ptr<Shader> s, const std::string& content);
UniformType parseType(const std::string& str);

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

        std::vector<char> log(log_size);

        glGetShaderInfoLog(handle, log_size, &log_size, &log[0]);

        compileLog = &log[0];
        std::cerr << &log[0] << std::endl;
    
        glDeleteShader(handle);
        return false;
    }
    return true;
}


bool Shader::build() {

    if (!compileShader(GL_VERTEX_SHADER, vertexHandle, vertex, compileLogs[0]) ||
        !compileShader(GL_FRAGMENT_SHADER, fragmentHandle, fragment, compileLogs[1]) ||
        (!geometry.empty() && !compileShader(GL_GEOMETRY_SHADER, geometryHandle, geometry, compileLogs[2]))
        ) {
        compilation_failed = true;
        return false;
    }

    glHandle = glCreateProgram();

    glAttachShader(glHandle, vertexHandle);
    if(geometryHandle != 0)
        glAttachShader(glHandle, geometryHandle);
    glAttachShader(glHandle, fragmentHandle);

    glLinkProgram(glHandle);

    GLint isLinked = 0;
    glGetProgramiv(glHandle, GL_LINK_STATUS, (int *)&isLinked);
    if(isLinked == GL_FALSE) {
	    GLint log_size = 0;

        glGetProgramiv(glHandle, GL_INFO_LOG_LENGTH, &log_size);

        std::vector<char> log(log_size);

        glGetProgramInfoLog(glHandle, log_size, &log_size, &log[0]);
        linkLog = &log[0];
        std::cerr << &log[0] << std::endl;
	
	    glDeleteProgram(glHandle);
	    glDeleteShader(vertexHandle);
        if(geometryHandle != 0)
	        glDeleteShader(geometryHandle);
        glDeleteShader(fragmentHandle);
        linkage_failed = true;
	    return false;
    }

    glDetachShader(glHandle, vertexHandle);
    if(geometryHandle != 0)
	        glDetachShader(glHandle, geometryHandle);
    glDetachShader(glHandle, fragmentHandle);

    return true;
}

std::shared_ptr<Shader> Shader::load(string filepath) {
	std::shared_ptr<Shader> s = std::make_shared<Shader>();

	string vertexPath = filepath + ".v";
	string geometryPath = filepath + ".g";
	string fragmentPath = filepath + ".f";

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

	findUniforms(s, s->vertex);
	findUniforms(s, s->fragment);

    if(!s->geometry.empty())
	    findUniforms(s, s->geometry);

	return s;
}


void Shader::use() {
    if (compilation_failed || linkage_failed)
        return;

    if (!built)
        built = build();
    
    glUseProgram(this->glHandle);
}

void findUniforms(std::shared_ptr<Shader> s, const std::string& content) {
	if (content.empty()) return;
	StringList lines = tokenize(content, "\n");

	std::string firstToken;
	StringList lineTokens;
	
	std::size_t offset = 0;

	for (auto line = lines.begin(); line != lines.end(); line++) {
		offset = 0;
		if (!findToken(*line, " ", offset, firstToken))continue;
		if (firstToken == "uniform") {
			lineTokens = tokenize(line->substr(offset), " ;");
			if (lineTokens.size() >= 2) {
				UniformType type = parseType(lineTokens[0]);
				std::cout << "Type: " << lineTokens[0] << std::endl;
				switch(type){
				case INT:
					s->uniforms.insert(std::pair<std::string, UniformBase*>(lineTokens[1], new Uniform<int>(s, lineTokens[1])));
					break;
				case FLOAT:
					s->uniforms.insert(std::pair<std::string, UniformBase*>(lineTokens[1], new Uniform<float>(s, lineTokens[1])));
					break;
				case VEC2:
					s->uniforms.insert(std::pair<std::string, UniformBase*>(lineTokens[1], new Uniform<Vec2>(s, lineTokens[1])));
					break;
				case VEC3:
					s->uniforms.insert(std::pair<std::string, UniformBase*>(lineTokens[1], new Uniform<Vec3>(s, lineTokens[1])));
					break;
				case VEC4:
					s->uniforms.insert(std::pair<std::string, UniformBase*>(lineTokens[1], new Uniform<Vec4>(s, lineTokens[1])));
					break;
				default:
					std::cerr << "Unknown uniform type at line: " << std::endl;
					if(line-lines.begin()>=1)
						std::cerr << "    " << *(line-1) << std::endl;
					std::cerr << "--> " << *(line) << std::endl;
					if(lines.end()-line>1)
						std::cerr << "    " << *(line+1) << std::endl;
				}
			}
		}
	}
}

UniformType parseType(const std::string& str) {
	if (str == "int")
		return INT;
	if (str == "float")
		return FLOAT;
	if (str == "vec2")
		return VEC2;
	if (str == "vec3")
		return VEC3;
	if (str == "vec4")
		return VEC4;
	return UNKNOWN;
}
