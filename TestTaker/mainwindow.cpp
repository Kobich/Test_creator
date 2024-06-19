#include "mainwindow.h"
#include "ui_mainwindow.h" // Включение сгенерированного файла

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mainScreen(new Main_screen(this)),
    testScreen(new Test_screen(this)),
    resultScreen(new Result_screen(this))
{
    ui->setupUi(this);
    setCentralWidget(mainScreen);

    //connect(mainScreen, &Main_screen::startTestClicked, this, &MainWindow::startTest);
    //connect(testScreen, &Test_screen::testCompleted, this, &MainWindow::showResults);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::startTest() {
    setCentralWidget(testScreen);
}

void MainWindow::showResults() {
    setCentralWidget(resultScreen);
}
