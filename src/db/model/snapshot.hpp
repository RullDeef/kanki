#pragma once

#include <string>
#include "tools/uuid.hpp"

class DBSnapshot
{
public:
    UUID sessionId;
    UUID cardId;
    std::wstring cardSymbol;
    std::wstring cardReading;
    std::wstring cardDescription;
    int param;
    int knowledgeDegree;
    time_t timePoint;

    DBSnapshot() = default;
    DBSnapshot(const DBSnapshot &) = default;
};
