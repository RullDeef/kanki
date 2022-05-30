#include "tools/logger.hpp"
#include "learnercontroller.hpp"

LearnerController::LearnerController(ICollectionManager *collectionManager, ISessionManager *sessionManager)
    : collectionManager(collectionManager), sessionManager(sessionManager)
{
}

void LearnerController::setView(ILearnerView *newView)
{
    view = newView;
}

void LearnerController::setLearner(ILearner *newLearner)
{
    learner = newLearner;
}

void LearnerController::setEstimator(IEstimator *newEstimator)
{
    estimator = newEstimator;
}

void LearnerController::learnNext(size_t deckId)
{
    LOG_METHOD();

    try
    {
        auto card = learner->getNextForLearn(deckId);

        if (view != nullptr)
            view->showCard(card);
    }
    catch (const std::exception &e)
    {
        if (view != nullptr)
            view->noCardsForLearn();
    }
}

void LearnerController::repeatNext(size_t deckId)
{
    LOG_METHOD();

    Card readingCard, translatingCard;

    bool hasReading = getNextCardFor(deckId, readingCard, Snapshot::ParamType::READING);
    bool hasTranslating = getNextCardFor(deckId, translatingCard, Snapshot::ParamType::TRANSLATION);

    if (hasReading && cardParam == Snapshot::ParamType::READING)
    {
        if (view != nullptr)
            view->askCard(readingCard, cardParam);
        cardParam = Snapshot::ParamType::TRANSLATION;
    }
    else if (hasTranslating)
    {
        if (view != nullptr)
            view->askCard(translatingCard, Snapshot::ParamType::TRANSLATION);
        cardParam = Snapshot::ParamType::READING;
    }
    else if (hasReading)
    {
        if (view != nullptr)
            view->askCard(readingCard, Snapshot::ParamType::READING);
    }
    else if (view != nullptr)
        view->noCardsForRepeat();
}

void LearnerController::confirmLearned(size_t cardId)
{
    LOG_METHOD();

    Card card = collectionManager->getCardById(cardId);
    Snapshot snapshot(card);

    sessionManager->addSnapshot(snapshot);
}

void LearnerController::markEasy(size_t cardId, int paramType)
{
    LOG_METHOD();

    Card card = collectionManager->getCardById(cardId);
    Snapshot snapshot(card, Snapshot::ParamType(paramType));

    estimator->markEasy(snapshot);
    sessionManager->addSnapshot(snapshot);
}

void LearnerController::markGood(size_t cardId, int paramType)
{
    LOG_METHOD();

    Card card = collectionManager->getCardById(cardId);
    Snapshot snapshot(card, Snapshot::ParamType(paramType));

    estimator->markGood(snapshot);
    sessionManager->addSnapshot(snapshot);
}

void LearnerController::markAgain(size_t cardId, int paramType)
{
    LOG_METHOD();

    Card card = collectionManager->getCardById(cardId);
    Snapshot snapshot(card, Snapshot::ParamType(paramType));

    estimator->markAgain(snapshot);
    sessionManager->addSnapshot(snapshot);
}

bool LearnerController::getNextCardFor(size_t deckId, Card &card, int paramType)
{
    try
    {
        card = learner->getNextForRepeat(deckId, paramType);
        return true;
    }
    catch(const std::exception& e)
    {
        return false;
    }    
}
