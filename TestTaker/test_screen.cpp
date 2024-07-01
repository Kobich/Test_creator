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
#include <QMessageBox>
#include <QThread>

Test_screen::Test_screen(const QSqlDatabase &db, QWidget *parent, int timeTest) :
    QWidget(parent),
    ui(new Ui::Test_screen),
    timeRemaining(timeTest* 60),
    db(db)
{
    ui->setupUi(this);

    // Открытие базы данных
    if (db.isOpen()) {
        qDebug() << "Database is already open.";
    }

    readDataFromDatabase(db); // Вызов функции для чтения данных из базы

    // Перемешиваем вопросы
    shuffleQuestions();


    loadQuestionsFromDatabase();



    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Test_screen::updateTimer);
    timer->start(1000);

    readScoreTable(db);
    closeDatabase();

    connect(ui->completeTheTest, &QPushButton::clicked, [=]() {
        completeTheTest();
    });

    show();
    //триггер для нормального отображения окон
    parent->resize(900, 800);



}

Test_screen::~Test_screen()
{

    delete ui;

}

void Test_screen::closeDatabase()
{
    if (db.isOpen()) {
        db.close();
        qDebug() << "Database closed";
    } else {
        qDebug() << "Database was already closed";
    }

    QString connectionName = db.connectionName();
    db = QSqlDatabase(); // Сбрасываем объект базы данных
    QSqlDatabase::removeDatabase(connectionName); // Удаляем соединение из пула
    qDebug() << "Database connection removed:" << connectionName;
}


void Test_screen::completeTheTest(){
    qDebug()<<"Button clicked";

    checkAnswers();
    emit testCompleted(score);

}

void Test_screen::readScoreTable(const QSqlDatabase &db) {
    if (!db.isOpen()) {
        qDebug() << "Database is not open.";
        return;
    }

    QSqlQuery query("SELECT score_satisfactory, score_good, score_excellent FROM scores", db);

    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return;
    }

    if (query.next()) {
        int scoreSatisfactory = query.value(0).toInt();
        int scoreGood = query.value(1).toInt();
        int scoreExcellent = query.value(2).toInt();



        score.insert("score_satisfactory", scoreSatisfactory);
        score.insert("score_good", scoreGood);
        score.insert("score_excellent", scoreExcellent);

    } else {
        qDebug() << "No data retrieved from scores table.";
    }
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
        completeTheTest();
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
    auto seed = static_cast<std::default_random_engine::result_type>(std::chrono::system_clock::now().time_since_epoch().count());
    std::default_random_engine rng(seed);
    std::shuffle(questions.begin(), questions.end(), rng);
    std::shuffle(openQuestions.begin(), openQuestions.end(), rng);
    shuffledQuestions = questions;
    shuffledOpenQuestions = openQuestions;
}

