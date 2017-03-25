#include <ios>
#include <fstream>
#include <sstream>

#include "core/resources/shader.h"
#include "core/utils.h"

Shader Shader::load(string filepath) {
	Shader s;

	string vertexPath = filepath + ".v";
	string geometryPath = filepath + ".g";
	string fragmentPath = filepath + ".f";

	StringList vertexLines, geometryLines, fragmentLines;

	{
		bool vertex, geometry, fragment;
		vertex = readFileLines(vertexPath, vertexLines);
		geometry = readFileLines(geometryPath, geometryLines);
		fragment = readFileLines(fragmentPath, fragmentLines);

		if (!vertex)
			throw std::runtime_error("No vertex shader has been found.");
		if (!fragment)
			throw std::runtime_error("No fragment shader has been found.");
	}

	StringList tok = tokenize(vertexLines[0], ", \n");
	for (auto i = tok.begin(); i != tok.end(); i++) {
		std::cout << *i << std::endl;
	}
	return s;
}
