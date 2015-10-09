/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNewUser;
    QAction *actionAdd_User;
    QWidget *centralWidget;
    QLineEdit *numberEntry;
    QTextBrowser *log;
    QLabel *label;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menuFile;

    QTextBrowser *textBrowserErrors;
    QLabel *labelErrors;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(568, 442);
        actionNewUser = new QAction(MainWindow);
        actionNewUser->setObjectName(QStringLiteral("actionNewUser"));
        actionAdd_User = new QAction(MainWindow);
        actionAdd_User->setObjectName(QStringLiteral("actionAdd_User"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        numberEntry = new QLineEdit(centralWidget);
        numberEntry->setObjectName(QStringLiteral("numberEntry"));
        numberEntry->setGeometry(QRect(210, 280, 161, 21));
        log = new QTextBrowser(centralWidget);
        log->setObjectName(QStringLiteral("log"));
        log->setGeometry(QRect(30, 70, 511, 191));
        textBrowserErrors = new QTextBrowser(centralWidget);
        textBrowserErrors->setObjectName(QStringLiteral("textBrowserErrors"));
        textBrowserErrors->setGeometry(QRect(30, 330, 511, 61));
        QFont font;
        font.setFamily(QStringLiteral("Times New Roman"));
        font.setPointSize(10);
        log->setFont(font);
        textBrowserErrors->setFont(font);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 20, 551, 21));
        labelErrors = new QLabel(centralWidget);
        labelErrors->setObjectName(QStringLiteral("labelErrors"));
        labelErrors->setGeometry(40, 310, 59, 16);
        QFont font1;
        font1.setFamily(QStringLiteral("Times New Roman"));
        font1.setPointSize(24);
        label->setFont(font1);
        label->setAlignment(Qt::AlignCenter);
        QFont font2;
        font2.setFamily(QStringLiteral("Times New Roman"));
        font2.setPointSize(16);
        labelErrors->setFont(font2);
        labelErrors->setAlignment(Qt::AlignCenter);
        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        statusBar->setSizeGripEnabled(true);
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 568, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionAdd_User);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionNewUser->setText(QApplication::translate("MainWindow", "Add New User", 0));
        actionAdd_User->setText(QApplication::translate("MainWindow", "Add User", 0));
        label->setText(QApplication::translate("MainWindow", "Attendance", 0));
        labelErrors->setText(QApplication::translate("MainWindow", "Errors", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
