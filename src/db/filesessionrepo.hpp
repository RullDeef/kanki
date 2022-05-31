#pragma once

#include <list>
#include <string>
#include "core/isessionrepository.hpp"
#include "db/idtoreader.hpp"
#include "db/idtowriter.hpp"

class FileSessionRepository : public ISessionRepository
{
public:
    virtual std::list<Session> getSessions() override;
    virtual Session getSession(UUID id) override;
    virtual void removeSession(UUID id) override;
    virtual void saveSession(const Session &session) override;

    void load(IDTOReader &reader);
    void dump(IDTOWriter &writer);

private:
    std::list<Session> sessions;
};
