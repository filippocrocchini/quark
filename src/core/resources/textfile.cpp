#include <ios>
#include <fstream>
#include <sstream>
#include <iostream>

#include <thread>

#include "core/resources/textfile.h"
#include "core/utils.h"

TextFileResource TextFileResource::load(std::string filepath) {
	TextFileResource res;
	if(!readFile(filepath, res.text))
		throw std::runtime_error("The file " + filepath + " cannot be opened for reading.");
	return res;
}
