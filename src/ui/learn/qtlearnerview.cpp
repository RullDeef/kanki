#include "qtlearnerview.hpp"

void QtLearnerView::showCard(const Card& card) {
    emit showCardSignal(card);
}

void QtLearnerView::askCard(const Card& card) {
    emit showSnapshotSignal(card);
}
