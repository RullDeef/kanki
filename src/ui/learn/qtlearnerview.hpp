#pragma once

#include <QObject>
#include "core/ilearnerview.hpp"

class LearnerController;

class QtLearnerView : public QObject, public ILearnerView
{
    Q_OBJECT

public:
    virtual void showCard(const Card& card) override;
    virtual void askCard(const Card& card) override;

    virtual void noCardsForLearn() override;
    virtual void noCardsForRepeat() override;

    void setController(LearnerController* newController);

private:
    LearnerController* controller = nullptr;
};
