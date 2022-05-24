#pragma once

#include <random>

class IdGenerator
{
public:
    IdGenerator() {
        size_t a = 1;
        size_t b = 100000;

        idGenerator = std::mt19937(rd());
        idDestribution = std::uniform_int_distribution<size_t>(a, b);
    }

    size_t operator()() {
        return idDestribution(idGenerator);
    }

private:
    std::random_device rd;
    std::mt19937 idGenerator;
    std::uniform_int_distribution<size_t> idDestribution;
};
