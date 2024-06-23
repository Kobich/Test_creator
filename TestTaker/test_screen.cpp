#include "test_screen.h"
#include "ui_test_screen.h"
#include <QSqlQuery>
#include <QLabel>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QScrollArea>
#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>
#include <QLineEdit>
#include <algorithm>
#include <random>

Test_screen::Test_screen(const QSqlDatabase &db, QWidget *parent, int timeTest) :
    QWidget(parent),
    ui(new Ui::Test_screen),
    timeRemaining(timeTest* 60)
{
    ui->setupUi(this);

    // Открытие базы данных
    if (db.isOpen()) {
        qDebug() << "Database is already open.";
    }

    readDataFromDatabase(db); // Вызов функции для чтения данных из базы

    // Перемешиваем вопросы
    shuffleQuestions();

    // Загружаем вопросы из базы данных и создаем виджеты
    loadQuestionsFromDatabase();

    // Выводим перемешанные вопросы
    printShuffledQuestions();

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Test_screen::updateTimer);
    timer->start(1000);
}

Test_screen::~Test_screen()
{
    delete ui;
}

void Test_screen::updateTimer() {
    if (timeRemaining > 0) {
        timeRemaining--;

        int minutes = timeRemaining / 60;
        int seconds = timeRemaining % 60;

        QString timeText = QString("Оставшееся время: %1:%2")
                            .arg(minutes, 2, 10, QChar('0'))
                            .arg(seconds, 2, 10, QChar('0'));

        ui->timerLabel->setText(timeText);
    } else {
        timer->stop();
        // Добавьте код для завершения теста или других действий по истечении времени
        qDebug() << "Time is up!";
    }
}

void Test_screen::readDataFromDatabase(const QSqlDatabase &db) {
    if (!db.isOpen()) {
        qDebug() << "Database is not open.";
        return;
    }

    // Чтение данных из таблицы questions
    QSqlQuery queryQuestions("SELECT * FROM questions", db);
    while (queryQuestions.next()) {
        Question question;
        question.id = queryQuestions.value(0).toInt();
        question.question_text = queryQuestions.value(1).toString();
        question.image = queryQuestions.value(2).toByteArray();
        question.score = queryQuestions.value(3).toInt();
        questions.append(question);
    }

    // Чтение данных из таблицы answers
    QSqlQuery queryAnswers("SELECT * FROM answers", db);
    while (queryAnswers.next()) {
        Answer answer;
        answer.id = queryAnswers.value(0).toInt();
        answer.question_id = queryAnswers.value(1).toInt();
        answer.answer_text = queryAnswers.value(2).toString();
        answer.is_correct = queryAnswers.value(3).toInt();

        // Найти соответствующий вопрос и добавить ответ к нему
        for (Question &question : questions) {
            if (question.id == answer.question_id) {
                question.answers.append(answer);
                break;
            }
        }
    }

    // Чтение данных из таблицы open_questions
    QSqlQuery queryOpenQuestions("SELECT * FROM open_questions", db);
    while (queryOpenQuestions.next()) {
        OpenQuestion openQuestion;
        openQuestion.id = queryOpenQuestions.value(0).toInt();
        openQuestion.question_text = queryOpenQuestions.value(1).toString();
        openQuestion.answer_text = queryOpenQuestions.value(2).toString();
        openQuestion.image = queryOpenQuestions.value(3).toByteArray();
        openQuestion.score = queryOpenQuestions.value(4).toInt();
        openQuestions.append(openQuestion);
    }

    // Вывод данных в консоль
    qDebug() << "Questions and Answers loaded from the database.";
}

void Test_screen::shuffleQuestions() {
    // Используем текущее время в качестве случайного зерна
    auto seed = static_cast<std::default_random_engine::result_type>(std::chrono::system_clock::now().time_since_epoch().count());

    // Создаем генератор случайных чисел
    std::default_random_engine rng(seed);

    // Перемешиваем вопросы
    std::shuffle(questions.begin(), questions.end(), rng);

    // Перемешиваем открытые вопросы
    std::shuffle(openQuestions.begin(), openQuestions.end(), rng);

    // Копируем перемешанные вопросы в соответствующие списки
    shuffledQuestions = questions;
    shuffledOpenQuestions = openQuestions;
}

