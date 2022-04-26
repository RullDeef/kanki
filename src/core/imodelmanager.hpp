#pragma once

#include <memory>
#include <list>
#include "model/session.hpp"
#include "model/cardsnapshot.hpp"
#include "model/card.hpp"
#include "model/collection.hpp"

class IModelManager
{
public:
    virtual ~IModelManager() = default;

    virtual std::shared_ptr<Collection> getCollection() = 0;
    virtual std::shared_ptr<Session> getActiveSession() = 0;
    virtual std::list<CardSnapshot> getSnapshots(const Card& card) = 0;

    virtual void setCollection(const Collection& newCollection) = 0;
};
