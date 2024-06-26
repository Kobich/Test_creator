#ifndef RESULT_SCREEN_H
#define RESULT_SCREEN_H

#include <QWidget>
#include <QMap>

namespace Ui {
class Result_screen;
}

class Result_screen : public QWidget
{
    Q_OBJECT

public:
    explicit Result_screen(QWidget *parent = nullptr, QMap<QString, float> score = QMap<QString, float>());
    ~Result_screen();
private slots:
    void on_mainScreenButton_clicked();
private:
    Ui::Result_screen *ui;
    void displayResults(const QMap<QString, float> &score);

signals:
    void createNewMainScreen();

};

#endif // RESULT_SCREEN_H
