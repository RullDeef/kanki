#pragma once

#include <QObject>
#include "viewapi/icollectionview.hpp"

class QtCollectionView : public QObject, public ICollectionView
{
    Q_OBJECT

public:
    virtual void showCollection(const CollectionParams& collectionParams) override;

signals:
    void showCollectionSignal(const CollectionParams& collectionParams);
};
