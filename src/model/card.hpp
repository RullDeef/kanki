#pragma once

#include <string>

class Card
{
public:
    Card(const std::wstring& symbol, const std::wstring& reading, const std::wstring& description);

    const std::wstring& getSymbol() const;
    const std::wstring& getReading() const;
    const std::wstring& getDescription() const;

    void setSymbol(const std::wstring& value);
    void setReading(const std::wstring& value);
    void setDescription(const std::wstring& value);

private:
    std::wstring symbol;
    std::wstring reading;
    std::wstring description;
};
