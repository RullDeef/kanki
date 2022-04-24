#pragma once

#include <string>
#include "dbapi/irepofactory.hpp"

class FileRepositoryFactory : public IRepositoryFactory
{
public:
    FileRepositoryFactory(const std::string& collectionFilename, const std::string& sessionsFilename);

    virtual std::shared_ptr<ICollectionRepository> getCollectionRepo() override;
    virtual std::shared_ptr<ISessionRepository> getSessionRepo() override;

private:
    std::shared_ptr<ICollectionRepository> collectionRepo;
    std::shared_ptr<ISessionRepository> sessionRepo;
};
