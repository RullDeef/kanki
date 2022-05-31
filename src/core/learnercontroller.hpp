#pragma once

#include <memory>
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

    void learnNext(UUID deckId);
    void repeatNext(UUID deckId);

    void confirmLearned(UUID cardId);

    void markEasy(UUID cardId, int paramType);
    void markGood(UUID cardId, int paramType);
    void markAgain(UUID cardId, int paramType);

private:
    std::unique_ptr<Card> getNextCardFor(UUID deckId, int paramType);

    ILearnerView *view = nullptr;
    ILearner *learner = nullptr;
    IEstimator *estimator = nullptr;

    IdGenerator idGenerator;
    int cardParam = Snapshot::ParamType::READING;

    ICollectionManager *collectionManager;
    ISessionManager *sessionManager;
};
