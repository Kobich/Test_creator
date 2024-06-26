#include "result_screen.h"
#include "ui_result_screen.h"

Result_screen::Result_screen(QWidget *parent, QMap<QString, float> score) :
    QWidget(parent),
    ui(new Ui::Result_screen)
{
    ui->setupUi(this);
    displayResults(score);  // Call the method to display results
}

Result_screen::~Result_screen()
{
    delete ui;
}

void Result_screen::displayResults(const QMap<QString, float> &score)
{
    float totalUserScore = score.value("totalUserScore", 0);
    float maxScore = score.value("maxScore", 0);

    // Переводим проценты в баллы
    float scoreSatisfactory = (score.value("score_satisfactory", 0) / 100) * maxScore;
    float scoreGood = (score.value("score_good", 0) / 100) * maxScore;
    float scoreExcellent = (score.value("score_excellent", 0) / 100) * maxScore;

    // Set text for the final score label
    ui->finalScoreLabel->setText(QString("Итоговый балл: %1 из %2")
                                 .arg(QString::number(static_cast<double>(totalUserScore), 'f', 2))
                                 .arg(QString::number(static_cast<double>(maxScore), 'f', 2)));

    // Determine and set the text for the mark label
    QString mark;
    if (totalUserScore >= scoreExcellent) {
        mark = "Отлично";
    } else if (totalUserScore >= scoreGood) {
        mark = "Хорошо";
    } else if (totalUserScore >= scoreSatisfactory) {
        mark = "Удовлетворительно";
    } else {
        mark = "Неудовлетворительно";
    }
    ui->markLabel->setText(QString("Оценка: %1").arg(mark));
}

void Result_screen::on_mainScreenButton_clicked(){

    emit createNewMainScreen();
}

