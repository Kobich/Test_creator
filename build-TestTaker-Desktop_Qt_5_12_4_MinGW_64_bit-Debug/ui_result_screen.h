/********************************************************************************
** Form generated from reading UI file 'result_screen.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESULT_SCREEN_H
#define UI_RESULT_SCREEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Result_screen
{
public:

    void setupUi(QWidget *Result_screen)
    {
        if (Result_screen->objectName().isEmpty())
            Result_screen->setObjectName(QString::fromUtf8("Result_screen"));
        Result_screen->resize(894, 584);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Result_screen->sizePolicy().hasHeightForWidth());
        Result_screen->setSizePolicy(sizePolicy);

        retranslateUi(Result_screen);

        QMetaObject::connectSlotsByName(Result_screen);
    } // setupUi

    void retranslateUi(QWidget *Result_screen)
    {
        Result_screen->setWindowTitle(QApplication::translate("Result_screen", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Result_screen: public Ui_Result_screen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESULT_SCREEN_H
