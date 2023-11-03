#ifndef SERVER_MODEL_UUID_GENERATOR_H
#define SERVER_MODEL_UUID_GENERATOR_H

#include <random>
#include <string>
#include <iostream>
#include <boost/random.hpp>
#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators

class UUIDGenerator {
private:
    bool random;
    boost::random::mt19937 mt19937;
    boost::uuids::random_generator_mt19937 nonRandomGenerator;
    boost::uuids::random_generator randomGenerator;
public:
    UUIDGenerator(uint32_t seed = 0);
    UUIDGenerator(const UUIDGenerator&);
    boost::uuids::uuid makeUUID();
};

#endif