void Test_screen::loadQuestionsFromDatabase() {
    QList<QPair<int, bool>> questionTypes; // Pair of (question id, 0 for normal question, 1 for open question)
    for (const Question &question : shuffledQuestions) {
        questionTypes.append(qMakePair(question.id, false));
    }
    for (const OpenQuestion &openQuestion : shuffledOpenQuestions) {
        questionTypes.append(qMakePair(openQuestion.id, true));
    }

    // Shuffle question types
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(questionTypes.begin(), questionTypes.end(), g);

    int questionCounter = 1; // Счетчик вопросов

    for (const auto &questionType : questionTypes) {
        if (questionType.second) {
            // Open question
            const OpenQuestion &openQuestion = std::find_if(shuffledOpenQuestions.begin(), shuffledOpenQuestions.end(),
                [&questionType](const OpenQuestion &q) { return q.id == questionType.first; }).operator*();

            QWidget *newWidget = new QWidget();

            QGridLayout *newGridLayout = new QGridLayout(newWidget);

            QLabel *questionLabel = new QLabel(QString("%1.").arg(questionCounter)); // Нумеруем вопросы по порядку
            AutoResizingTextEdit *textEdit = new AutoResizingTextEdit();
            textEdit->setObjectName(QString("openQuestionText_%1").arg(openQuestion.id));
            textEdit->setHtml(openQuestion.question_text);
            textEdit->setTextInteractionFlags(Qt::NoTextInteraction);
            textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

            QLabel *scoreLabel = new QLabel("Баллы:");
            QLabel *scoreLineEdit = new QLabel();
            scoreLineEdit->setText(QString::number(openQuestion.score));
            scoreLineEdit->setMaximumWidth(30);

            QHBoxLayout *scoreLayout = new QHBoxLayout();
            scoreLayout->addWidget(scoreLabel);
            scoreLayout->addWidget(scoreLineEdit);

            newGridLayout->addLayout(scoreLayout, 0, 2, 1, 1, Qt::AlignRight);

            newGridLayout->addWidget(questionLabel, 0, 0, 1, 2);
            newGridLayout->addWidget(textEdit, 1, 0, 1, 3);

            QLineEdit *answerLineEdit = new QLineEdit();
            answerLineEdit->setObjectName(QString("openQuestionAnswer_%1").arg(openQuestion.id));

            newGridLayout->addWidget(answerLineEdit, 2, 0, 1, 3);

            newGridLayout->setColumnStretch(1, 1);
            newWidget->setLayout(newGridLayout);
            newWidget->setContentsMargins(0, 0, 0, 100);

            ui->verticalLayout->addWidget(newWidget);

            openQuestionLineEdits[openQuestion.id] = answerLineEdit;
        } else {
            // Normal question
            const Question &question = std::find_if(shuffledQuestions.begin(), shuffledQuestions.end(),
                [&questionType](const Question &q) { return q.id == questionType.first; }).operator*();

            QWidget *newWidget = new QWidget();
            QGridLayout *newGridLayout = new QGridLayout(newWidget);

            QLabel *questionLabel = new QLabel(QString("%1.").arg(questionCounter)); // Нумеруем вопросы по порядку
            AutoResizingTextEdit *textEdit = new AutoResizingTextEdit();
            textEdit->setObjectName(QString("questionText_%1").arg(question.id));
            textEdit->setHtml(question.question_text);
            textEdit->setTextInteractionFlags(Qt::NoTextInteraction);
            textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

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
            QList<AnswerWidget> answerWidgets;
            for (const Answer &answer : question.answers) {
                QCheckBox *checkBox = new QCheckBox();
                AutoResizingTextEdit *answerTextLabel = new AutoResizingTextEdit();
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
                answerWidgets.append(newAnswerWidget);

                QHBoxLayout *answerLayout = new QHBoxLayout();
                answerLayout->addWidget(checkBox);
                answerLayout->addWidget(answerTextLabel);

                newGridLayout->addLayout(answerLayout, 4 + answerCounter - 1, 0, 1, 3);

                answerCounter++;
            }

            newGridLayout->setColumnStretch(1, 1);
            newWidget->setLayout(newGridLayout);
            newWidget->setContentsMargins(0, 0, 0, 100);

            ui->verticalLayout->addWidget(newWidget);

            // Добавляем виджет в список виджетов вопросов
            QuestionWidget newQuestionWidget;
            newQuestionWidget.textEdit = textEdit;
            newQuestionWidget.answers = answerWidgets; // Добавляем ответы в виджет вопроса
            newQuestionWidget.scoreLineEdit = scoreLineEdit;
            questionWidgets.append(newQuestionWidget);

            // Добавляем чекбоксы в QMap для дальнейшей проверки ответов
            QList<QCheckBox*> checkBoxList;
            for (const AnswerWidget &answerWidget : newQuestionWidget.answers) {
                checkBoxList.append(answerWidget.checkBox);
            }
            questionCheckBoxes[question.id] = checkBoxList;
        }
        questionCounter++; // Увеличиваем счетчик вопросов
    }
}


