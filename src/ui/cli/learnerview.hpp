#pragma once

#include "core/learnercontroller.hpp"
#include "ui/model/uilearnerview.hpp"

namespace cli
{
    class LearnerView : public UILearnerView
    {
    public:
        void setLearnerController(std::shared_ptr<LearnerController> newController);

        virtual void showCard(const CardParams &params) override;
        virtual void askCard(const CardParams &card, int paramType) override;

        virtual void noCardsForLearn() override;
        virtual void noCardsForRepeat() override;

    private:
        std::shared_ptr<LearnerController> controller;
    };
} // namespace cli
