#pragma once

#include <memory>
#include "ilearnstategy.hpp"
#include "imodelmanager.hpp"

///TODO: create tests for this class
class SpacedRepetitionLearn : public ILearningStrategy
{
public:
    explicit SpacedRepetitionLearn(std::shared_ptr<IModelManager> modelManager);

    virtual Card getNextForLearn(const Deck& deck) override;
    virtual CardSnapshot getNextForRepeat(const Deck& deck, CardSnapshot::ParamType param) override;

private:
    // возвращает последний период повторения
    int getCurrInterval(const Card& card, CardSnapshot::ParamType param);

    // возвращает актуальный уровень знания карточки
    int getKnowledgeLevel(const Card& card, CardSnapshot::ParamType param);

    std::shared_ptr<IModelManager> modelManager;
};
