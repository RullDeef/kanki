#pragma once

#include "core/editorcontroller.hpp"
#include "view/uieditorview.hpp"

namespace cli
{
    class EditorView : public UIEditorView
    {
    public:
        void setEditorController(EditorController &newController);

        virtual void showCollection(const CollectionParams &collection) override;
        virtual void showDeck(const DeckParams &deck) override;
        virtual void showCard(const CardParams &card) override;

    private:
        EditorController *controller = nullptr;
    };
} // namespace cli
