#include "result_screen.h"
#include "ui_result_screen.h"

Result_screen::Result_screen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Result_screen)
{
    ui->setupUi(this);
}

Result_screen::~Result_screen()
{
    delete ui;
}
