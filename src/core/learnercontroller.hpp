#pragma once

#include "tools/idgenerator.hpp"
#include "model/session.hpp"
#include "model/snapshot.hpp"
#include "core/ilearner.hpp"
#include "core/iestimator.hpp"
#include "core/ilearnerview.hpp"
#include "core/icollectionmanager.hpp"
#include "core/isessionmanager.hpp"

class LearnerController
{
public:
    LearnerController(ICollectionManager *collectionManager, ISessionManager *sessionManager);

    void setView(ILearnerView *newView);
    void setLearner(ILearner *newLearner);
    void setEstimator(IEstimator *newEstimator);

    void learnNext(size_t deckId);
    void repeatNext(size_t deckId);

    void confirmLearned(size_t cardId);

    void markEasy(size_t cardId, int paramType);
    void markGood(size_t cardId, int paramType);
    void markAgain(size_t cardId, int paramType);

private:
    bool getNextCardFor(size_t deckId, Card& card, int paramType);

    ILearnerView *view = nullptr;
    ILearner *learner = nullptr;
    IEstimator *estimator = nullptr;

    IdGenerator idGenerator;
    int cardParam = Snapshot::ParamType::READING;

    ICollectionManager *collectionManager;
    ISessionManager *sessionManager;
};
