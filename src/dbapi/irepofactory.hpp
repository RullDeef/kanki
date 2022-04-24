#pragma once

#include <memory>
#include "icollectionrepo.hpp"
#include "isessionrepo.hpp"

class IRepositoryFactory
{
public:
    virtual ~IRepositoryFactory() = default;

    virtual std::shared_ptr<ICollectionRepository> getCollectionRepo() = 0;
    virtual std::shared_ptr<ISessionRepository> getSessionRepo() = 0;
};
