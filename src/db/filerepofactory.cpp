#include "filecollectionrepo.hpp"
#include "filesessionrepo.hpp"
#include "filerepofactory.hpp"

FileRepositoryFactory::FileRepositoryFactory(const std::string& collectionFilename, const std::string& sessionsFilename)
{
    collectionRepo = std::shared_ptr<ICollectionRepository>
        (new FileCollectionRepository(collectionFilename));
    sessionRepo = std::shared_ptr<ISessionRepository>
        (new FileSessionRepository(sessionsFilename));
}

std::shared_ptr<ICollectionRepository> FileRepositoryFactory::getCollectionRepo()
{
    return collectionRepo;
}

std::shared_ptr<ISessionRepository> FileRepositoryFactory::getSessionRepo()
{
    return sessionRepo;
}
