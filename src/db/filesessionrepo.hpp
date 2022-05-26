#pragma once

#include <list>
#include <string>
#include "core/icollectionrepository.hpp"
#include "core/isessionrepository.hpp"

class FileSessionRepository : public ISessionRepository
{
public:
    FileSessionRepository(ICollectionRepository *collectionRepo, const std::string &filename);
    ~FileSessionRepository();

    virtual std::list<Session> getSessions() override;
    virtual Session getSession(size_t id) override;
    virtual void removeSession(size_t id) override;
    virtual void saveSession(const Session &session) override;

    void load();
    void dump();

private:
    Session updateSessionCards(const Session &session);
    Card findCardById(size_t cardId);

    std::string filename;
    std::list<Session> sessions;

    ICollectionRepository *collectionRepo;
};
