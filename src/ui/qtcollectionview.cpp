#include <iostream>
#include "tools/logger.hpp"
#include "qtcollectionview.hpp"

void QtCollectionView::showCollection(const CollectionParams& collectionParams)
{
    emit showCollectionSignal(collectionParams);
}
