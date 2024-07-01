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
#include "autoresizingtextedit.h"

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
    AutoResizingTextEdit *textEdit;
};

struct QuestionWidget {
    AutoResizingTextEdit *textEdit;
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
    void insertImage();
    void on_actionCreate_triggered();
    void on_actionOpen_triggered();
    void on_actionSaveAs_triggered();
    void on_actionSave_triggered();
    void on_addOpenQuestionButton_clicked();
    void on_addQuestionButton_clicked();

private:
    bool connectToDatabase(const QString &dbName);
    void clearAllQuestions();
    void clearDatabase();
    bool createTables();
    void deleteAnswer();
    void deleteQuestion();
    int findOpenQuestionIndex(QWidget *questionWidget);
    int findQuestionIndex(QWidget *questionWidget);
    void loadOpenQuestionsFromDatabase();
    void loadQuestionsFromDatabase();
    void loadScoresFromDatabase(); // Метод для загрузки оценок
    void loadTimeOfTestFromDatabase(); // Новый метод для загрузки времени теста
    bool insertAnswer(int questionId, const QString &answerText, bool isCorrect);
    bool insertOpenQuestion(const QString &questionText, const QString &answerText, int score);
    bool insertQuestion(const QString &questionText, int &questionId, int score);
    bool insertScores(int questionId, int score3, int score4, int score5); // Метод для вставки оценок
    void removeAnswer(QHBoxLayout *answerLayout, QWidget *parentWidget, int row);
    void removeOpenQuestion(QWidget *questionWidget, int questionIndex);
    void removeQuestion(QWidget *questionWidget, int questionIndex);
    void saveAllOpenQuestionsToDatabase();
    void saveAllQuestionsToDatabase();
    void saveScoresToDatabase();
    void saveTimeOfTestToDatabase(); // Новый метод для сохранения времени теста
    bool validateQuestions(); // Проверка на наличие правильных ответов
    bool validateScores();

    Ui::MainWindow *ui;
    QList<QuestionWidget> questions;
    QList<OpenQuestionWidget> openQuestions;
    QTextEdit *currentTextEdit; // Указатель на текущий QTextEdit для вставки изображения
    QWidget* createOpenQuestionWidget(int index);
    AutoResizingTextEdit *textEditFor3;
    AutoResizingTextEdit *textEditFor4;
    AutoResizingTextEdit *textEditFor5;
    AutoResizingTextEdit *timeOfTest; // Новый AutoResizingTextEdit для времени теста
    QString currentFileName;
};

#endif // MAINWINDOW_H
