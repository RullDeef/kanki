#pragma once

#include <list>
#include <memory>
#include "model/card.hpp"
#include "model/collection.hpp"
#include "model/cardsnapshot.hpp"
#include "model/session.hpp"
#include "dbapi/irepofactory.hpp"

class ModelManager
{
public:
    explicit ModelManager(std::shared_ptr<IRepositoryFactory> repoFactory);
    ~ModelManager();

    std::shared_ptr<Collection> getCollection();
    std::shared_ptr<Session> getActiveSession();
    std::list<CardSnapshot> getSnapshots(const Card& card);

    void setCollection(const Collection& newCollection);

private:
    std::shared_ptr<IRepositoryFactory> repoFactory;

    std::shared_ptr<Collection> activeCollection;
    std::shared_ptr<Session> activeSession;
};
