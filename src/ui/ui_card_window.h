/********************************************************************************
** Form generated from reading UI file 'card_windowJoZVgC.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef CARD_WINDOWJOZVGC_H
#define CARD_WINDOWJOZVGC_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CardWindow
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *symbolLineEdit;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *readingLineEdit;
    QTextEdit *translationLineEdit;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *applyButton;
    QPushButton *discardButton;

    void setupUi(QDialog *CardWindow)
    {
        if (CardWindow->objectName().isEmpty())
            CardWindow->setObjectName(QString::fromUtf8("CardWindow"));
        CardWindow->resize(320, 185);
        verticalLayout = new QVBoxLayout(CardWindow);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(CardWindow);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        symbolLineEdit = new QLineEdit(CardWindow);
        symbolLineEdit->setObjectName(QString::fromUtf8("symbolLineEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, symbolLineEdit);

        label_2 = new QLabel(CardWindow);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        label_3 = new QLabel(CardWindow);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        readingLineEdit = new QLineEdit(CardWindow);
        readingLineEdit->setObjectName(QString::fromUtf8("readingLineEdit"));

        formLayout->setWidget(1, QFormLayout::FieldRole, readingLineEdit);

        translationLineEdit = new QTextEdit(CardWindow);
        translationLineEdit->setObjectName(QString::fromUtf8("translationLineEdit"));

        formLayout->setWidget(2, QFormLayout::FieldRole, translationLineEdit);


        verticalLayout->addLayout(formLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        applyButton = new QPushButton(CardWindow);
        applyButton->setObjectName(QString::fromUtf8("applyButton"));
        applyButton->setFlat(false);

        horizontalLayout->addWidget(applyButton);

        discardButton = new QPushButton(CardWindow);
        discardButton->setObjectName(QString::fromUtf8("discardButton"));

        horizontalLayout->addWidget(discardButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(CardWindow);

        applyButton->setDefault(false);


        QMetaObject::connectSlotsByName(CardWindow);
    } // setupUi

    void retranslateUi(QDialog *CardWindow)
    {
        CardWindow->setWindowTitle(QCoreApplication::translate("CardWindow", "\320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\320\275\320\270\320\265 \320\272\320\260\321\200\321\202\320\276\321\207\320\272\320\270", nullptr));
        label->setText(QCoreApplication::translate("CardWindow", "\320\235\320\260\320\277\320\270\321\201\320\260\320\275\320\270\320\265", nullptr));
        label_2->setText(QCoreApplication::translate("CardWindow", "\320\247\321\202\320\265\320\275\320\270\320\265", nullptr));
        label_3->setText(QCoreApplication::translate("CardWindow", "\320\237\320\265\321\200\320\265\320\262\320\276\320\264", nullptr));
        applyButton->setText(QCoreApplication::translate("CardWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        discardButton->setText(QCoreApplication::translate("CardWindow", "\320\236\321\202\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CardWindow: public Ui_CardWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // CARD_WINDOWJOZVGC_H
