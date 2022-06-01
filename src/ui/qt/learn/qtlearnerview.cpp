#include "learn_window.hpp"
#include "repeat_window.hpp"
#include "info_window.hpp"
#include "qtlearnerview.hpp"

void QtLearnerView::showCard(const CardParams &card)
{
    LearnWindow window(controller, card);
    window.exec();
}

void QtLearnerView::askCard(const CardParams &card, int paramType)
{
    RepeatWindow window(controller, *this, card, paramType);
    window.exec();
}

void QtLearnerView::noCardsForLearn()
{
    InfoWindow window("Все карточки в этой колоде<br>уже изучены");
    window.exec();
}

void QtLearnerView::noCardsForRepeat()
{
    InfoWindow window("Нет карточек<br>для повторения");
    window.show();
}

void QtLearnerView::setController(std::shared_ptr<LearnerController> newController)
{
    controller = newController;
}
