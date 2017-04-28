#pragma once
#include <string>

class TextFileResource {
public:
	std::string text;
	static std::shared_ptr<TextFileResource> load(std::string filepath);
	TextFileResource() = default;
private:
};