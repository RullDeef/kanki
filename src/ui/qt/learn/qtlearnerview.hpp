#pragma once

#include <QObject>
#include <memory>
#include "ui/model/uilearnerview.hpp"

class LearnerController;

class QtLearnerView : public QObject, public UILearnerView
{
    Q_OBJECT

public:
    virtual void showCard(const CardParams& params) override;
    virtual void askCard(const CardParams& card, int paramType) override;

    virtual void noCardsForLearn() override;
    virtual void noCardsForRepeat() override;

    void setController(std::shared_ptr<LearnerController> newController);

private:
    std::shared_ptr<LearnerController> controller;
};
