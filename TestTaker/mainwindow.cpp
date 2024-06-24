#include "mainwindow.h"
#include "ui_mainwindow.h" // Включение сгенерированного файла

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mainScreen(new Main_screen(this)),
    testScreen(nullptr), // Инициализируем как nullptr
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
    if (testScreen) {
        delete testScreen; // Удаляем предыдущий экземпляр, если он существует
    }

    testScreen = new Test_screen(db, this, timeTest);
    setCentralWidget(testScreen);
}

void MainWindow::showResults()
{
    setCentralWidget(resultScreen);
}
