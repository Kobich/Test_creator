#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mainScreen(new Main_screen(this)),
    testScreen(nullptr),
    resultScreen(nullptr)
{
    ui->setupUi(this);
    setCentralWidget(mainScreen);

    connect(mainScreen, &Main_screen::startTestClicked, this, &MainWindow::startTest);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startTest(int timeTest, const QSqlDatabase &db)
{

    testScreen = new Test_screen(db, this, timeTest);
    setCentralWidget(testScreen);
    connect(testScreen, &Test_screen::testCompleted, this, &MainWindow::showResults);
}

void MainWindow::showResults(QMap<QString, float> score)
{


    resultScreen = new Result_screen(this, score);
    setCentralWidget(resultScreen);
    connect(resultScreen, &Result_screen::createNewMainScreen, this, &MainWindow::takeNewTest);
}

void MainWindow::takeNewTest()
{

    mainScreen = new Main_screen(this);
    setCentralWidget(mainScreen);
    connect(mainScreen, &Main_screen::startTestClicked, this, &MainWindow::startTest);
}
