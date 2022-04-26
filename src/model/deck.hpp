#pragma once

#include <memory>
#include <list>
#include <string>
#include "card.hpp"

class Deck
{
public:
    using name_type = std::string;

    explicit Deck(const name_type& name = "new Deck");

    const name_type& getName() const;
    void setName(const name_type& newName);

    void addCard(Card&& card);
    std::shared_ptr<Card> addNewCard();
    
    void deleteCard(size_t index);
    void deleteCard(const std::shared_ptr<Card>& card);

    size_t size() const;

    std::list<std::shared_ptr<Card>>::const_iterator begin() const;
    std::list<std::shared_ptr<Card>>::const_iterator end() const;

private:
    name_type name;
    std::list<std::shared_ptr<Card>> cards;
};
