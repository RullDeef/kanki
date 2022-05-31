#pragma once

#include <list>
#include "model/snapshot.hpp"
#include "model/session.hpp"

class ISessionRepository
{
public:
    virtual ~ISessionRepository() = default;

    virtual std::list<Session> getSessions() = 0;
    virtual Session getSession(UUID id) = 0;
    virtual void removeSession(UUID id) = 0;
    virtual void saveSession(const Session& session) = 0;
};
