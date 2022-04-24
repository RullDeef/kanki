#pragma once

#include <memory>
#include <string>
#include <map>
#include "viewapi/icollectionview.hpp"
#include "deckcontroller.hpp"
#include "modelmanager.hpp"

class CollectionController
{
public:
    CollectionController(ICollectionView* view, std::shared_ptr<ModelManager> modelManager);
    ~CollectionController();

    CollectionController(const CollectionController&) = delete;
    CollectionController& operator=(const CollectionController&) = delete;

    ///TODO: look for controller builders...
    std::string addDeck();
    void deleteDeck(const std::string& deckToken);

    void importCollection(const std::string& filename);
    void exportCollection(const std::string& filename);

private:
    ///TODO: avoid friendship (single place for all tokens in the system)
    friend class DeckController;
    Deck& getDeck(const std::string& deckToken);
    void confirmEditDeck();
    ///TODO: ?? void cancelNewDeck();

    ICollectionView* view;

    std::shared_ptr<ModelManager> modelManager;
    std::map<std::string, std::shared_ptr<Deck>> tokenMap;
};
