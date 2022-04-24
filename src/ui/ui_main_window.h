/********************************************************************************
** Form generated from reading UI file 'main_windowqWDhFI.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef MAIN_WINDOWQWDHFI_H
#define MAIN_WINDOWQWDHFI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QListWidget *decksList;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QPushButton *learnDeckButton;
    QPushButton *repeatDeckButton;
    QPushButton *deleteDeckButton;
    QPushButton *editDeckButton;
    QPushButton *addDeckButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        decksList = new QListWidget(groupBox);
        decksList->setObjectName(QString::fromUtf8("decksList"));

        verticalLayout->addWidget(decksList);


        horizontalLayout->addWidget(groupBox);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        learnDeckButton = new QPushButton(centralwidget);
        learnDeckButton->setObjectName(QString::fromUtf8("learnDeckButton"));

        verticalLayout_2->addWidget(learnDeckButton);

        repeatDeckButton = new QPushButton(centralwidget);
        repeatDeckButton->setObjectName(QString::fromUtf8("repeatDeckButton"));

        verticalLayout_2->addWidget(repeatDeckButton);

        deleteDeckButton = new QPushButton(centralwidget);
        deleteDeckButton->setObjectName(QString::fromUtf8("deleteDeckButton"));

        verticalLayout_2->addWidget(deleteDeckButton);

        editDeckButton = new QPushButton(centralwidget);
        editDeckButton->setObjectName(QString::fromUtf8("editDeckButton"));

        verticalLayout_2->addWidget(editDeckButton);

        addDeckButton = new QPushButton(centralwidget);
        addDeckButton->setObjectName(QString::fromUtf8("addDeckButton"));

        verticalLayout_2->addWidget(addDeckButton);


        horizontalLayout->addLayout(verticalLayout_2);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\320\234\320\276\320\264\321\203\320\273\320\270", nullptr));
        learnDeckButton->setText(QCoreApplication::translate("MainWindow", "\320\230\320\267\321\203\321\207\320\270\321\202\321\214 \320\274\320\276\320\264\321\203\320\273\321\214", nullptr));
        repeatDeckButton->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\262\321\202\320\276\321\200\320\270\321\202\321\214 \320\274\320\276\320\264\321\203\320\273\321\214", nullptr));
        deleteDeckButton->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\274\320\276\320\264\321\203\320\273\321\214", nullptr));
        editDeckButton->setText(QCoreApplication::translate("MainWindow", "\320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\274\320\276\320\264\321\203\320\273\321\214", nullptr));
        addDeckButton->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\274\320\276\320\264\321\203\320\273\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MAIN_WINDOWQWDHFI_H
