#pragma once

#include <list>
#include "model/snapshot.hpp"
#include "model/session.hpp"

class ISessionManager
{
public:
    virtual ~ISessionManager() = default;

    virtual const Session& getActiveSession() = 0;
    virtual void addSnapshot(const Snapshot& snapshot) = 0;
    virtual std::list<Snapshot> getAllCardSnapshots(const Card& card) = 0;
};
