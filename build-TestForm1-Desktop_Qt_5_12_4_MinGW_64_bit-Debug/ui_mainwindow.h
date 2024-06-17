/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSaveAs;
    QAction *actionOpen;
    QAction *actionCreate;
    QAction *actionSave;
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *assessment;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *labelFor3;
    QTextEdit *textEditFor3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *labelFor4;
    QTextEdit *textEditFor4;
    QHBoxLayout *horizontalLayout_5;
    QLabel *labelFor5;
    QTextEdit *textEditFor5;
    QSpacerItem *verticalSpacer_2;
    QLabel *labelForTime;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QTextEdit *timeOfTest;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;
    QPushButton *addQuestionButton;
    QPushButton *addOpenQuestionButton;
    QMenuBar *menuBar;
    QMenu *menu31331;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(916, 752);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(12);
        MainWindow->setFont(font);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        MainWindow->setIconSize(QSize(32, 32));
        actionSaveAs = new QAction(MainWindow);
        actionSaveAs->setObjectName(QString::fromUtf8("actionSaveAs"));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionCreate = new QAction(MainWindow);
        actionCreate->setObjectName(QString::fromUtf8("actionCreate"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setSizeConstraint(QLayout::SetMinAndMaxSize);
        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy1);
        scrollArea->setFocusPolicy(Qt::WheelFocus);
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 898, 681));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(scrollAreaWidgetContents->sizePolicy().hasHeightForWidth());
        scrollAreaWidgetContents->setSizePolicy(sizePolicy2);
        gridLayout = new QGridLayout(scrollAreaWidgetContents);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
        gridLayout->setContentsMargins(-1, -1, -1, 9);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetMinAndMaxSize);
        verticalLayout_2->setContentsMargins(-1, 0, -1, 9);
        assessment = new QLabel(scrollAreaWidgetContents);
        assessment->setObjectName(QString::fromUtf8("assessment"));
        assessment->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(assessment);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout->setContentsMargins(-1, 15, -1, -1);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setSizeConstraint(QLayout::SetMinimumSize);
        labelFor3 = new QLabel(scrollAreaWidgetContents);
        labelFor3->setObjectName(QString::fromUtf8("labelFor3"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(labelFor3->sizePolicy().hasHeightForWidth());
        labelFor3->setSizePolicy(sizePolicy3);

        horizontalLayout_3->addWidget(labelFor3);

        textEditFor3 = new QTextEdit(scrollAreaWidgetContents);
        textEditFor3->setObjectName(QString::fromUtf8("textEditFor3"));
        QSizePolicy sizePolicy4(QSizePolicy::Maximum, QSizePolicy::Ignored);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(textEditFor3->sizePolicy().hasHeightForWidth());
        textEditFor3->setSizePolicy(sizePolicy4);
        textEditFor3->setMinimumSize(QSize(0, 40));

        horizontalLayout_3->addWidget(textEditFor3);


        horizontalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setSizeConstraint(QLayout::SetMinimumSize);
        labelFor4 = new QLabel(scrollAreaWidgetContents);
        labelFor4->setObjectName(QString::fromUtf8("labelFor4"));
        sizePolicy3.setHeightForWidth(labelFor4->sizePolicy().hasHeightForWidth());
        labelFor4->setSizePolicy(sizePolicy3);

        horizontalLayout_4->addWidget(labelFor4);

        textEditFor4 = new QTextEdit(scrollAreaWidgetContents);
        textEditFor4->setObjectName(QString::fromUtf8("textEditFor4"));
        sizePolicy4.setHeightForWidth(textEditFor4->sizePolicy().hasHeightForWidth());
        textEditFor4->setSizePolicy(sizePolicy4);
        textEditFor4->setMinimumSize(QSize(0, 40));

        horizontalLayout_4->addWidget(textEditFor4);


        horizontalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setSizeConstraint(QLayout::SetMinimumSize);
        labelFor5 = new QLabel(scrollAreaWidgetContents);
        labelFor5->setObjectName(QString::fromUtf8("labelFor5"));
        sizePolicy3.setHeightForWidth(labelFor5->sizePolicy().hasHeightForWidth());
        labelFor5->setSizePolicy(sizePolicy3);

        horizontalLayout_5->addWidget(labelFor5);

        textEditFor5 = new QTextEdit(scrollAreaWidgetContents);
        textEditFor5->setObjectName(QString::fromUtf8("textEditFor5"));
        sizePolicy4.setHeightForWidth(textEditFor5->sizePolicy().hasHeightForWidth());
        textEditFor5->setSizePolicy(sizePolicy4);
        textEditFor5->setMinimumSize(QSize(0, 40));

        horizontalLayout_5->addWidget(textEditFor5);


        horizontalLayout->addLayout(horizontalLayout_5);


        verticalLayout_2->addLayout(horizontalLayout);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_2);

        labelForTime = new QLabel(scrollAreaWidgetContents);
        labelForTime->setObjectName(QString::fromUtf8("labelForTime"));
        labelForTime->setMinimumSize(QSize(60, 0));
        labelForTime->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(labelForTime);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        timeOfTest = new QTextEdit(scrollAreaWidgetContents);
        timeOfTest->setObjectName(QString::fromUtf8("timeOfTest"));
        QSizePolicy sizePolicy5(QSizePolicy::Expanding, QSizePolicy::Ignored);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(timeOfTest->sizePolicy().hasHeightForWidth());
        timeOfTest->setSizePolicy(sizePolicy5);
        timeOfTest->setMinimumSize(QSize(100, 40));

        horizontalLayout_2->addWidget(timeOfTest);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_2);


        gridLayout->addLayout(verticalLayout_2, 4, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);

        gridLayout->addItem(verticalSpacer, 9, 0, 1, 1);

        addQuestionButton = new QPushButton(scrollAreaWidgetContents);
        addQuestionButton->setObjectName(QString::fromUtf8("addQuestionButton"));
        addQuestionButton->setEnabled(true);
        addQuestionButton->setMinimumSize(QSize(0, 0));
        QFont font1;
        font1.setPointSize(14);
        font1.setItalic(false);
        addQuestionButton->setFont(font1);

        gridLayout->addWidget(addQuestionButton, 7, 0, 1, 1);

        addOpenQuestionButton = new QPushButton(scrollAreaWidgetContents);
        addOpenQuestionButton->setObjectName(QString::fromUtf8("addOpenQuestionButton"));
        QFont font2;
        font2.setPointSize(14);
        addOpenQuestionButton->setFont(font2);

        gridLayout->addWidget(addOpenQuestionButton, 6, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout_2->addWidget(scrollArea, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 916, 21));
        menu31331 = new QMenu(menuBar);
        menu31331->setObjectName(QString::fromUtf8("menu31331"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu31331->menuAction());
        menu31331->addSeparator();
        menu31331->addAction(actionCreate);
        menu31331->addAction(actionSaveAs);
        menu31331->addAction(actionSave);
        menu31331->addAction(actionOpen);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionSaveAs->setText(QApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\272\320\260\320\272", nullptr));
        actionOpen->setText(QApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214 ", nullptr));
        actionCreate->setText(QApplication::translate("MainWindow", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214 \320\275\320\276\320\262\321\213\320\271", nullptr));
        actionSave->setText(QApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        assessment->setText(QApplication::translate("MainWindow", "\320\236\321\206\320\265\320\275\320\272\320\270 \320\262 \321\201\320\276\320\276\321\202\320\262\320\265\321\202\321\201\321\202\320\262\320\270\320\270 \321\201 \320\261\320\260\320\273\320\273\320\260\320\274\320\270, %", nullptr));
        labelFor3->setText(QApplication::translate("MainWindow", "\320\243\320\264\320\276\320\262\320\273\320\265\321\202\320\262\320\276\321\200\320\270\321\202\320\265\320\273\321\214\320\275\320\276", nullptr));
        labelFor4->setText(QApplication::translate("MainWindow", "                     \320\245\320\276\321\200\320\276\321\210\320\276", nullptr));
        labelFor5->setText(QApplication::translate("MainWindow", "                     \320\236\321\202\320\273\320\270\321\207\320\275\320\276", nullptr));
        labelForTime->setText(QApplication::translate("MainWindow", "\320\222\321\200\320\265\320\274\321\217 \320\262\321\213\320\277\320\276\320\273\320\275\320\265\320\275\320\270\321\217 \321\202\320\265\321\201\321\202\320\260, \320\274\320\270\320\275\321\203\321\202\321\213", nullptr));
        addQuestionButton->setText(QApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\262\320\276\320\277\321\200\320\276\321\201", nullptr));
        addOpenQuestionButton->setText(QApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\262\320\276\320\277\321\200\320\276\321\201 \321\201 \320\276\321\202\320\272\321\200\321\213\321\202\321\213\320\274 \321\202\320\265\320\272\321\201\321\202\320\276\320\274", nullptr));
        menu31331->setTitle(QApplication::translate("MainWindow", "\320\244\320\260\320\271\320\273", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
