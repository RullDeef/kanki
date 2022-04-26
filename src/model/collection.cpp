//#include <algorithm>
#include "collection.hpp"

std::shared_ptr<Deck> Collection::addNewDeck()
{
    return decks.emplace_back(std::make_shared<Deck>());
}

void Collection::removeDeck(const std::shared_ptr<Deck>& deck)
{
    decks.remove(deck);
}

size_t Collection::size() const
{
    return decks.size();
}

std::list<Deck::name_type> Collection::getDeckNames() const
{
    std::list<Deck::name_type> names(size());
    std::transform(begin(), end(), names.begin(),
        [](const std::shared_ptr<Deck>& d) { return d->getName(); });
    return names;
}

std::list<std::shared_ptr<Deck>>::const_iterator Collection::begin() const
{
    return decks.begin();
}

std::list<std::shared_ptr<Deck>>::const_iterator Collection::end() const
{
    return decks.end();
}
