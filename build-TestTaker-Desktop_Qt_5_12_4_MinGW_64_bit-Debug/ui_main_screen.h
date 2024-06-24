/********************************************************************************
** Form generated from reading UI file 'main_screen.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_SCREEN_H
#define UI_MAIN_SCREEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Main_screen
{
public:
    QAction *actionSaveAs;
    QAction *actionOpen;
    QAction *actionCreate;
    QAction *actionSave;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_3;
    QLabel *assessment_2;
    QHBoxLayout *horizontalLayout_6;
    QHBoxLayout *horizontalLayout_7;
    QLabel *labelFor3_2;
    QTextEdit *textEditFor3_2;
    QHBoxLayout *horizontalLayout_8;
    QLabel *labelFor4_2;
    QTextEdit *textEditFor4_2;
    QHBoxLayout *horizontalLayout_9;
    QLabel *labelFor5_2;
    QTextEdit *textEditFor5_2;
    QSpacerItem *verticalSpacer_3;
    QLabel *labelForTime_2;
    QHBoxLayout *horizontalLayout_10;
    QSpacerItem *horizontalSpacer_3;
    QTextEdit *timeOfTest_2;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_11;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *chooseTestButton;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *Main_screen)
    {
        if (Main_screen->objectName().isEmpty())
            Main_screen->setObjectName(QString::fromUtf8("Main_screen"));
        Main_screen->setWindowModality(Qt::NonModal);
        Main_screen->setEnabled(true);
        Main_screen->resize(837, 518);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Main_screen->sizePolicy().hasHeightForWidth());
        Main_screen->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(12);
        Main_screen->setFont(font);
        Main_screen->setStyleSheet(QString::fromUtf8(""));
        Main_screen->setProperty("iconSize", QVariant(QSize(32, 32)));
        actionSaveAs = new QAction(Main_screen);
        actionSaveAs->setObjectName(QString::fromUtf8("actionSaveAs"));
        actionOpen = new QAction(Main_screen);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionCreate = new QAction(Main_screen);
        actionCreate->setObjectName(QString::fromUtf8("actionCreate"));
        actionSave = new QAction(Main_screen);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        gridLayout = new QGridLayout(Main_screen);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setSizeConstraint(QLayout::SetMinAndMaxSize);
        verticalLayout_3->setContentsMargins(-1, 0, -1, 9);
        assessment_2 = new QLabel(Main_screen);
        assessment_2->setObjectName(QString::fromUtf8("assessment_2"));
        assessment_2->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(assessment_2);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setSizeConstraint(QLayout::SetMinAndMaxSize);
        horizontalLayout_6->setContentsMargins(-1, 15, -1, -1);
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setSizeConstraint(QLayout::SetMinAndMaxSize);
        labelFor3_2 = new QLabel(Main_screen);
        labelFor3_2->setObjectName(QString::fromUtf8("labelFor3_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(labelFor3_2->sizePolicy().hasHeightForWidth());
        labelFor3_2->setSizePolicy(sizePolicy1);

        horizontalLayout_7->addWidget(labelFor3_2);

        textEditFor3_2 = new QTextEdit(Main_screen);
        textEditFor3_2->setObjectName(QString::fromUtf8("textEditFor3_2"));
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Ignored);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(textEditFor3_2->sizePolicy().hasHeightForWidth());
        textEditFor3_2->setSizePolicy(sizePolicy2);
        textEditFor3_2->setMinimumSize(QSize(0, 40));
        textEditFor3_2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textEditFor3_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textEditFor3_2->setReadOnly(true);
        textEditFor3_2->setTextInteractionFlags(Qt::NoTextInteraction);

        horizontalLayout_7->addWidget(textEditFor3_2);


        horizontalLayout_6->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_8->setSizeConstraint(QLayout::SetMinAndMaxSize);
        labelFor4_2 = new QLabel(Main_screen);
        labelFor4_2->setObjectName(QString::fromUtf8("labelFor4_2"));
        sizePolicy1.setHeightForWidth(labelFor4_2->sizePolicy().hasHeightForWidth());
        labelFor4_2->setSizePolicy(sizePolicy1);

        horizontalLayout_8->addWidget(labelFor4_2);

        textEditFor4_2 = new QTextEdit(Main_screen);
        textEditFor4_2->setObjectName(QString::fromUtf8("textEditFor4_2"));
        sizePolicy2.setHeightForWidth(textEditFor4_2->sizePolicy().hasHeightForWidth());
        textEditFor4_2->setSizePolicy(sizePolicy2);
        textEditFor4_2->setMinimumSize(QSize(0, 40));
        textEditFor4_2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textEditFor4_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textEditFor4_2->setReadOnly(true);
        textEditFor4_2->setTextInteractionFlags(Qt::NoTextInteraction);

        horizontalLayout_8->addWidget(textEditFor4_2);


        horizontalLayout_6->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalLayout_9->setSizeConstraint(QLayout::SetMinAndMaxSize);
        labelFor5_2 = new QLabel(Main_screen);
        labelFor5_2->setObjectName(QString::fromUtf8("labelFor5_2"));
        sizePolicy1.setHeightForWidth(labelFor5_2->sizePolicy().hasHeightForWidth());
        labelFor5_2->setSizePolicy(sizePolicy1);

        horizontalLayout_9->addWidget(labelFor5_2);

        textEditFor5_2 = new QTextEdit(Main_screen);
        textEditFor5_2->setObjectName(QString::fromUtf8("textEditFor5_2"));
        sizePolicy2.setHeightForWidth(textEditFor5_2->sizePolicy().hasHeightForWidth());
        textEditFor5_2->setSizePolicy(sizePolicy2);
        textEditFor5_2->setMinimumSize(QSize(0, 40));
        textEditFor5_2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textEditFor5_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textEditFor5_2->setTabChangesFocus(false);
        textEditFor5_2->setReadOnly(true);
        textEditFor5_2->setOverwriteMode(false);
        textEditFor5_2->setAcceptRichText(true);
        textEditFor5_2->setTextInteractionFlags(Qt::NoTextInteraction);

        horizontalLayout_9->addWidget(textEditFor5_2);


        horizontalLayout_6->addLayout(horizontalLayout_9);


        verticalLayout_3->addLayout(horizontalLayout_6);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_3->addItem(verticalSpacer_3);

        labelForTime_2 = new QLabel(Main_screen);
        labelForTime_2->setObjectName(QString::fromUtf8("labelForTime_2"));
        labelForTime_2->setMinimumSize(QSize(60, 0));
        labelForTime_2->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(labelForTime_2);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_3);

        timeOfTest_2 = new QTextEdit(Main_screen);
        timeOfTest_2->setObjectName(QString::fromUtf8("timeOfTest_2"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Ignored);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(timeOfTest_2->sizePolicy().hasHeightForWidth());
        timeOfTest_2->setSizePolicy(sizePolicy3);
        timeOfTest_2->setMinimumSize(QSize(100, 40));
        timeOfTest_2->setLayoutDirection(Qt::LeftToRight);
        timeOfTest_2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        timeOfTest_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        timeOfTest_2->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        timeOfTest_2->setReadOnly(false);
        timeOfTest_2->setTextInteractionFlags(Qt::TextEditable);

        horizontalLayout_10->addWidget(timeOfTest_2);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_4);


        verticalLayout_3->addLayout(horizontalLayout_10);


        gridLayout->addLayout(verticalLayout_3, 1, 0, 1, 1);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        horizontalLayout_11->setContentsMargins(-1, 14, -1, -1);
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_5);

        chooseTestButton = new QPushButton(Main_screen);
        chooseTestButton->setObjectName(QString::fromUtf8("chooseTestButton"));
        QSizePolicy sizePolicy4(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(chooseTestButton->sizePolicy().hasHeightForWidth());
        chooseTestButton->setSizePolicy(sizePolicy4);
        chooseTestButton->setMinimumSize(QSize(0, 0));

        horizontalLayout_11->addWidget(chooseTestButton);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_6);


        gridLayout->addLayout(horizontalLayout_11, 2, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 3, 0, 1, 1);


        retranslateUi(Main_screen);

        QMetaObject::connectSlotsByName(Main_screen);
    } // setupUi

    void retranslateUi(QWidget *Main_screen)
    {
        Main_screen->setWindowTitle(QApplication::translate("Main_screen", "MainWindow", nullptr));
        actionSaveAs->setText(QApplication::translate("Main_screen", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\272\320\260\320\272", nullptr));
        actionOpen->setText(QApplication::translate("Main_screen", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214 ", nullptr));
        actionCreate->setText(QApplication::translate("Main_screen", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214 \320\275\320\276\320\262\321\213\320\271", nullptr));
        actionSave->setText(QApplication::translate("Main_screen", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        assessment_2->setText(QApplication::translate("Main_screen", "\320\237\321\200\320\276\321\206\320\265\320\275\321\202\320\275\321\213\320\271 \320\277\320\276\321\200\320\276\320\263 \320\264\320\273\321\217 \320\277\320\276\320\273\321\203\321\207\320\265\320\275\320\270\321\217 \320\276\321\206\320\265\320\275\320\272\320\270", nullptr));
        labelFor3_2->setText(QApplication::translate("Main_screen", "\320\243\320\264\320\276\320\262\320\273\320\265\321\202\320\262\320\276\321\200\320\270\321\202\320\265\320\273\321\214\320\275\320\276", nullptr));
        labelFor4_2->setText(QApplication::translate("Main_screen", "                     \320\245\320\276\321\200\320\276\321\210\320\276", nullptr));
        labelFor5_2->setText(QApplication::translate("Main_screen", "                     \320\236\321\202\320\273\320\270\321\207\320\275\320\276", nullptr));
        labelForTime_2->setText(QApplication::translate("Main_screen", "\320\222\321\200\320\265\320\274\321\217 \320\262\321\213\320\277\320\276\320\273\320\275\320\265\320\275\320\270\321\217 \321\202\320\265\321\201\321\202\320\260, \320\274\320\270\320\275\321\203\321\202\321\213", nullptr));
        chooseTestButton->setText(QApplication::translate("Main_screen", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214 \321\202\320\265\321\201\321\202", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Main_screen: public Ui_Main_screen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_SCREEN_H
