#pragma once
#include <string>
#include <vector>

typedef std::vector<std::string> StringList;

bool readFile(const std::string path, std::string& content);
bool readFileLines(const std::string path, StringList& content);
bool findToken(const std::string& str, const std::string& delimiters, std::size_t& offset, std::string &token);
StringList tokenize(const std::string& str, const std::string& delimiters);