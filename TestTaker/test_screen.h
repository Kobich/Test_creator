#ifndef TEST_SCREEN_H
#define TEST_SCREEN_H

#include <QWidget>
#include <QSqlDatabase>
#include <QTimer>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QCheckBox>
#include <QLabel>
#include <QMap>
#include <QLineEdit>
#include <QTextEdit>

class AutoResizingTextEdit : public QTextEdit {
    Q_OBJECT
public:
    AutoResizingTextEdit(QWidget *parent = nullptr) : QTextEdit(parent) {
        setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        connect(this, &QTextEdit::textChanged, this, &AutoResizingTextEdit::adjustHeight);
    }

private slots:
    void adjustHeight() {
        document()->setTextWidth(width());
        QSize newSize(document()->size().toSize());
        setMinimumHeight(newSize.height() + 10);
    }
};

class CustomAutoResizingTextEdit : public QTextEdit {
    Q_OBJECT
public:
    CustomAutoResizingTextEdit(QWidget *parent = nullptr) : QTextEdit(parent) {
        setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        connect(this, &QTextEdit::textChanged, this, &CustomAutoResizingTextEdit::adjustHeight);
    }
protected:
    void resizeEvent(QResizeEvent *event) override {
        QTextEdit::resizeEvent(event); // Вызываем реализацию базового класса

        // При изменении размера виджета также корректируем его высоту
        adjustHeight();
    }
private slots:
    void adjustHeight() {
        document()->setTextWidth(width());
        QSize newSize(document()->size().toSize());
        setMinimumHeight(newSize.height() + 10);
    }
};

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
        CustomAutoResizingTextEdit *textLabel;
    };

    struct QuestionWidget {
        AutoResizingTextEdit *textEdit;
        QList<AnswerWidget> answers;
        QLabel *scoreLineEdit;
    };

    explicit Test_screen(const QSqlDatabase &db, QWidget *parent = nullptr, int timeTest = 0);
    ~Test_screen();

private slots:
    void updateTimer();
    void checkAnswers();

private:
    void readDataFromDatabase(const QSqlDatabase &db);
    void shuffleQuestions();
    void loadQuestionsFromDatabase();
    void printShuffledQuestions();
    QString insertLineBreaks(const QString &text, int maxWidth, const QFont &font);
    Ui::Test_screen *ui;
    QTimer *timer;
    int timeRemaining;

    QList<Question> questions;
    QList<OpenQuestion> openQuestions;
    QList<Question> shuffledQuestions;
    QList<OpenQuestion> shuffledOpenQuestions;

    QList<QuestionWidget> questionWidgets;

    // Layout for questions and open questions
    QVBoxLayout *questionsLayout;
    QVBoxLayout *openQuestionsLayout;

    // Storage for user answers
    QMap<int, QList<QCheckBox*>> questionCheckBoxes;
    QMap<int, QLineEdit*> openQuestionLineEdits;
};

#endif // TEST_SCREEN_H
