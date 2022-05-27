#pragma once

#include <string>

class SnapshotDTO
{
public:
    size_t sessionId;
    size_t cardId;
    size_t deckId;
    std::wstring cardSymbol;
    std::wstring cardReading;
    std::wstring cardDescription;
    int param;
    int knowledgeDegree;
    time_t timePoint;
};