void Test_screen::loadQuestionsFromDatabase() {
    for (const Question &question : shuffledQuestions) {
        QWidget *newWidget = new QWidget();
        QGridLayout *newGridLayout = new QGridLayout(newWidget);

        QLabel *questionLabel = new QLabel(QString("Вопрос %1").arg(question.id));
        AutoResizingTextEdit *textEdit = new AutoResizingTextEdit();
        textEdit->setObjectName(QString("questionText_%1").arg(question.id));
        textEdit->setHtml(question.question_text);
        textEdit->setTextInteractionFlags(Qt::NoTextInteraction);
        textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


        QuestionWidget newQuestionWidget;
        newQuestionWidget.textEdit = textEdit;

        newGridLayout->addWidget(questionLabel, 0, 0, 1, 2);
        newGridLayout->addWidget(textEdit, 1, 0, 1, 3);

        // Добавляем поле для ввода баллов
        QLabel *scoreLabel = new QLabel("Баллы:");
        QLabel *scoreLineEdit = new QLabel();
        scoreLineEdit->setText(QString::number(question.score));
        scoreLineEdit->setMaximumWidth(30);

        QHBoxLayout *scoreLayout = new QHBoxLayout();
        scoreLayout->addWidget(scoreLabel);
        scoreLayout->addWidget(scoreLineEdit);

        newGridLayout->addLayout(scoreLayout, 0, 0, 1, 3, Qt::AlignRight);

        int answerCounter = 1;
        for (const Answer &answer : question.answers) {
            QCheckBox *checkBox = new QCheckBox();
            CustomAutoResizingTextEdit *answerTextLabel = new CustomAutoResizingTextEdit();
            answerTextLabel->setObjectName(QString("answerText_%1_%2").arg(question.id).arg(answerCounter));
            answerTextLabel->setText(answer.answer_text);

            // Установка минимальной высоты для текстового поля
            answerTextLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            answerTextLabel->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            answerTextLabel->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            answerTextLabel->setReadOnly(true); // Опционально: чтобы текст был только для чтения

            AnswerWidget newAnswerWidget;
            newAnswerWidget.checkBox = checkBox;
            newAnswerWidget.textLabel = answerTextLabel;

            newQuestionWidget.answers.append(newAnswerWidget);

            QHBoxLayout *answerLayout = new QHBoxLayout();
            answerLayout->addWidget(checkBox);
            answerLayout->addWidget(answerTextLabel);

            newGridLayout->addLayout(answerLayout, 4 + answerCounter - 1, 0, 1, 3);
            answerCounter++;
        }

        newGridLayout->setColumnStretch(1, 1);
        newWidget->setLayout(newGridLayout);
        newWidget->setContentsMargins(0, 0, 0, 40);

        ui->verticalLayout->addWidget(newWidget);

        newQuestionWidget.scoreLineEdit = nullptr;
        questionWidgets.append(newQuestionWidget);
        questionCheckBoxes[question.id] = QList<QCheckBox*>();
        for (const AnswerWidget &answerWidget : newQuestionWidget.answers) {
            questionCheckBoxes[question.id].append(answerWidget.checkBox);
        }
    }

    for (const OpenQuestion &openQuestion : shuffledOpenQuestions) {
        QWidget *newWidget = new QWidget();
        QGridLayout *newGridLayout = new QGridLayout(newWidget);

        QLabel *questionLabel = new QLabel(QString("Открытый вопрос %1").arg(openQuestion.id));
        AutoResizingTextEdit *textEdit = new AutoResizingTextEdit();
        textEdit->setObjectName(QString("openQuestionText_%1").arg(openQuestion.id));
        textEdit->setHtml(openQuestion.question_text);
        textEdit->setTextInteractionFlags(Qt::NoTextInteraction);
        textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        newGridLayout->addWidget(questionLabel, 0, 0, 1, 2);
        newGridLayout->addWidget(textEdit, 1, 0, 1, 3);

        QLineEdit *answerLineEdit = new QLineEdit();
        answerLineEdit->setObjectName(QString("openQuestionAnswer_%1").arg(openQuestion.id));

        newGridLayout->addWidget(answerLineEdit, 2, 0, 1, 3);

        newGridLayout->setColumnStretch(1, 1);
        newWidget->setLayout(newGridLayout);
        newWidget->setContentsMargins(0, 0, 0, 40);

        ui->verticalLayout->addWidget(newWidget);

        openQuestionLineEdits[openQuestion.id] = answerLineEdit;
    }
}




