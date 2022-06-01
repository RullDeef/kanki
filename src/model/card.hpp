#pragma once

#include <string>
#include "tools/uuid.hpp"

class Card
{
public:
    Card(UUID id,
         const std::wstring &symbol,
         const std::wstring &reading,
         const std::wstring &description);

    UUID getId() const;
    const std::wstring &getSymbol() const;
    const std::wstring &getReading() const;
    const std::wstring &getDescription() const;

    void setSymbol(const std::wstring &value);
    void setReading(const std::wstring &value);
    void setDescription(const std::wstring &value);

    bool operator==(const Card &other) const;

private:
    UUID id;
    std::wstring symbol;
    std::wstring reading;
    std::wstring description;
};
