/********************************************************************************
** Form generated from reading UI file 'learn_windowhODCuo.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef LEARN_WINDOWHODCUO_H
#define LEARN_WINDOWHODCUO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_LearnWindow
{
public:
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QFrame *line;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout;
    QLabel *symbolLabel;
    QLabel *readingLabel;
    QSpacerItem *verticalSpacer_2;
    QLabel *descriptionLabel;
    QSpacerItem *verticalSpacer_3;
    QFrame *line_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *LearnWindow)
    {
        if (LearnWindow->objectName().isEmpty())
            LearnWindow->setObjectName(QString::fromUtf8("LearnWindow"));
        LearnWindow->resize(480, 320);
        verticalLayout_2 = new QVBoxLayout(LearnWindow);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label = new QLabel(LearnWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label);

        line = new QFrame(LearnWindow);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        symbolLabel = new QLabel(LearnWindow);
        symbolLabel->setObjectName(QString::fromUtf8("symbolLabel"));
        QFont font;
        font.setPointSize(24);
        font.setBold(true);
        font.setWeight(75);
        font.setKerning(true);
        font.setStyleStrategy(QFont::PreferDefault);
        symbolLabel->setFont(font);
        symbolLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(symbolLabel);

        readingLabel = new QLabel(LearnWindow);
        readingLabel->setObjectName(QString::fromUtf8("readingLabel"));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(false);
        font1.setWeight(50);
        font1.setKerning(true);
        font1.setStyleStrategy(QFont::PreferDefault);
        readingLabel->setFont(font1);
        readingLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(readingLabel);


        verticalLayout_2->addLayout(verticalLayout);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        descriptionLabel = new QLabel(LearnWindow);
        descriptionLabel->setObjectName(QString::fromUtf8("descriptionLabel"));
        descriptionLabel->setFont(font1);
        descriptionLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(descriptionLabel);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_3);

        line_2 = new QFrame(LearnWindow);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(LearnWindow);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(LearnWindow);

        QMetaObject::connectSlotsByName(LearnWindow);
    } // setupUi

    void retranslateUi(QDialog *LearnWindow)
    {
        LearnWindow->setWindowTitle(QCoreApplication::translate("LearnWindow", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("LearnWindow", "\320\235\320\276\320\262\320\260\321\217 \320\272\320\260\321\200\321\202\320\276\321\207\320\272\320\260 \320\264\320\273\321\217 \320\270\320\267\321\203\321\207\320\265\320\275\320\270\321\217", nullptr));
        symbolLabel->setText(QCoreApplication::translate("LearnWindow", "<<\320\235\320\260\320\277\320\270\321\201\320\260\320\275\320\270\320\265>>", nullptr));
        readingLabel->setText(QCoreApplication::translate("LearnWindow", "<<\320\247\321\202\320\265\320\275\320\270\320\265>>", nullptr));
        descriptionLabel->setText(QCoreApplication::translate("LearnWindow", "<<\320\237\320\265\321\200\320\265\320\262\320\276\320\264>>", nullptr));
        pushButton->setText(QCoreApplication::translate("LearnWindow", "\320\227\320\260\320\277\320\276\320\274\320\275\320\270\320\273(-\320\260)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LearnWindow: public Ui_LearnWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // LEARN_WINDOWHODCUO_H
