#pragma once

#include "dbapi/irepofactory.hpp"
#include "imodelmanager.hpp"

class ModelManager : public IModelManager
{
public:
    explicit ModelManager(std::shared_ptr<IRepositoryFactory> repoFactory);
    ~ModelManager();

    virtual std::shared_ptr<Collection> getCollection() override;
    virtual std::shared_ptr<Session> getActiveSession() override;
    virtual std::list<CardSnapshot> getSnapshots(const Card& card) override;

    virtual void setCollection(const Collection& newCollection) override;

private:
    std::shared_ptr<IRepositoryFactory> repoFactory;

    std::shared_ptr<Collection> activeCollection;
    std::shared_ptr<Session> activeSession;
};
