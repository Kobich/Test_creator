#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "main_screen.h"
#include "test_screen.h"
#include "result_screen.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void startTest(int timeTest, const QSqlDatabase &db);
    void showResults(QMap<QString, float> score);
    void takeNewTest();

private:
    Ui::MainWindow *ui;
    Main_screen *mainScreen;
    Test_screen *testScreen;
    Result_screen *resultScreen;
};

#endif // MAINWINDOW_H
