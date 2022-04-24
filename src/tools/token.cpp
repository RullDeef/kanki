#include "token.hpp"
#include <sstream>
#include <chrono>

std::string TokenGenerator::generate()
{
    auto tp = std::chrono::system_clock::now();
    auto ticks = tp.time_since_epoch().count();

    std::ostringstream token;
    token << "token#" << ticks;

    return token.str();
}
