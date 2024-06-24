#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QTextEdit>
#include <QRadioButton>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QFileDialog>
#include <QMessageBox>
#include <QLabel>
#include <QDebug>
#include <QLineEdit>

// Новый класс AutoResizingTextEdit
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
class MainWindow;
}

struct OpenQuestionWidget {
    QWidget *widget;
    AutoResizingTextEdit *questionTextEdit;
    AutoResizingTextEdit *answerTextEdit;
    QLineEdit* scoreLineEdit;
};

struct AnswerWidget {
    QCheckBox *checkBox;
    AutoResizingTextEdit *textEdit; // Используем AutoResizingTextEdit вместо QTextEdit
};

struct QuestionWidget {
    AutoResizingTextEdit *textEdit; // Используем AutoResizingTextEdit вместо QTextEdit
    QList<AnswerWidget> answers;
    QLineEdit* scoreLineEdit;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addAnswerButton();
    void on_addQuestionButton_clicked();
    void on_addOpenQuestionButton_clicked();
    void on_actionSaveAs_triggered();
    void on_actionOpen_triggered();
    void on_actionCreate_triggered();
    void on_actionSave_triggered();

    void insertImage();

private:
    Ui::MainWindow *ui;
    QList<QuestionWidget> questions;
    QList<OpenQuestionWidget> openQuestions;
    QTextEdit *currentTextEdit; // Указатель на текущий QTextEdit для вставки изображения
    QWidget* createOpenQuestionWidget(int index);
    // Новые поля для хранения значений из textEditFor3, textEditFor4, textEditFor5 и timeOfTest
    AutoResizingTextEdit *textEditFor3;
    AutoResizingTextEdit *textEditFor4;
    AutoResizingTextEdit *textEditFor5;
    AutoResizingTextEdit *timeOfTest; // Новый AutoResizingTextEdit для времени теста
    QString currentFileName;

    bool connectToDatabase(const QString &dbName);
    bool createTables();
    bool insertQuestion(const QString &questionText, int &questionId, int score);
    bool insertAnswer(int questionId, const QString &answerText, bool isCorrect);
    bool insertScores(int questionId, int score3, int score4, int score5); // Метод для вставки оценок
    void saveAllQuestionsToDatabase();
    void loadQuestionsFromDatabase();
    void loadScoresFromDatabase(); // Метод для загрузки оценок
    void saveTimeOfTestToDatabase(); // Новый метод для сохранения времени теста
    void loadTimeOfTestFromDatabase(); // Новый метод для загрузки времени теста
    bool validateQuestions(); // Проверка на наличие правильных ответов
    void clearAllQuestions();
    void saveScoresToDatabase();
    void clearDatabase();
    bool validateScores();
    void deleteQuestion();
    void deleteAnswer();
    void removeQuestion(QWidget *questionWidget);
    void removeQuestion(QWidget *questionWidget, int questionIndex);
    void removeAnswer(QHBoxLayout *answerLayout, QWidget *parentWidget, int row);
    int findQuestionIndex(QWidget *questionWidget);
    void saveAllOpenQuestionsToDatabase();
    void loadOpenQuestionsFromDatabase();
    bool insertOpenQuestion(const QString &questionText, const QString &answerText, int score);
    void removeOpenQuestion(QWidget *questionWidget, int questionIndex);
    int  findOpenQuestionIndex(QWidget *questionWidget);
};

#endif // MAINWINDOW_H
