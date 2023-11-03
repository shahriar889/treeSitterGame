#include "JoinCode.h"

char JoinCodeGenerator::chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

std::ostream& operator<<(std::ostream& out, const JoinCode& code) {
    out << code.code;
    return out;
}

bool operator== (const JoinCode& j1, const JoinCode& j2) {
    return j1.code == j2.code;
}

// If seed == 0, JoinCodeGenerator will generate a random sequence of JoinCode.
// Otherwise, it will generate a non-random sequence of JoinCode based on the seed. 
JoinCodeGenerator::JoinCodeGenerator(uint_fast32_t seed) {
    if (seed == 0) {
        rg = std::mt19937{std::random_device{}()};
    } else {
        rg = std::mt19937{seed};
    }
    std::uniform_int_distribution<std::string::size_type> intdist(0, sizeof(chars) - 2);
    pick = intdist;
}

JoinCode JoinCodeGenerator::makeJoinCode(int length) {
    std::string code;
    code.reserve(length);

    while (length --) {
        code += chars[pick(rg)];
    }
    
    return JoinCode{code};
}
