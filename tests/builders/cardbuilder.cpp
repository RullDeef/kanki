#include "builder_base.hpp"
#include "cardbuilder.hpp"

CardBuilder CardBuilder::random()
{
    return CardBuilder()
        .withId(gen_random_uuid())
        .withSymbol(gen_random_string(10))
        .withReading(gen_random_string(15))
        .withDescription(gen_random_string(20));
}

CardBuilder &CardBuilder::withId(UUID newId)
{
    id = newId;
    return *this;
}

CardBuilder &CardBuilder::withSymbol(std::wstring newSymbol)
{
    symbol = std::move(newSymbol);
    return *this;
}

CardBuilder &CardBuilder::withReading(std::wstring newReading)
{
    reading = std::move(newReading);
    return *this;
}

CardBuilder &CardBuilder::withDescription(std::wstring newDescription)
{
    description = std::move(newDescription);
    return *this;
}

Card CardBuilder::build()
{
    return Card(id, symbol, reading, description);
}
