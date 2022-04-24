#pragma once

#include "deckparams.hpp"
#include "collectionparams.hpp"

class ICollectionView
{
public:
    virtual ~ICollectionView() = default;

    virtual void showCollection(const CollectionParams& collectionParams) = 0;
};
