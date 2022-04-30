#include "qtcardview.hpp"

void QtCardView::showCard(const CardParams& cardParams)
{
    emit onShowCard(cardParams);
}
