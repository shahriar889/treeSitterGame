#include "StringHandling.h"
#include <string>
#include <vector>

//https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
std::vector<std::string> stringTools::split(const std::string &str, const std::string &delim){
    std::vector<std::string> tokens;
    size_t prev = 0, pos = 0;
    do{
        pos = str.find(delim, prev);
        if(pos == std::string::npos) pos = str.length();
        std::string token = str.substr(prev, pos-prev);
        if(!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }while(pos < str.length() && prev < str.length());
    return tokens;
}