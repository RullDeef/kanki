#pragma once

#include "cardparams.hpp"

class ICardView
{
public:
    virtual ~ICardView() = default;

    virtual void showCard(const CardParams& cardParams) = 0;
};
