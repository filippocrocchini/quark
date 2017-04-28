#include <ios>
#include <fstream>
#include <sstream>
#include <iostream>

#include <thread>

#include "core/resources/textfile.h"
#include "core/utils.h"

std::shared_ptr<TextFileResource> TextFileResource::load(std::string filepath) {
	std::shared_ptr<TextFileResource> res = std::make_shared<TextFileResource>();
	if(!readFile(filepath, res->text))
		throw std::runtime_error("The file " + filepath + " cannot be opened for reading.");
	return res;
}
