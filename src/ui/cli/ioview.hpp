#pragma once

#include "ui/model/uiioview.hpp"

namespace cli
{
    class IOView : public UIIOView
    {
    public:
        virtual void showImportedCollection(const CollectionParams &params) override;
        virtual void showExportStatus(bool success) override;
    };
} // namespace cli
