#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    a.setWindowIcon(QIcon(":/image/icon.png"));


    QFile file(":/style.css");
    file.open(QFile::ReadOnly);
    a.setStyleSheet(file.readAll());
    MainWindow w;

    w.setWindowIcon(QIcon(":/image/icon.png"));

    w.setWindowTitle(" ");

    w.show();

    return a.exec();
}
