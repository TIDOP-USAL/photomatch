/********************************************************************************
** Form generated from reading UI file 'AboutFME.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTFME_H
#define UI_ABOUTFME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_AboutFME
{
public:

    void setupUi(QDialog *AboutFME)
    {
        if (AboutFME->objectName().isEmpty())
            AboutFME->setObjectName(QStringLiteral("AboutFME"));
        AboutFME->resize(400, 300);

        retranslateUi(AboutFME);

        QMetaObject::connectSlotsByName(AboutFME);
    } // setupUi

    void retranslateUi(QDialog *AboutFME)
    {
        AboutFME->setWindowTitle(QApplication::translate("AboutFME", "Dialog", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class AboutFME: public Ui_AboutFME {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTFME_H
