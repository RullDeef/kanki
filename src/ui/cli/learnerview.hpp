#pragma once

#include "core/learnercontroller.hpp"
#include "ui/model/uilearnerview.hpp"

namespace cli
{
    class LearnerView : public UILearnerView
    {
    public:
        void setLearnerController(LearnerController &newController);

        virtual void showCard(const CardParams &params) override;
        virtual void askCard(const CardParams &card, int paramType) override;

        virtual void noCardsForLearn() override;
        virtual void noCardsForRepeat() override;

    private:
        LearnerController *controller = nullptr;
    };
} // namespace cli
