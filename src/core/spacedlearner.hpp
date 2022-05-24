#pragma once

#include "core/ilearner.hpp"
#include "core/collectionmanager.hpp"
#include "core/sessionmanager.hpp"

class SpacedLearner : public ILearner
{
public:
    SpacedLearner(CollectionManager& collectionManager, SessionManager& sessionManager)
        : collectionManager(collectionManager), sessionManager(sessionManager)
    {}

    virtual Card getNextForLearn(size_t deckId) override {
        auto deck = collectionManager.getDeckById(deckId);

        for (auto card : deck) {
            auto snapshots = sessionManager.getAllCardSnapshots(card);

            if (snapshots.size() == 0)
                return card;
        }

        return Card(0, L"test symbol", L"test reading", L"все карты уже пересмотрены");
    }

    virtual Card getNextForRepeat(size_t deckId) override {
        ///TODO: implement
        return Card(0, L"test symbol", L"test reading", L"test description");
    }

private:
    CollectionManager& collectionManager;
    SessionManager& sessionManager;
};
