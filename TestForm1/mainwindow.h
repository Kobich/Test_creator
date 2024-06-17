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
    explicit AutoResizingTextEdit(QWidget *parent = nullptr) : QTextEdit(parent) {
        connect(this, &QTextEdit::textChanged, this, &AutoResizingTextEdit::adjustHeight);
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Отключаем вертикальную полосу прокрутки
    }

private slots:
    void adjustHeight() {
        document()->setTextWidth(viewport()->width());
        QSize size = document()->size().toSize();
        setMinimumHeight(size.height() + 10); // Увеличение минимальной высоты на 10 пикселей
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
