#pragma once
#include <string>

class TextFileResource {
public:
	std::string text;
	static TextFileResource load(std::string filepath);
private:
	TextFileResource() = default;
};