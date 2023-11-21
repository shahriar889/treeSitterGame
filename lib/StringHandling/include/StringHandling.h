#pragma once

#include <string>
#include <vector>

namespace stringTools{

std::vector<std::string> split(const std::string &str, const std::string &delim);
// std::vector<std::string_view> split(const std::string &str, const char &delim);

};
