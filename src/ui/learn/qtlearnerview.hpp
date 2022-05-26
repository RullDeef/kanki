#pragma once

#include <QObject>
#include "core/ilearnerview.hpp"

class QtLearnerView : public QObject, public ILearnerView
{
    Q_OBJECT

public:
    virtual void showCard(const Card& card) override;
    virtual void askCard(const Card& card) override;

    virtual void noCardsForLearn() override;
    virtual void noCardsForRepeat() override;

signals:
    void showCardSignal(const Card& card);
    void showSnapshotSignal(const Card& card);

    void noCardsForLearnSignal();
    void noCardsForRepeatSignal();
};
