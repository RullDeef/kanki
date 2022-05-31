#pragma once

#include <memory>
#include "core/editorcontroller.hpp"
#include "ui/model/uiioview.hpp"

class QtIOView : public UIIOView
{
public:
    void setEditorController(std::shared_ptr<EditorController> controller);

    virtual void showImportedCollection(const CollectionParams &params) override;
    virtual void showExportStatus(bool success) override;

private:
    std::shared_ptr<EditorController> controller;
};
