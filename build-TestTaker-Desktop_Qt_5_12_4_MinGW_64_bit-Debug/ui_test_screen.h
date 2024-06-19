/********************************************************************************
** Form generated from reading UI file 'test_screen.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEST_SCREEN_H
#define UI_TEST_SCREEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Test_screen
{
public:

    void setupUi(QWidget *Test_screen)
    {
        if (Test_screen->objectName().isEmpty())
            Test_screen->setObjectName(QString::fromUtf8("Test_screen"));
        Test_screen->resize(400, 300);

        retranslateUi(Test_screen);

        QMetaObject::connectSlotsByName(Test_screen);
    } // setupUi

    void retranslateUi(QWidget *Test_screen)
    {
        Test_screen->setWindowTitle(QApplication::translate("Test_screen", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Test_screen: public Ui_Test_screen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEST_SCREEN_H
