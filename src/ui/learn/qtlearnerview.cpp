#include "qtlearnerview.hpp"

void QtLearnerView::showCard(const Card& card) {
    emit showCardSignal(card);
}

void QtLearnerView::askCard(const Card& card) {
    emit showSnapshotSignal(card);
}

void QtLearnerView::noCardsForLearn() {
    emit noCardsForLearnSignal();
}

void QtLearnerView::noCardsForRepeat() {
    emit noCardsForRepeatSignal();
}
