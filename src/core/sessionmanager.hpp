#pragma once

#include <list>
#include "tools/logger.hpp"
#include "tools/idgenerator.hpp"
#include "model/card.hpp"
#include "model/snapshot.hpp"
#include "model/session.hpp"
#include "core/isessionrepository.hpp"
#include "core/isessionmanager.hpp"

class SessionManager : public ISessionManager
{
public:
    SessionManager(ISessionRepository* sessionRepository)
        : sessionRepository(sessionRepository), activeSession(IdGenerator()())
    {}

    ~SessionManager() {
        try {
            activeSession.endSession();
            sessionRepository->saveSession(activeSession);
        } catch (const std::exception& e) {
            ERROR_METHOD(e.what());
        }
    }

    virtual const Session& getActiveSession() override { return activeSession; }

    virtual void addSnapshot(const Snapshot& snapshot) override {
        LOG_METHOD();

        activeSession.addSnapshot(snapshot);

        ///KOSTYLI: preserve active session in repository
        activeSession.endSession();
        sessionRepository->saveSession(activeSession);
    }

    virtual std::list<Snapshot> getAllCardSnapshots(const Card& card) override {
        LOG_METHOD();

        std::list<Snapshot> result;

        for (auto session : sessionRepository->getSessions())
            for (auto snapshot : session)
                if (snapshot.getCard() == card)
                    result.push_back(snapshot);

        return result;
    }

private:
    ISessionRepository* sessionRepository;
    Session activeSession;
};
