#include <algorithm>
#include "collection.hpp"

Collection::Collection(size_t id, const std::wstring &name)
    : id(id), name(name)
{
}

size_t Collection::getId() const
{
    return id;
}

const std::wstring &Collection::getName() const
{
    return name;
}

size_t Collection::size() const
{
    return decks.size();
}

std::list<std::wstring> Collection::getDeckNames() const
{
    std::list<std::wstring> names(size());
    std::transform(begin(), end(), names.begin(), [](const Deck &d)
                   { return d.getName(); });
    return names;
}

void Collection::addDeck(const Deck &deck)
{
    size_t id = deck.getId();
    auto iter = std::find_if(decks.begin(), decks.end(), [id](const Deck &deck)
                             { return deck.getId() == id; });

    if (iter != decks.end())
        *iter = deck;
    else
        decks.push_back(deck);
}

Collection::ConstIterator Collection::begin() const
{
    return decks.begin();
}

Collection::ConstIterator Collection::end() const
{
    return decks.end();
}

const Deck *Collection::getDeckById(size_t id) const
{
    auto iter = std::find_if(begin(), end(), [id](const Deck &deck)
                             { return deck.getId() == id; });

    if (iter != end())
        return &*iter;
    return nullptr;
}

void Collection::removeDeckById(size_t id)
{
    decks.erase(
        std::remove_if(decks.begin(), decks.end(), [id](const Deck &deck)
                       { return deck.getId() == id; }),
        decks.end());
}
