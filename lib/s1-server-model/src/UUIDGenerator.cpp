#include "UUIDGenerator.h"

// If the seed passed is == 0, UUIDGenerator will generate a random sequence of UUIDs.
// Otherwise, it will generate a non-random sequence of UUIDs based on the seed. 
UUIDGenerator::UUIDGenerator(uint32_t seed)
    : random{seed == 0}
    , mt19937{seed}
    , nonRandomGenerator{mt19937}
{}

UUIDGenerator::UUIDGenerator(const UUIDGenerator &other)
    : random{other.random}
    , mt19937{other.mt19937}
    , nonRandomGenerator{mt19937}
{}

boost::uuids::uuid UUIDGenerator::makeUUID() {
    return random ? randomGenerator() : nonRandomGenerator();
}
