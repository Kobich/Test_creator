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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Result_screen
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QTextEdit *textEdit;
    QTextEdit *textEdit_2;

    void setupUi(QWidget *Result_screen)
    {
        if (Result_screen->objectName().isEmpty())
            Result_screen->setObjectName(QString::fromUtf8("Result_screen"));
        Result_screen->resize(371, 170);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Result_screen->sizePolicy().hasHeightForWidth());
        Result_screen->setSizePolicy(sizePolicy);
        horizontalLayoutWidget = new QWidget(Result_screen);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(390, 140, 335, 61));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        textEdit = new QTextEdit(horizontalLayoutWidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(textEdit->sizePolicy().hasHeightForWidth());
        textEdit->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(textEdit);

        textEdit_2 = new QTextEdit(horizontalLayoutWidget);
        textEdit_2->setObjectName(QString::fromUtf8("textEdit_2"));
        sizePolicy1.setHeightForWidth(textEdit_2->sizePolicy().hasHeightForWidth());
        textEdit_2->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(textEdit_2);


        retranslateUi(Result_screen);

        QMetaObject::connectSlotsByName(Result_screen);
    } // setupUi

    void retranslateUi(QWidget *Result_screen)
    {
        Result_screen->setWindowTitle(QApplication::translate("Result_screen", "Form", nullptr));
        textEdit->setHtml(QApplication::translate("Result_screen", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">ggrgrgrgrgrgr</p></body></html>", nullptr));
        textEdit_2->setHtml(QApplication::translate("Result_screen", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"> h hj h jh h jh h </p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Result_screen: public Ui_Result_screen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESULT_SCREEN_H
