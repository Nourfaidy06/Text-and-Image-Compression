/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QPushButton *btnBrowse;
    QPushButton *btnCompress;
    QPushButton *btnDecompress;
    QPushButton *btnPngCompress;
    QLabel *lblStats;
    QTextEdit *txtCodes;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        btnBrowse = new QPushButton(centralwidget);
        btnBrowse->setObjectName("btnBrowse");

        verticalLayout->addWidget(btnBrowse);

        btnCompress = new QPushButton(centralwidget);
        btnCompress->setObjectName("btnCompress");

        verticalLayout->addWidget(btnCompress);

        btnDecompress = new QPushButton(centralwidget);
        btnDecompress->setObjectName("btnDecompress");

        verticalLayout->addWidget(btnDecompress);

        btnPngCompress = new QPushButton(centralwidget);
        btnPngCompress->setObjectName("btnPngCompress");

        verticalLayout->addWidget(btnPngCompress);

        lblStats = new QLabel(centralwidget);
        lblStats->setObjectName("lblStats");

        verticalLayout->addWidget(lblStats);

        txtCodes = new QTextEdit(centralwidget);
        txtCodes->setObjectName("txtCodes");

        verticalLayout->addWidget(txtCodes);


        verticalLayout_2->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 17));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        btnBrowse->setText(QCoreApplication::translate("MainWindow", "Browse button", nullptr));
        btnCompress->setText(QCoreApplication::translate("MainWindow", "Compress file", nullptr));
        btnDecompress->setText(QCoreApplication::translate("MainWindow", "Decompress file", nullptr));
        btnPngCompress->setText(QCoreApplication::translate("MainWindow", "PNG Compression", nullptr));
        lblStats->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
