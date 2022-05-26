#pragma once

#include <string>

class Card
{
public:
    Card(size_t id = 0,
         const std::wstring &symbol = L"symbol",
         const std::wstring &reading = L"reading",
         const std::wstring &description = L"description");

    const size_t getId() const;
    const std::wstring &getSymbol() const;
    const std::wstring &getReading() const;
    const std::wstring &getDescription() const;

    void setSymbol(const std::wstring &value);
    void setReading(const std::wstring &value);
    void setDescription(const std::wstring &value);

    bool operator==(const Card &other) const;

private:
    size_t id;
    std::wstring symbol;
    std::wstring reading;
    std::wstring description;
};
