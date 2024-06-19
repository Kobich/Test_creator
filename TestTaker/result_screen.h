#ifndef RESULT_SCREEN_H
#define RESULT_SCREEN_H

#include <QWidget>

namespace Ui {
class Result_screen;
}

class Result_screen : public QWidget
{
    Q_OBJECT

public:
    explicit Result_screen(QWidget *parent = nullptr);
    ~Result_screen();

private:
    Ui::Result_screen *ui;
};

#endif // RESULT_SCREEN_H
