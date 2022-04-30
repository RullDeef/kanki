#pragma once

#include <QObject>
#include "viewapi/icardview.hpp"

class QtCardView : public QObject, public ICardView
{
    Q_OBJECT

public:
    virtual void showCard(const CardParams& cardParams) override;

signals:
    void onShowCard(const CardParams& cardParams);
};
