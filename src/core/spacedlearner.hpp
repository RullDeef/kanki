#pragma once

#include "core/ilearner.hpp"
#include "core/icollectionmanager.hpp"
#include "core/isessionmanager.hpp"

class SpacedLearner : public ILearner
{
public:
    SpacedLearner(ICollectionManager* collectionManager, ISessionManager* sessionManager)
        : collectionManager(collectionManager), sessionManager(sessionManager)
    {}

    virtual Card getNextForLearn(size_t deckId) override {
        auto deck = collectionManager->getDeckById(deckId);

        for (auto card : deck) {
            auto snapshots = sessionManager->getAllCardSnapshots(card);

            if (snapshots.empty())
                return card;
        }

        return Card(0, L"", L"", L"все карты уже пересмотрены");
    }

    virtual Card getNextForRepeat(size_t deckId) override {
        auto targets = getTargets(deckId);

        if (targets.empty())
            return Card(0, L"", L"", L"нет новых карт для повторения");

        // выбрать карту из targets
        auto selectedSnapshot = targets.front();
        std::chrono::system_clock::duration maxDuration = selectedSnapshot.getTimeDelta();
        for (const auto snapshot : targets)
        {
            ///TODO: должно быть не время старта, а время до момента повторения
            if (snapshot.getTimeDelta() > maxDuration)
            {
                selectedSnapshot = snapshot;
                maxDuration = snapshot.getTimeDelta();
            }
        }

        return selectedSnapshot.getCard();
    }

private:
    std::list<Snapshot> getTargets(size_t deckId) {
        std::list<Snapshot> result;
        auto deck = collectionManager->getDeckById(deckId);

        for (auto card : deck) {
            auto snapshots = sessionManager->getAllCardSnapshots(card);

            if (snapshots.size() == 0)
                continue;
            
            Snapshot recentSnapshot = snapshots.front();
            for (auto snapshot : snapshots)
                if (snapshot.getTimePoint() > recentSnapshot.getTimePoint())
                    recentSnapshot = snapshot;
            
            result.push_back(recentSnapshot);
        }

        return result;
    }

    ICollectionManager* collectionManager;
    ISessionManager* sessionManager;
};
