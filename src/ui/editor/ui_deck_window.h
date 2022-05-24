/********************************************************************************
** Form generated from reading UI file 'deck_windowndviIu.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef DECK_WINDOWNDVIIU_H
#define DECK_WINDOWNDVIIU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DeckWindow
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label_2;
    QLineEdit *deckNameEdit;
    QFrame *line_2;
    QLabel *label;
    QListWidget *cardListWidget;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QPushButton *addCardButton;
    QPushButton *editCardButton;
    QPushButton *deleteCardButton;
    QFrame *line;
    QPushButton *applyChangesButton;
    QPushButton *discardChangesButton;

    void setupUi(QDialog *DeckWindow)
    {
        if (DeckWindow->objectName().isEmpty())
            DeckWindow->setObjectName(QString::fromUtf8("DeckWindow"));
        DeckWindow->resize(625, 392);
        horizontalLayout = new QHBoxLayout(DeckWindow);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label_2 = new QLabel(DeckWindow);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_2);

        deckNameEdit = new QLineEdit(DeckWindow);
        deckNameEdit->setObjectName(QString::fromUtf8("deckNameEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, deckNameEdit);


        verticalLayout->addLayout(formLayout);

        line_2 = new QFrame(DeckWindow);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);

        label = new QLabel(DeckWindow);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        cardListWidget = new QListWidget(DeckWindow);
        cardListWidget->setObjectName(QString::fromUtf8("cardListWidget"));

        verticalLayout->addWidget(cardListWidget);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        addCardButton = new QPushButton(DeckWindow);
        addCardButton->setObjectName(QString::fromUtf8("addCardButton"));

        verticalLayout_2->addWidget(addCardButton);

        editCardButton = new QPushButton(DeckWindow);
        editCardButton->setObjectName(QString::fromUtf8("editCardButton"));

        verticalLayout_2->addWidget(editCardButton);

        deleteCardButton = new QPushButton(DeckWindow);
        deleteCardButton->setObjectName(QString::fromUtf8("deleteCardButton"));

        verticalLayout_2->addWidget(deleteCardButton);

        line = new QFrame(DeckWindow);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line);

        applyChangesButton = new QPushButton(DeckWindow);
        applyChangesButton->setObjectName(QString::fromUtf8("applyChangesButton"));

        verticalLayout_2->addWidget(applyChangesButton);

        discardChangesButton = new QPushButton(DeckWindow);
        discardChangesButton->setObjectName(QString::fromUtf8("discardChangesButton"));

        verticalLayout_2->addWidget(discardChangesButton);


        horizontalLayout->addLayout(verticalLayout_2);


        retranslateUi(DeckWindow);

        QMetaObject::connectSlotsByName(DeckWindow);
    } // setupUi

    void retranslateUi(QDialog *DeckWindow)
    {
        DeckWindow->setWindowTitle(QCoreApplication::translate("DeckWindow", "\320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\320\275\320\270\320\265 \320\274\320\276\320\264\321\203\320\273\321\217", nullptr));
        label_2->setText(QCoreApplication::translate("DeckWindow", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265 \320\274\320\276\320\264\321\203\320\273\321\217", nullptr));
        label->setText(QCoreApplication::translate("DeckWindow", "\320\241\320\277\320\270\321\201\320\276\320\272 \320\272\320\260\321\200\321\202\320\276\321\207\320\265\320\272", nullptr));
        addCardButton->setText(QCoreApplication::translate("DeckWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\272\320\260\321\200\321\202\320\276\321\207\320\272\321\203", nullptr));
        editCardButton->setText(QCoreApplication::translate("DeckWindow", "\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214 \320\272\320\260\321\200\321\202\320\276\321\207\320\272\321\203", nullptr));
        deleteCardButton->setText(QCoreApplication::translate("DeckWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\272\320\260\321\200\321\202\320\276\321\207\320\272\321\203", nullptr));
        applyChangesButton->setText(QCoreApplication::translate("DeckWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\274\320\276\320\264\321\203\320\273\321\214", nullptr));
        discardChangesButton->setText(QCoreApplication::translate("DeckWindow", "\320\236\321\202\320\274\320\265\320\275\320\270\321\202\321\214 \320\270\320\267\320\274\320\265\320\275\320\265\320\275\320\270\321\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DeckWindow: public Ui_DeckWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // DECK_WINDOWNDVIIU_H
