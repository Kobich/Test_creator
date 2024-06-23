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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Test_screen
{
public:
    QGridLayout *gridLayout;
    QLabel *timerLabel;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout;

    void setupUi(QWidget *Test_screen)
    {
        if (Test_screen->objectName().isEmpty())
            Test_screen->setObjectName(QString::fromUtf8("Test_screen"));
        Test_screen->resize(835, 518);
        gridLayout = new QGridLayout(Test_screen);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(-1, 9, -1, 0);
        timerLabel = new QLabel(Test_screen);
        timerLabel->setObjectName(QString::fromUtf8("timerLabel"));
        timerLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(timerLabel, 0, 0, 1, 1);

        scrollArea = new QScrollArea(Test_screen);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 817, 490));
        gridLayout_2 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setSizeConstraint(QLayout::SetMinAndMaxSize);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
        verticalLayout->setContentsMargins(-1, -1, -1, 9);

        gridLayout_2->addLayout(verticalLayout, 0, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout->addWidget(scrollArea, 1, 0, 1, 1);


        retranslateUi(Test_screen);

        QMetaObject::connectSlotsByName(Test_screen);
    } // setupUi

    void retranslateUi(QWidget *Test_screen)
    {
        Test_screen->setWindowTitle(QApplication::translate("Test_screen", "Form", nullptr));
        timerLabel->setText(QApplication::translate("Test_screen", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Test_screen: public Ui_Test_screen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEST_SCREEN_H
