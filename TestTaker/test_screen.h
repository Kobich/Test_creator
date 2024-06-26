#ifndef TEST_SCREEN_H
#define TEST_SCREEN_H

#include <QWidget>
#include <QSqlDatabase>
#include <QTimer>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QLabel>
#include <QMap>
#include <QLineEdit>
#include <QTextEdit>
#include <QWheelEvent>
#include "autoresizingtextedit.h"

namespace Ui {
class Test_screen;
}

class Test_screen : public QWidget
{
    Q_OBJECT

public:
    struct Answer {
        int id;
        int question_id;
        QString answer_text;
        int is_correct;
    };

    struct Question {
        int id;
        QString question_text;
        QByteArray image;
        int score;
        QList<Answer> answers;
    };

    struct OpenQuestion {
        int id;
        QString question_text;
        QString answer_text;
        QByteArray image;
        int score;
    };

    struct AnswerWidget {
        QCheckBox *checkBox;
        AutoResizingTextEdit *textLabel;
    };

    struct QuestionWidget {
        AutoResizingTextEdit *textEdit;
        QList<AnswerWidget> answers;
        QLabel *scoreLineEdit;
    };

    explicit Test_screen(const QSqlDatabase &db, QWidget *parent = nullptr, int timeTest = 0);
    ~Test_screen();

signals:
    void testCompleted(QMap<QString, float> score);

private slots:
    void updateTimer();
    void checkAnswers();
    void completeTheTest();

private:
    void readDataFromDatabase(const QSqlDatabase &db);
    void shuffleQuestions();
    void loadQuestionsFromDatabase();
    void printShuffledQuestions();
    QString insertLineBreaks(const QString &text, int maxWidth, const QFont &font);
    void readScoreTable(const QSqlDatabase &db);
    void closeDatabase();
    QString extractPlainTextFromHtml(const QString &html);

    QMap<int, QList<bool>> getUserAnswers(); // Для обычных вопросов
    QMap<int, QString> getUserOpenAnswers();

    Ui::Test_screen *ui;
    QTimer *timer;
    int timeRemaining;

    QList<Question> questions;
    QList<OpenQuestion> openQuestions;
    QList<Question> shuffledQuestions;
    QList<OpenQuestion> shuffledOpenQuestions;
    QList<QuestionWidget> questionWidgets;

    QVBoxLayout *questionsLayout; // Layout for questions
    QVBoxLayout *openQuestionsLayout; // Layout for open questions

    QMap<int, QList<QCheckBox*>> questionCheckBoxes; // Storage for user answers
    QMap<int, QLineEdit*> openQuestionLineEdits;

    QMap<QString, float> score;
    QSqlDatabase db;
};

#endif // TEST_SCREEN_H
