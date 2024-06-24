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
#include <QWheelEvent>

class AutoResizingTextEdit : public QTextEdit {
    Q_OBJECT
public:
    AutoResizingTextEdit(QWidget *parent = nullptr) : QTextEdit(parent) {
        setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        connect(this, &QTextEdit::textChanged, this, &AutoResizingTextEdit::adjustHeight);
        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    }

protected:

    void resizeEvent(QResizeEvent *event) override {
        QTextEdit::resizeEvent(event); // Вызываем реализацию базового класса
        adjustHeight();
    }

    void wheelEvent(QWheelEvent *event) override {
           // Не вызываем базовую реализацию, чтобы предотвратить прокрутку
           event->ignore();
       }

       // Переопределяем события прокрутки для вертикального и горизонтального прокрутки
       void scrollContentsBy(int dx, int dy) override {
           // Ничего не делаем, чтобы предотвратить прокрутку
           Q_UNUSED(dx);
           Q_UNUSED(dy);
       }
private slots:
    void adjustHeight() {
        document()->setTextWidth(width());
        QSize newSize(document()->size().toSize());
        setMinimumHeight(newSize.height() + 15);
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
        AutoResizingTextEdit *textLabel;
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
    void on_completeTheTest_clicked();



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
    QString extractPlainTextFromHtml(const QString &html);

    QList<QuestionWidget> questionWidgets;

    // Layout for questions and open questions
    QVBoxLayout *questionsLayout;
    QVBoxLayout *openQuestionsLayout;

    // Storage for user answers
    QMap<int, QList<QCheckBox*>> questionCheckBoxes;
    QMap<int, QLineEdit*> openQuestionLineEdits;
    QMap<int, QList<bool>> getUserAnswers(); // Для обычных вопросов
    QMap<int, QString> getUserOpenAnswers();
};

#endif // TEST_SCREEN_H
