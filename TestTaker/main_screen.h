#ifndef MAIN_SCREEN_H
#define MAIN_SCREEN_H

#include <QWidget>
#include <QSqlDatabase>
#include <QPushButton>

namespace Ui {
class Main_screen;
}

class Main_screen : public QWidget
{
    Q_OBJECT

public:
    explicit Main_screen(QWidget *parent = nullptr);
    ~Main_screen();

signals:
    void startTestClicked(int timeTest, const QSqlDatabase &db);

private slots:
    void chooseTestButtonClicked();
    void startTestButtonClicked();

private:
    bool openDatabase(const QString &fileName);
    bool checkDatabaseSchema();

    Ui::Main_screen *ui;
    QSqlDatabase db;
    int scoreSatisfactory;
    int scoreGood;
    int scoreExcellent;
    int timeTest;
    QString dbPath;

    QPushButton *startTestButton; // указатель на кнопку
};

#endif // MAIN_SCREEN_H
