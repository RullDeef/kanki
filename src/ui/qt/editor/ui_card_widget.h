/********************************************************************************
** Form generated from reading UI file 'card_widgetwKZzOW.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef CARD_WIDGETWKZZOW_H
#define CARD_WIDGETWKZZOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CardViewWidget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *symbolLabel;
    QSpacerItem *horizontalSpacer;
    QLabel *readingLabel;
    QLabel *descriptionLabel;

    void setupUi(QWidget *CardViewWidget)
    {
        if (CardViewWidget->objectName().isEmpty())
            CardViewWidget->setObjectName(QString::fromUtf8("CardViewWidget"));
        CardViewWidget->resize(244, 63);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(CardViewWidget->sizePolicy().hasHeightForWidth());
        CardViewWidget->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(CardViewWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        symbolLabel = new QLabel(CardViewWidget);
        symbolLabel->setObjectName(QString::fromUtf8("symbolLabel"));

        horizontalLayout->addWidget(symbolLabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        readingLabel = new QLabel(CardViewWidget);
        readingLabel->setObjectName(QString::fromUtf8("readingLabel"));

        horizontalLayout->addWidget(readingLabel);


        verticalLayout->addLayout(horizontalLayout);

        descriptionLabel = new QLabel(CardViewWidget);
        descriptionLabel->setObjectName(QString::fromUtf8("descriptionLabel"));

        verticalLayout->addWidget(descriptionLabel);


        retranslateUi(CardViewWidget);

        QMetaObject::connectSlotsByName(CardViewWidget);
    } // setupUi

    void retranslateUi(QWidget *CardViewWidget)
    {
        CardViewWidget->setWindowTitle(QCoreApplication::translate("CardViewWidget", "Form", nullptr));
        symbolLabel->setText(QCoreApplication::translate("CardViewWidget", "<<\320\235\320\260\320\277\320\270\321\201\320\260\320\275\320\270\320\265>>", nullptr));
        readingLabel->setText(QCoreApplication::translate("CardViewWidget", "<<\320\247\321\202\320\265\320\275\320\270\320\265>>", nullptr));
        descriptionLabel->setText(QCoreApplication::translate("CardViewWidget", "<<\320\237\320\265\321\200\320\265\320\262\320\276\320\264>>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CardViewWidget: public Ui_CardViewWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // CARD_WIDGETWKZZOW_H
