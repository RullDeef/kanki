#include <iostream>
#include "ioview.hpp"

void cli::IOView::showImportedCollection(const CollectionParams &params)
{
    std::cout << "Импортирована колода\n";
}

void cli::IOView::showExportStatus(bool success)
{
    std::cout << "Колода экспортирована успешно!\n";
}
