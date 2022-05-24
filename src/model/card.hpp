#pragma once

#include <string>

class Card
{
public:
    Card(size_t id = 0,
        const std::wstring& symbol = L"symbol",
        const std::wstring& reading = L"reading",
        const std::wstring& description = L"description")
        : id(id), symbol(symbol), reading(reading), description(description)
    {}

    const size_t getId() const { return id; }
    const std::wstring& getSymbol() const { return symbol; }
    const std::wstring& getReading() const { return reading; }
    const std::wstring& getDescription() const { return description; }

    void setSymbol(const std::wstring& value) { symbol = value; }
    void setReading(const std::wstring& value) { reading = value; }
    void setDescription(const std::wstring& value) { description = value; }

    bool operator==(const Card& other) const {
        return symbol == other.symbol && reading == other.reading &&
            description == other.description;
    }

private:
    size_t id;
    std::wstring symbol;
    std::wstring reading;
    std::wstring description;
};
