#pragma once
#include <string>

class TextFileResource {
public:
	std::string text;
	static TextFileResource load(std::string filepath);
private:
	TextFileResource() = default;
};


/*
std::string loadTextFile(std::string path) {
	std::stringstream text;
	std::ifstream file;
	
	try {
		file.open(path);
	}
	catch (std::ios::failure exc) {
		std::cout << exc.what() << std::endl;
		file.close();
		return "";
	}

	text << file.rdbuf();
	file.close();

	return text.str();
}*/