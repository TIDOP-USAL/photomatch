/********************************************************************************
** Form generated from reading UI file 'MainWindowFME.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOWFME_H
#define UI_MAINWINDOWFME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowFME
{
public:
    QAction *actionExit;
    QAction *actionLeft_Image;
    QAction *actionRight_Image;
    QAction *actionAbout_FME;
    QAction *actionLoad;
    QAction *actionCreate;
    QAction *actionRobust_matches;
    QAction *actionCorrect_matches;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuLoad;
    QMenu *menuExport;
    QMenu *menuHelp;
    QMenu *menuTools;
    QMenu *menuGround_truth;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindowFME)
    {
        if (MainWindowFME->objectName().isEmpty())
            MainWindowFME->setObjectName(QStringLiteral("MainWindowFME"));
        MainWindowFME->resize(400, 300);
        actionExit = new QAction(MainWindowFME);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionLeft_Image = new QAction(MainWindowFME);
        actionLeft_Image->setObjectName(QStringLiteral("actionLeft_Image"));
        actionRight_Image = new QAction(MainWindowFME);
        actionRight_Image->setObjectName(QStringLiteral("actionRight_Image"));
        actionAbout_FME = new QAction(MainWindowFME);
        actionAbout_FME->setObjectName(QStringLiteral("actionAbout_FME"));
        actionLoad = new QAction(MainWindowFME);
        actionLoad->setObjectName(QStringLiteral("actionLoad"));
        actionCreate = new QAction(MainWindowFME);
        actionCreate->setObjectName(QStringLiteral("actionCreate"));
        actionRobust_matches = new QAction(MainWindowFME);
        actionRobust_matches->setObjectName(QStringLiteral("actionRobust_matches"));
        actionCorrect_matches = new QAction(MainWindowFME);
        actionCorrect_matches->setObjectName(QStringLiteral("actionCorrect_matches"));
        centralWidget = new QWidget(MainWindowFME);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MainWindowFME->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindowFME);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuLoad = new QMenu(menuFile);
        menuLoad->setObjectName(QStringLiteral("menuLoad"));
        menuExport = new QMenu(menuFile);
        menuExport->setObjectName(QStringLiteral("menuExport"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QStringLiteral("menuTools"));
        menuGround_truth = new QMenu(menuTools);
        menuGround_truth->setObjectName(QStringLiteral("menuGround_truth"));
        MainWindowFME->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindowFME);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindowFME->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuTools->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(menuLoad->menuAction());
        menuFile->addAction(menuExport->menuAction());
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuLoad->addAction(actionLeft_Image);
        menuLoad->addAction(actionRight_Image);
        menuExport->addAction(actionRobust_matches);
        menuExport->addAction(actionCorrect_matches);
        menuHelp->addAction(actionAbout_FME);
        menuTools->addAction(menuGround_truth->menuAction());
        menuGround_truth->addAction(actionLoad);
        menuGround_truth->addAction(actionCreate);

        retranslateUi(MainWindowFME);

        QMetaObject::connectSlotsByName(MainWindowFME);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowFME)
    {
        MainWindowFME->setWindowTitle(QApplication::translate("MainWindowFME", "MainWindowFME", Q_NULLPTR));
        actionExit->setText(QApplication::translate("MainWindowFME", "Exit", Q_NULLPTR));
        actionLeft_Image->setText(QApplication::translate("MainWindowFME", "Left Image", Q_NULLPTR));
        actionRight_Image->setText(QApplication::translate("MainWindowFME", "Right Image", Q_NULLPTR));
        actionAbout_FME->setText(QApplication::translate("MainWindowFME", "About FME.", Q_NULLPTR));
        actionLoad->setText(QApplication::translate("MainWindowFME", "Load", Q_NULLPTR));
        actionCreate->setText(QApplication::translate("MainWindowFME", "Create", Q_NULLPTR));
        actionRobust_matches->setText(QApplication::translate("MainWindowFME", "Robust matches", Q_NULLPTR));
        actionCorrect_matches->setText(QApplication::translate("MainWindowFME", "Correct matches", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("MainWindowFME", "File", Q_NULLPTR));
        menuLoad->setTitle(QApplication::translate("MainWindowFME", "Load", Q_NULLPTR));
        menuExport->setTitle(QApplication::translate("MainWindowFME", "Export", Q_NULLPTR));
        menuHelp->setTitle(QApplication::translate("MainWindowFME", "Help", Q_NULLPTR));
        menuTools->setTitle(QApplication::translate("MainWindowFME", "Tools", Q_NULLPTR));
        menuGround_truth->setTitle(QApplication::translate("MainWindowFME", "Ground truth", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindowFME: public Ui_MainWindowFME {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOWFME_H