void Test_screen::printShuffledQuestions() {
    qDebug() << "Shuffled Questions:";
    for (const Question &question : shuffledQuestions) {
        qDebug() << "ID:" << question.id << "Text:" << question.question_text;
        for (const Answer &answer : question.answers) {
            qDebug() << "Answer ID:" << answer.id << "Text:" << answer.answer_text << "Correct:" << answer.is_correct;
        }
    }

    qDebug() << "Shuffled Open Questions:";
    for (const OpenQuestion &openQuestion : shuffledOpenQuestions) {
        qDebug() << "ID:" << openQuestion.id << "Question:" << openQuestion.question_text << "Answer:" << openQuestion.answer_text;
    }
}

void Test_screen::checkAnswers() {
    // Checking multiple choice questions
    for (const Question &question : shuffledQuestions) {
        const QList<QCheckBox*> checkBoxes = questionCheckBoxes[question.id];
        for (const Answer &answer : question.answers) {
            bool userChecked = checkBoxes[answer.id]->isChecked();
            bool correct = (answer.is_correct == 1);
            if (userChecked != correct) {
                qDebug() << "Question ID:" << question.id << "Answer ID:" << answer.id << "is incorrect.";
            } else {
                qDebug() << "Question ID:" << question.id << "Answer ID:" << answer.id << "is correct.";
            }
        }
    }

    // Checking open questions
    for (const OpenQuestion &openQuestion : shuffledOpenQuestions) {
        QString userAnswer = openQuestionLineEdits[openQuestion.id]->text();
        if (userAnswer.trimmed().toLower() != openQuestion.answer_text.trimmed().toLower()) {
            qDebug() << "Open Question ID:" << openQuestion.id << "Answer is incorrect.";
        } else {
            qDebug() << "Open Question ID:" << openQuestion.id << "Answer is correct.";
        }
    }
}



