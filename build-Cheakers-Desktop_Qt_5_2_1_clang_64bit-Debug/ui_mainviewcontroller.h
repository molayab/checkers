/********************************************************************************
** Form generated from reading UI file 'mainviewcontroller.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINVIEWCONTROLLER_H
#define UI_MAINVIEWCONTROLLER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainViewController
{
public:
    QWidget *centralWidget;
    QTableView *tableView;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainViewController)
    {
        if (MainViewController->objectName().isEmpty())
            MainViewController->setObjectName(QStringLiteral("MainViewController"));
        MainViewController->resize(795, 506);
        centralWidget = new QWidget(MainViewController);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tableView = new QTableView(centralWidget);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(10, 10, 621, 431));
        MainViewController->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainViewController);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 795, 22));
        MainViewController->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainViewController);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainViewController->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainViewController);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainViewController->setStatusBar(statusBar);

        retranslateUi(MainViewController);

        QMetaObject::connectSlotsByName(MainViewController);
    } // setupUi

    void retranslateUi(QMainWindow *MainViewController)
    {
        MainViewController->setWindowTitle(QApplication::translate("MainViewController", "MainViewController", 0));
    } // retranslateUi

};

namespace Ui {
    class MainViewController: public Ui_MainViewController {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINVIEWCONTROLLER_H
