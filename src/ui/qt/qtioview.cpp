#include <QMessageBox>
#include "qtioview.hpp"

void QtIOView::setEditorController(std::shared_ptr<EditorController> newController)
{
    controller = newController;
}

void QtIOView::showImportedCollection(const CollectionParams &params)
{
    QMessageBox(QMessageBox::Icon::Information, "Импорт", "Коллекция успешно импортирована.").exec();
    controller->editCollection();
}

void QtIOView::showExportStatus(bool success)
{
    if (success)
        QMessageBox(QMessageBox::Icon::Information, "Экспорт", "Коллекция успешно экспортирована.").exec();
    else
        QMessageBox(QMessageBox::Icon::Critical, "Экспорт", "Не удалось экспортировать коллекцию.").exec();
}
