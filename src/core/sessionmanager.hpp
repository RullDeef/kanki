#pragma once

#include <list>
#include "model/card.hpp"
#include "model/snapshot.hpp"
#include "model/session.hpp"
#include "core/isessionrepository.hpp"
#include "core/isessionmanager.hpp"

class SessionManager : public ISessionManager
{
public:
    SessionManager(ISessionRepository *sessionRepository);
    ~SessionManager();

    virtual const Session &getActiveSession() override;
    virtual void addSnapshot(const Snapshot &snapshot) override;
    virtual std::list<Snapshot> getAllCardSnapshots(const Card &card) override;

private:
    ISessionRepository *sessionRepository;
    Session activeSession;
};