/*

void Test_screen::loadQuestionsFromDatabase() {
    QSqlQuery questionQuery("SELECT id, question_text, score FROM questions");
    while (questionQuery.next()) {
        int questionId = questionQuery.value(0).toInt();
        QString questionText = questionQuery.value(1).toString();
        int score = questionQuery.value(2).toInt(); // Считывание баллов

        QWidget *newWidget = new QWidget();
        QGridLayout *newGridLayout = new QGridLayout(newWidget);

        QLabel *questionLabel = new QLabel(QString("Вопрос %1").arg(questionId));
        AutoResizingTextEdit *textEdit = new AutoResizingTextEdit();
        textEdit->setObjectName(QString("questionText_%1").arg(questionId));
        textEdit->setHtml(questionText); // Используем setHtml для загрузки HTML
        textEdit->setTextInteractionFlags(Qt::NoTextInteraction);

        QuestionWidget newQuestion;
        newQuestion.textEdit = textEdit;

        newGridLayout->addWidget(questionLabel, 0, 0, 1, 2);
        newGridLayout->addWidget(textEdit, 1, 0, 1, 3);

        // Добавляем поле для ввода баллов
        QLabel *scoreLabel = new QLabel("Баллы:");
        QLabel *scoreLineEdit = new QLabel();
        scoreLineEdit->setText(QString::number(score));
        scoreLineEdit->setMaximumWidth(30);
        //scoreLineEdit->setReadOnly(true); // Запретить редактирование текста

        QHBoxLayout *scoreLayout = new QHBoxLayout();
        scoreLayout->addWidget(scoreLabel);
        scoreLayout->addWidget(scoreLineEdit);

        newGridLayout->addLayout(scoreLayout, 0, 0, 1, 3,Qt::AlignRight);

        QSqlQuery answerQuery;
        answerQuery.prepare("SELECT answer_text, is_correct FROM answers WHERE question_id = :question_id");
        answerQuery.bindValue(":question_id", questionId);
        answerQuery.exec();

        int answerCounter = 1;
        while (answerQuery.next()) {
                    QString answerText = answerQuery.value(0).toString();

                    QCheckBox *checkBox = new QCheckBox();
                    QLabel *answerTextLabel = new QLabel();
                    answerTextLabel->setObjectName(QString("answerText_%1_%2").arg(questionId).arg(answerCounter));
                    answerTextLabel->setText(answerText); // Используем setText

                    AnswerWidget newAnswer;
                    newAnswer.checkBox = checkBox;
                    newAnswer.textLabel = answerTextLabel;

                    newQuestion.answers.append(newAnswer);

                    QHBoxLayout *answerLayout = new QHBoxLayout();
                    answerLayout->addWidget(checkBox);
                    answerLayout->addWidget(answerTextLabel);
                    answerLayout->addStretch(); // Добавляем растяжку для выравнивания

                    newGridLayout->addLayout(answerLayout, 4 + answerCounter - 1, 0, 1, 3);
                    //newGridLayout->addLayout(answerLayout, 4 + answerCounter - 1, 0, 1, 3);
                    answerCounter++;
                }

        newGridLayout->setColumnStretch(1, 1);
        newWidget->setLayout(newGridLayout);
        newWidget->setContentsMargins(0, 0, 0, 40);

        ui->verticalLayout->addWidget(newWidget);

        newQuestion.scoreLineEdit = nullptr;
        questions.append(newQuestion);
    }
}






void Test_screen::loadOpenQuestionsFromDatabase(){

    QSqlQuery query("SELECT id, question_text, answer_text, score FROM open_questions");
    int openQuestionCounter = openQuestions.size() + 1;
    while (query.next()) {
        //int questionId = query.value(0).toInt();
        QString questionText = query.value(1).toString();
        QString answerText = query.value(2).toString();
        int score = query.value(3).toInt();

        QWidget *newWidget = new QWidget();
        QGridLayout *newGridLayout = new QGridLayout(newWidget);

        QLabel *questionLabel = new QLabel(QString("Открытый вопрос %1").arg(openQuestionCounter));
        AutoResizingTextEdit *questionTextEdit = new AutoResizingTextEdit();
        questionTextEdit->setObjectName(QString("openQuestionText_%1").arg(openQuestionCounter));
        questionTextEdit->setHtml(questionText); // Используем setHtml для загрузки HTML
        questionTextEdit->setTextInteractionFlags(Qt::NoTextInteraction);

        QLabel *answerLabel = new QLabel("Ответ:");
        AutoResizingTextEdit *answerTextEdit = new AutoResizingTextEdit();
        answerTextEdit->setObjectName(QString("openAnswerText_%1").arg(openQuestionCounter));
        answerTextEdit->setHtml(answerText); // Используем setHtml для загрузки HTML

        QLabel *scoreLabel = new QLabel("Баллы:");
        QLabel *scoreLineEdit = new QLabel();

        scoreLineEdit->setText(QString::number(score));
        scoreLineEdit->setMaximumWidth(30);

        QHBoxLayout *scoreLayout = new QHBoxLayout();
        scoreLayout->addWidget(scoreLabel);
        scoreLayout->addWidget(scoreLineEdit);
        //scoreLayout->addItem(spacer);

        newGridLayout->addLayout(scoreLayout, 0, 1, 1, 2, Qt::AlignRight);

        newGridLayout->addWidget(questionLabel, 0, 0, 1, 1);
        newGridLayout->addWidget(questionTextEdit, 1, 0, 1, 3);
        newGridLayout->addWidget(answerLabel, 4, 0, 1, 1);
        newGridLayout->addWidget(answerTextEdit, 5, 0, 1, 3);

        ui->verticalLayout->addWidget(newWidget);

        OpenQuestionWidget newOpenQuestion;
        newOpenQuestion.questionTextEdit = questionTextEdit;
        newOpenQuestion.answerTextEdit = answerTextEdit;
        newOpenQuestion.scoreLineEdit = nullptr;

        openQuestions.append(newOpenQuestion);
        openQuestionCounter++;
    }
}
*/
