#ifndef TEST_SCREEN_H
#define TEST_SCREEN_H

#include <QWidget>

namespace Ui {
class Test_screen;
}

class Test_screen : public QWidget
{
    Q_OBJECT

public:
    explicit Test_screen(QWidget *parent = nullptr);
    ~Test_screen();

private:
    Ui::Test_screen *ui;
};

#endif // TEST_SCREEN_H
