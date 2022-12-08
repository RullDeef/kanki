#include <algorithm>
#include <stdexcept>
#include "tools/logger.hpp"
#include "deckcollection.hpp"

DeckCollection::DeckCollection(UUID id, const std::wstring &name, std::list<Deck> decks)
    : id(id), name(name), decks(std::move(decks))
{
    if (id.is_nil())
    {
        ERROR_METHOD("nil as deckCollection id is not valid");
        throw std::runtime_error("nil as deckCollection id is not valid");
    }
}

UUID DeckCollection::getId() const
{
    return id;
}

const std::wstring &DeckCollection::getName() const
{
    return name;
}

size_t DeckCollection::size() const
{
    return decks.size();
}

std::list<std::wstring> DeckCollection::getDeckNames() const
{
    std::list<std::wstring> names(size());
    std::transform(begin(), end(), names.begin(), [](const Deck &d)
                   { return d.getName(); });
    return names;
}

void DeckCollection::addDeck(const Deck &deck)
{
    auto id = deck.getId();
    auto iter = std::find_if(decks.begin(), decks.end(), [id](const Deck &deck)
                             { return deck.getId() == id; });

    if (iter != decks.end())
        *iter = deck;
    else
        decks.push_back(deck);
}

DeckCollection::ConstIterator DeckCollection::begin() const
{
    return decks.begin();
}

DeckCollection::ConstIterator DeckCollection::end() const
{
    return decks.end();
}

const Deck *DeckCollection::getDeckById(UUID id) const
{
    auto iter = std::find_if(begin(), end(), [id](const Deck &deck)
                             { return deck.getId() == id; });

    if (iter != end())
        return &*iter;
    return nullptr;
}

void DeckCollection::removeDeckById(UUID id)
{
    decks.erase(
        std::remove_if(decks.begin(), decks.end(), [id](const Deck &deck)
                       { return deck.getId() == id; }),
        decks.end());
}

bool DeckCollection::operator==(const DeckCollection &other) const
{
    return id == other.id && name == other.name && decks == other.decks;
}

DeckCollection DeckCollection::createDefault()
{
    auto gen = std::mt19937();
    auto uuid = uuids::uuid_random_generator(gen)();
    return std::move(DeckCollection(uuid, L"collection"));
}
