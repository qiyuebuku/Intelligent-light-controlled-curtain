/********************************************************************************
** Form generated from reading UI file 'conmainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONMAINWINDOW_H
#define UI_CONMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCommandLinkButton>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConMainWindow
{
public:
    QWidget *centralwidget;
    QRadioButton *radioButton;
    QCommandLinkButton *commandLinkButton;
    QTableView *tableView;
    QTreeView *treeView;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ConMainWindow)
    {
        if (ConMainWindow->objectName().isEmpty())
            ConMainWindow->setObjectName(QStringLiteral("ConMainWindow"));
        ConMainWindow->resize(800, 600);
        centralwidget = new QWidget(ConMainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        radioButton = new QRadioButton(centralwidget);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setGeometry(QRect(170, 210, 115, 19));
        commandLinkButton = new QCommandLinkButton(centralwidget);
        commandLinkButton->setObjectName(QStringLiteral("commandLinkButton"));
        commandLinkButton->setGeometry(QRect(240, 280, 187, 41));
        tableView = new QTableView(centralwidget);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(270, 370, 256, 192));
        treeView = new QTreeView(centralwidget);
        treeView->setObjectName(QStringLiteral("treeView"));
        treeView->setGeometry(QRect(580, 80, 256, 192));
        ConMainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ConMainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        ConMainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(ConMainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        ConMainWindow->setStatusBar(statusbar);

        retranslateUi(ConMainWindow);

        QMetaObject::connectSlotsByName(ConMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ConMainWindow)
    {
        ConMainWindow->setWindowTitle(QApplication::translate("ConMainWindow", "MainWindow", Q_NULLPTR));
        radioButton->setText(QApplication::translate("ConMainWindow", "RadioButton", Q_NULLPTR));
        commandLinkButton->setText(QApplication::translate("ConMainWindow", "CommandLinkButton", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ConMainWindow: public Ui_ConMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONMAINWINDOW_H
