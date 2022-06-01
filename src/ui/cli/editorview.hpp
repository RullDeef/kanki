#pragma once

#include <map>
#include <memory>
#include "core/editorcontroller.hpp"
#include "ui/model/uieditorview.hpp"

namespace cli
{
    class EditorView : public UIEditorView
    {
    public:
        void setEditorController(std::shared_ptr<EditorController> newController);

        virtual void showCollection(const CollectionParams &collection) override;
        virtual void showDeck(const DeckParams &deck) override;
        virtual void showCard(const CardParams &card) override;

        const std::map<size_t, UUID> &getDeckIdMapping() const;

    private:
        void updateDeckIdMapping(const CollectionParams& collection);
        void updateCardIdMapping(const DeckParams& deck);

        std::shared_ptr<EditorController> controller;

        std::map<size_t, UUID> deckIdMapping;
        std::map<size_t, UUID> cardIdMapping;
    };
} // namespace cli
