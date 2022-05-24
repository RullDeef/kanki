#pragma once

#include "tools/logger.hpp"
#include "tools/idgenerator.hpp"
#include "model/session.hpp"
#include "model/snapshot.hpp"
#include "core/ilearner.hpp"
#include "core/iestimator.hpp"
#include "core/ilearnerview.hpp"
#include "core/collectionmanager.hpp"
#include "core/sessionmanager.hpp"

class LearnerController
{
public:
    LearnerController(CollectionManager& collectionManager, SessionManager& sessionManager)
        : collectionManager(collectionManager), sessionManager(sessionManager)
    {}

    void setView(ILearnerView* newView) { view = newView; }
    void setLearner(ILearner* newLearner) { learner = newLearner; }
    void setEstimator(IEstimator* newEstimator) { estimator = newEstimator; }

    void learnNext(size_t deckId) {
        LOG_METHOD();

        auto card = learner->getNextForLearn(deckId);

        if (view != nullptr)
            view->showCard(card);
    }

    void repeatNext(size_t deckId) {
        LOG_METHOD();

        auto card = learner->getNextForRepeat(deckId);

        if (view != nullptr)
            view->askCard(card);
    }

    void confirmLearned(size_t cardId) {
        LOG_METHOD();

        Card card = collectionManager.getCardById(cardId);
        Snapshot snapshot(card, Snapshot::ParamType::READING); ///TODO: implement param type

        sessionManager.addSnapshot(snapshot);
    }

    void markEasy(size_t cardId) {
        LOG_METHOD();
        
        Card card = collectionManager.getCardById(cardId);
        Snapshot snapshot(card, Snapshot::ParamType::READING);

        estimator->markEasy(snapshot);
        sessionManager.addSnapshot(snapshot);
    }

    void markGood(size_t cardId) {
        LOG_METHOD();
        
        Card card = collectionManager.getCardById(cardId);
        Snapshot snapshot(card, Snapshot::ParamType::READING);

        estimator->markGood(snapshot);
        sessionManager.addSnapshot(snapshot);
    }

    void markAgain(size_t cardId) {
        LOG_METHOD();
        
        Card card = collectionManager.getCardById(cardId);
        Snapshot snapshot(card, Snapshot::ParamType::READING);

        estimator->markAgain(snapshot);
        sessionManager.addSnapshot(snapshot);
    }

private:
    ILearnerView* view = nullptr;
    ILearner* learner = nullptr;
    IEstimator* estimator = nullptr;

    IdGenerator idGenerator;

    CollectionManager& collectionManager;
    SessionManager& sessionManager;
};
