/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *host_name;
    QLineEdit *port;
    QPushButton *connect;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(800, 480);
        verticalLayout = new QVBoxLayout(Dialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        host_name = new QLineEdit(Dialog);
        host_name->setObjectName(QStringLiteral("host_name"));

        horizontalLayout->addWidget(host_name);

        port = new QLineEdit(Dialog);
        port->setObjectName(QStringLiteral("port"));

        horizontalLayout->addWidget(port);


        verticalLayout->addLayout(horizontalLayout);

        connect = new QPushButton(Dialog);
        connect->setObjectName(QStringLiteral("connect"));

        verticalLayout->addWidget(connect);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", Q_NULLPTR));
        host_name->setText(QApplication::translate("Dialog", "192.168.43.156", Q_NULLPTR));
        host_name->setPlaceholderText(QApplication::translate("Dialog", "IP\345\234\260\345\235\200", Q_NULLPTR));
        port->setText(QApplication::translate("Dialog", "6964", Q_NULLPTR));
        port->setPlaceholderText(QApplication::translate("Dialog", "\347\253\257\345\217\243", Q_NULLPTR));
        connect->setText(QApplication::translate("Dialog", "\350\277\236\346\216\245", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
