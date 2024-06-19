#include "test_screen.h"
#include "ui_test_screen.h"

Test_screen::Test_screen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Test_screen)
{
    ui->setupUi(this);
}

Test_screen::~Test_screen()
{
    delete ui;
}
