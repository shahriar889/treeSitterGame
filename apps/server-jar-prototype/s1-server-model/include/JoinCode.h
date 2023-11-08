#ifndef SERVER_MODEL_JOIN_CODE_H
#define SERVER_MODEL_JOIN_CODE_H

#include <random>
#include <string>
#include <iostream>

struct JoinCode {
    std::string code;
    friend std::ostream& operator<<(std::ostream& os, const JoinCode& dt);
    friend bool operator== (const JoinCode& c1, const JoinCode& c2);
};

class JoinCodeGenerator {
private:
    static char chars[];
    std::mt19937 rg;
    std::uniform_int_distribution<std::string::size_type> pick;
public:
    JoinCodeGenerator(uint_fast32_t seed = 0);
    JoinCode makeJoinCode(int length);
};

#endif