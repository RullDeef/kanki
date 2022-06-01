#pragma once

#include "tools/uuid.hpp"

class IdGenerator
{
public:
    IdGenerator()
        : seed_data(std::array<int, std::mt19937::state_size>())
    {
        std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));
        std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
        generator = std::mt19937(seq);
        uuidGenerator = new uuids::uuid_random_generator(generator);
    }

    ~IdGenerator()
    {
        delete uuidGenerator;
    }

    UUID operator()()
    {
        return uuidGenerator->operator()();
    }

private:
    std::array<int, std::mt19937::state_size> seed_data;
    uuids::uuid_random_generator *uuidGenerator;
    std::mt19937 generator;
    std::random_device rd;
};
