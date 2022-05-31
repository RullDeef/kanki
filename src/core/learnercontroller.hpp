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
    LearnerController(std::shared_ptr<ICollectionManager> collectionManager, std::shared_ptr<ISessionManager> sessionManager);

    void setView(ILearnerView *newView);
    void setLearner(std::shared_ptr<ILearner> newLearner);
    void setEstimator(std::shared_ptr<IEstimator> newEstimator);

    void learnNext(UUID deckId);
    void repeatNext(UUID deckId);

    void confirmLearned(UUID cardId);

    void markEasy(UUID cardId, int paramType);
    void markGood(UUID cardId, int paramType);
    void markAgain(UUID cardId, int paramType);

private:
    std::unique_ptr<Card> getNextCardFor(UUID deckId, int paramType);

    ILearnerView *view = nullptr;
    std::shared_ptr<ILearner> learner;
    std::shared_ptr<IEstimator> estimator;

    IdGenerator idGenerator;
    int cardParam = Snapshot::ParamType::READING;

    std::shared_ptr<ICollectionManager> collectionManager;
    std::shared_ptr<ISessionManager> sessionManager;
};
