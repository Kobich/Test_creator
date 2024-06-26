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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Result_screen
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer_2;
    QLabel *endLabel;
    QLabel *endLabel_2;
    QLabel *finalScoreLabel;
    QLabel *markLabel;
    QSpacerItem *verticalSpacer_3;
    QPushButton *mainScreenButton;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *Result_screen)
    {
        if (Result_screen->objectName().isEmpty())
            Result_screen->setObjectName(QString::fromUtf8("Result_screen"));
        Result_screen->resize(798, 506);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Result_screen->sizePolicy().hasHeightForWidth());
        Result_screen->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(Result_screen);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, -1, -1, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, -1, -1, 0);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setSizeConstraint(QLayout::SetMinAndMaxSize);
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        endLabel = new QLabel(Result_screen);
        endLabel->setObjectName(QString::fromUtf8("endLabel"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(endLabel->sizePolicy().hasHeightForWidth());
        endLabel->setSizePolicy(sizePolicy1);
        endLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(endLabel);

        endLabel_2 = new QLabel(Result_screen);
        endLabel_2->setObjectName(QString::fromUtf8("endLabel_2"));
        sizePolicy1.setHeightForWidth(endLabel_2->sizePolicy().hasHeightForWidth());
        endLabel_2->setSizePolicy(sizePolicy1);
        endLabel_2->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(endLabel_2);


        verticalLayout_2->addLayout(verticalLayout_3);

        finalScoreLabel = new QLabel(Result_screen);
        finalScoreLabel->setObjectName(QString::fromUtf8("finalScoreLabel"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(finalScoreLabel->sizePolicy().hasHeightForWidth());
        finalScoreLabel->setSizePolicy(sizePolicy2);
        finalScoreLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(finalScoreLabel);

        markLabel = new QLabel(Result_screen);
        markLabel->setObjectName(QString::fromUtf8("markLabel"));
        sizePolicy2.setHeightForWidth(markLabel->sizePolicy().hasHeightForWidth());
        markLabel->setSizePolicy(sizePolicy2);
        markLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(markLabel);

        verticalSpacer_3 = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_3);

        mainScreenButton = new QPushButton(Result_screen);
        mainScreenButton->setObjectName(QString::fromUtf8("mainScreenButton"));

        verticalLayout_2->addWidget(mainScreenButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        verticalLayout->addLayout(verticalLayout_2);


        horizontalLayout->addLayout(verticalLayout);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        retranslateUi(Result_screen);

        QMetaObject::connectSlotsByName(Result_screen);
    } // setupUi

    void retranslateUi(QWidget *Result_screen)
    {
        Result_screen->setWindowTitle(QApplication::translate("Result_screen", "Form", nullptr));
        endLabel->setText(QApplication::translate("Result_screen", "\320\242\320\265\321\201\321\202 \320\267\320\260\320\262\320\265\321\200\321\210\320\265\320\275.", nullptr));
        endLabel_2->setText(QApplication::translate("Result_screen", "\320\237\321\200\320\265\320\264\320\276\321\201\321\202\320\260\320\262\321\214\321\202\320\265 \321\200\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202 \320\277\321\200\320\265\320\277\320\276\320\264\320\260\320\262\320\260\321\202\320\265\320\273\321\216", nullptr));
        finalScoreLabel->setText(QApplication::translate("Result_screen", "\320\230\321\202\320\276\320\263\320\276\320\262\321\213\320\271 \320\261\320\260\320\273\320\273: ", nullptr));
        markLabel->setText(QApplication::translate("Result_screen", "\320\236\321\206\320\265\320\275\320\272\320\260: ", nullptr));
        mainScreenButton->setText(QApplication::translate("Result_screen", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Result_screen: public Ui_Result_screen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESULT_SCREEN_H
