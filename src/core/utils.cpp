#include "core/utils.h"

#include <fstream>
#include <sstream>
#include <iostream>

bool readFile(const std::string path, std::string& content) {
	if (path.empty())
	return false;

	std::ifstream file;
	std::stringstream raw;

	file.open(path);
	if (!file.is_open()) {
		file.close();
		std::cerr << "The file " + path + " cannot be opened for reading." << std::endl;
		return false;
	}
	raw << file.rdbuf();
	file.close();

	content = raw.str();
	return true;
}

bool readFileLines(const std::string path, StringList& content) {
	if (path.empty())
	return false;

	std::ifstream file;
	file.open(path);
	{
		if (!file.is_open()) {
			file.close();
			std::cerr << "The file " + path + " cannot be opened for reading." << std::endl;
			return false;
		}

		std::string str;
		content.clear();
		while (std::getline(file, str)) {
			content.push_back(str);
		}
	}
	file.close();
	return true;
}

bool findToken(const std::string& str, const std::string& delimiters, std::size_t& offset,  std::string &token) {
	std::size_t start = str.find_first_not_of(delimiters, offset);
	std::size_t end = str.find_first_of(delimiters, start);
	
	if (str.empty() || start == std::string::npos)
		return false;
	
	if (end != std::string::npos)
		token = str.substr(start, end - start);
	else
		token = str.substr(start);

	offset = end;
	return true;
}

StringList tokenize(const std::string& str, const std::string& delimiters) {
	StringList tokens;
	
	if (str.empty())
		return tokens;

	std::string token;
	std::size_t offset = 0;
	while (findToken(str, delimiters, offset, token)) tokens.push_back(token);
	
	return tokens;
}