QMap<int, QList<bool>> Test_screen::getUserAnswers() {
    QMap<int, QList<bool>> userAnswers;
    for (const Question &question : shuffledQuestions) {
        QList<bool> answers;
        const QList<QCheckBox*> checkBoxes = questionCheckBoxes[question.id];
        for (const QCheckBox *checkBox : checkBoxes) {
            answers.append(checkBox->isChecked());
        }
        userAnswers[question.id] = answers;
    }
    return userAnswers;
}

QMap<int, QString> Test_screen::getUserOpenAnswers() {
    QMap<int, QString> userOpenAnswers;
    for (const OpenQuestion &openQuestion : shuffledOpenQuestions) {
        QString userAnswer = openQuestionLineEdits[openQuestion.id]->text();
        userOpenAnswers[openQuestion.id] = userAnswer;
    }
    return userOpenAnswers;
}


void Test_screen::checkAnswers() {
    QMap<int, QList<bool>> userAnswers = getUserAnswers();
    QMap<int, QString> userOpenAnswers = getUserOpenAnswers();

    float totalUserScore = 0.0;
    float maxScore = 0.0;

    // Проверка ответов на обычные вопросы
    for (const Question &question : shuffledQuestions) {
        maxScore += static_cast<float>(question.score);

        if (userAnswers.contains(question.id)) {
            const QList<bool> userChecked = userAnswers[question.id];

            int correctAnswersCount = 0;
            int incorrectAnswersCount = 0;
            int totalCorrectAnswers = 0;

            // Считаем общее количество правильных ответов
            for (const Answer &answer : question.answers) {
                if (answer.is_correct) {
                    totalCorrectAnswers++;
                }
            }

            for (int i = 0; i < question.answers.size(); ++i) {
                const Answer &answer = question.answers[i];
                if (i < userChecked.size()) {
                    if (userChecked[i]) {
                        if (answer.is_correct) {
                            correctAnswersCount++;
                        } else {
                            incorrectAnswersCount++;
                        }
                    }
                }
            }

            float scoreFraction = static_cast<float>(correctAnswersCount - incorrectAnswersCount) / totalCorrectAnswers;
            float questionScore = scoreFraction * static_cast<float>(question.score);
            if (questionScore < float(0.0)) {
                questionScore = 0.0;
            }

            totalUserScore += questionScore;

            qDebug() << "Question ID:" << question.id << "Partial score:" << questionScore;
        } else {
            qDebug() << "Question ID:" << question.id << "No answers selected.";
        }
    }

    // Проверка ответов на открытые вопросы
    for (const OpenQuestion &openQuestion : shuffledOpenQuestions) {
        maxScore += static_cast<float>(openQuestion.score);

        if (userOpenAnswers.contains(openQuestion.id)) {
            QString userAnswer = userOpenAnswers[openQuestion.id];
            QString correctAnswer = openQuestion.answer_text;

            // Удаляем HTML-теги для сравнения
            QString userAnswerPlain = extractPlainTextFromHtml(userAnswer);
            QString correctAnswerPlain = extractPlainTextFromHtml(correctAnswer);

            if (userAnswerPlain.trimmed().toLower() == correctAnswerPlain.trimmed().toLower()) {
                totalUserScore += static_cast<float>(openQuestion.score);
                qDebug() << "Open Question ID:" << openQuestion.id << "Answer is correct.";
            } else {
                qDebug() << "Open Question ID:" << openQuestion.id << "Answer is incorrect.";
            }
        } else {
            qDebug() << "Open Question ID:" << openQuestion.id << "No answer provided.";
        }
    }

    score.insert("totalUserScore", static_cast<float>(totalUserScore));
    score.insert("maxScore", static_cast<float>(maxScore));
    qDebug() << "Total Score:" << totalUserScore << "Max Score:" << maxScore;
}

QString Test_screen::extractPlainTextFromHtml(const QString &htmlText) {
    QTextDocument textDoc;
    textDoc.setHtml(htmlText);
    return textDoc.toPlainText();
}


