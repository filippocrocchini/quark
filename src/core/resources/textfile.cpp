#include <ios>
#include <fstream>
#include <sstream>
#include <iostream>

#include <thread>

#include "core/resources/textfile.h"

TextFileResource TextFileResource::load(std::string filepath) {

	std::this_thread::sleep_for(std::chrono::seconds(4));

	TextFileResource res;
	
	std::stringstream raw;
	std::ifstream file;
	
	file.open(filepath);
	
	if (!file.is_open()) {
		file.close();
		throw std::runtime_error("The file " + filepath + " cannot be opened for reading. (Make sure it is in the executable folder ;) )");
	}

	raw << file.rdbuf();
	file.close();

	res.text = raw.str();
	return res;
}