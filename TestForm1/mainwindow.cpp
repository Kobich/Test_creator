#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QBuffer>
#include <QTextBlock>
#include <QTextStream>
#include <QMessageBox>
#include <QLabel>
#include <QSqlError>
#include <QDebug>
#include <QTextCursor>
#include <QTextDocumentFragment>
#include <QLineEdit>
#include <QCheckBox>
#include <QIntValidator>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    show();
    resize(this->width(),this->height());

}

MainWindow::~MainWindow() {
    delete ui;

}

bool MainWindow::validateScores() {
    bool allValid = true;
    QStringList errorMessages;

    QSet<int> uniqueScores;

    auto validateField = [&allValid, &errorMessages, &uniqueScores](QTextEdit *field, const QString &fieldName) {
        bool ok;
        int value = field->toPlainText().toInt(&ok);

        if (!ok || value < 1 || value > 100) {
            errorMessages.append(QObject::tr("Некорректное значение в поле %1. Пожалуйста, введите целое число от 1 до 100.").arg(fieldName));
            field->setStyleSheet("border: 1px solid red");
            field->setToolTip(QObject::tr("Пожалуйста, введите целое число от 1 до 100"));
            allValid = false;
        } else {
            field->setStyleSheet("");
            field->setToolTip("");
            if (uniqueScores.contains(value)) {
                errorMessages.append(QObject::tr("Значения в полях не должны повторяться. Пожалуйста, измените значение в поле %1.").arg(fieldName));
                field->setStyleSheet("border: 1px solid red");
                field->setToolTip(QObject::tr("Значения в полях не должны повторяться"));
                allValid = false;
            } else {
                uniqueScores.insert(value);
            }
        }
    };

    validateField(ui->textEditFor3, "<<удовлетворительно>>");
    validateField(ui->textEditFor4, "<<хорошо>>");
    validateField(ui->textEditFor5, "<<отлично>>");

    // Проверка времени теста
    bool ok;
    int timeValue = ui->timeOfTest->toPlainText().toInt(&ok);
    if (!ok || timeValue < 0) {
        errorMessages.append(tr("Некорректное значение в поле <<Время выполнения теста>>. Пожалуйста, введите неотрицательное целое число."));
        ui->timeOfTest->setStyleSheet("border: 1px solid red");
        ui->timeOfTest->setToolTip(tr("Пожалуйста, введите неотрицательное целое число"));
        allValid = false;
    } else {
        ui->timeOfTest->setStyleSheet("");
        ui->timeOfTest->setToolTip("");
    }

    if (!allValid && !errorMessages.isEmpty()) {
        QMessageBox::warning(this, tr("Ошибка"), errorMessages.join("\n"));
    }

    return allValid;
}



void MainWindow::addAnswerButton() {
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
    if (!clickedButton) return;

    AnswerWidget answerWidget;
    answerWidget.checkBox = new QCheckBox();
    answerWidget.textEdit = new AutoResizingTextEdit();

    QWidget *parentWidget = clickedButton->parentWidget();
    QGridLayout *gridLayoutParent = qobject_cast<QGridLayout*>(parentWidget->layout());

    if (parentWidget && gridLayoutParent) {
        int row = gridLayoutParent->rowCount();
        QHBoxLayout *answerLayout = new QHBoxLayout();
        answerLayout->addWidget(answerWidget.checkBox);
        answerLayout->addWidget(answerWidget.textEdit);
        answerWidget.textEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        answerWidget.textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        answerWidget.textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        QPushButton *deleteAnswerButton = new QPushButton("Удалить");
        connect(deleteAnswerButton, &QPushButton::clicked, [this, answerLayout, parentWidget, row]() {
            removeAnswer(answerLayout, parentWidget, row);
        });
        answerLayout->addWidget(deleteAnswerButton);

        gridLayoutParent->addLayout(answerLayout, row, 0, 1, 3);

        int questionIndex = -1;
        for (int i = 0; i < questions.size(); ++i) {
            if (questions[i].textEdit->parentWidget() == parentWidget) {
                questionIndex = i;
                break;
            }
        }
        if (questionIndex >= 0) {
            questions[questionIndex].answers.append(answerWidget);
        }
    }
}

void MainWindow::on_addQuestionButton_clicked() {
    int questionCounter = questions.size() + 1;

    QWidget *newWidget = new QWidget();
    QGridLayout *newGridLayout = new QGridLayout(newWidget);

    QLabel *questionLabel = new QLabel(QString("Вопрос %1").arg(questionCounter));
    AutoResizingTextEdit *textEdit = new AutoResizingTextEdit();
    textEdit->setObjectName(QString("questionText_%1").arg(questionCounter));

    QuestionWidget newQuestion;
    newQuestion.textEdit = textEdit;

    QPushButton *addAnswerButton = new QPushButton("Добавить\nответ");
    addAnswerButton->setObjectName(QString("addAnswerButton_%1").arg(questionCounter));

    QPushButton *insertImageButton = new QPushButton("Вставить изображение");
    connect(insertImageButton, &QPushButton::clicked, [this, textEdit]() {
        currentTextEdit = textEdit;
        insertImage();
    });

    QPushButton *deleteQuestionButton = new QPushButton("Удалить вопрос");
    connect(deleteQuestionButton, &QPushButton::clicked, [this, newWidget, questionCounter]() {
        removeQuestion(newWidget, questionCounter - 1);
    });

    QLabel *scoreLabel = new QLabel("Баллы:");
    QLineEdit *scoreLineEdit = new QLineEdit();
    QSpacerItem *spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    scoreLineEdit->setValidator(new QIntValidator(0, 99, this)); // Только цифры от 0 до 99
    scoreLineEdit->setText("1");
    scoreLineEdit->setMaximumWidth(30);

    QHBoxLayout *scoreLayout = new QHBoxLayout();
    scoreLayout->addWidget(scoreLabel);
    scoreLayout->addWidget(scoreLineEdit);
    scoreLayout->addItem(spacer);
    scoreLayout->addWidget(insertImageButton);

    newGridLayout->addLayout(scoreLayout, 2, 0, 1, 3);

    newGridLayout->addWidget(questionLabel, 0, 0, 1, 1);
    newGridLayout->addWidget(deleteQuestionButton, 0, 2, 1, 1, Qt::AlignRight);
    newGridLayout->addWidget(textEdit, 1, 0, 1, 3);
    newGridLayout->addWidget(addAnswerButton, 3, 0, 1, 1, Qt::AlignLeft);
    //newGridLayout->addWidget(insertImageButton, 3, 1, 1, 2, Qt::AlignRight);

    connect(addAnswerButton, &QPushButton::clicked, this, &MainWindow::addAnswerButton);

    ui->verticalLayout_2->addWidget(newWidget);

    newQuestion.answers.clear();
    newQuestion.scoreLineEdit = scoreLineEdit;
    questions.append(newQuestion);

    questionCounter++;
}


void MainWindow::on_addOpenQuestionButton_clicked() {
    int index = openQuestions.size();
    QWidget *newWidget = createOpenQuestionWidget(index);
    ui->verticalLayout_2->addWidget(newWidget);
}

void MainWindow::removeOpenQuestion(QWidget *questionWidget, int questionIndex) {
    // Обновление questionIndex для обработки возможного несоответствия
    questionIndex = findOpenQuestionIndex(questionWidget);

    if (questionIndex >= 0 && questionIndex < openQuestions.size()) {
        // Удаление виджетов из интерфейса
        ui->verticalLayout_2->removeWidget(questionWidget);
        questionWidget->deleteLater();

        // Удаление данных из модели
        openQuestions.removeAt(questionIndex);

        // Обновление номеров вопросов и кнопок
        for (int i = questionIndex; i < openQuestions.size(); ++i) {
            OpenQuestionWidget &openQuestion = openQuestions[i];
            QGridLayout *layout = qobject_cast<QGridLayout*>(openQuestion.widget->layout());
            QLabel *questionLabel = qobject_cast<QLabel*>(layout->itemAtPosition(0, 0)->widget());
            questionLabel->setText(QString("Открытый вопрос %1").arg(i + 1));

            QPushButton *deleteButton = qobject_cast<QPushButton*>(layout->itemAtPosition(0, 2)->widget());
            deleteButton->disconnect(); // Отключаем старые сигналы
            QWidget *currentWidget = openQuestion.widget;
            connect(deleteButton, &QPushButton::clicked, [this, currentWidget, i]() {
                removeOpenQuestion(currentWidget, i);
            });
        }
    }
}

QWidget* MainWindow::createOpenQuestionWidget(int index) {
    QWidget *newWidget = new QWidget();
    QGridLayout *newGridLayout = new QGridLayout(newWidget);

    QLabel *questionLabel = new QLabel(QString("Открытый вопрос %1").arg(index + 1));
    AutoResizingTextEdit *questionTextEdit = new AutoResizingTextEdit();
    questionTextEdit->setObjectName(QString("openQuestionText_%1").arg(index + 1));

    QLabel *answerLabel = new QLabel("Ответ:");
    AutoResizingTextEdit *answerTextEdit = new AutoResizingTextEdit();
    answerTextEdit->setObjectName(QString("openAnswerText_%1").arg(index + 1));

    QPushButton *deleteOpenQuestionButton = new QPushButton("Удалить вопрос");
    connect(deleteOpenQuestionButton, &QPushButton::clicked, [this, newWidget, index]() {
        removeOpenQuestion(newWidget, index);
    });

    QPushButton *insertImageButton = new QPushButton("Вставить изображение");
    connect(insertImageButton, &QPushButton::clicked, [this, questionTextEdit]() {
        currentTextEdit = questionTextEdit;
        insertImage();
    });

    // Добавляем поле для ввода баллов
    QLabel *scoreLabel = new QLabel("Баллы:");
    QLineEdit *scoreLineEdit = new QLineEdit();
    QSpacerItem *spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    scoreLineEdit->setValidator(new QIntValidator(0, 99, this)); // Только цифры от 0 до 99
    scoreLineEdit->setText("1");
    scoreLineEdit->setMaximumWidth(30);

    QHBoxLayout *scoreLayout = new QHBoxLayout();
    scoreLayout->addWidget(scoreLabel);
    scoreLayout->addWidget(scoreLineEdit);
    scoreLayout->addItem(spacer);
    scoreLayout->addWidget(insertImageButton);

    newGridLayout->addLayout(scoreLayout, 3, 0, 1, 3);

    newGridLayout->addWidget(questionLabel, 0, 0, 1, 1);
    newGridLayout->addWidget(deleteOpenQuestionButton, 0, 2, 1, 1, Qt::AlignRight);
    newGridLayout->addWidget(questionTextEdit, 1, 0, 1, 3);
    //newGridLayout->addWidget(insertImageButton, 2, 0, 1, 1);

    newGridLayout->addWidget(answerLabel, 4, 0, 1, 1);
    newGridLayout->addWidget(answerTextEdit, 5, 0, 1, 3);

    OpenQuestionWidget newOpenQuestion;
    newOpenQuestion.widget = newWidget;
    newOpenQuestion.questionTextEdit = questionTextEdit;
    newOpenQuestion.answerTextEdit = answerTextEdit;
    newOpenQuestion.scoreLineEdit = scoreLineEdit;

    openQuestions.append(newOpenQuestion);
    return newWidget;
}

int MainWindow::findOpenQuestionIndex(QWidget *questionWidget) {
    for (int i = 0; i < openQuestions.size(); ++i) {
        if (openQuestions[i].widget == questionWidget) {
            return i;
        }
    }
    return -1;
}

bool MainWindow::insertOpenQuestion(const QString &questionText, const QString &answerText, int score) {
    QSqlQuery query;
    query.prepare("INSERT INTO open_questions (question_text, answer_text, score) VALUES (:question_text, :answer_text, :score)");
    query.bindValue(":question_text", questionText);
    query.bindValue(":answer_text", answerText);
    query.bindValue(":score", score);

    if (!query.exec()) {
        qDebug() << "Couldn't insert open question: " << query.lastError();
        return false;
    }
    return true;
}

void MainWindow::saveAllOpenQuestionsToDatabase() {
    for (const OpenQuestionWidget &openQuestion : openQuestions) {
        if (!insertOpenQuestion(openQuestion.questionTextEdit->toHtml(), openQuestion.answerTextEdit->toHtml(), openQuestion.scoreLineEdit->text().toInt())) {
            qDebug() << "Couldn't insert open question";
        }
    }
}

void MainWindow::loadOpenQuestionsFromDatabase() {
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

        QLabel *answerLabel = new QLabel("Ответ:");
        AutoResizingTextEdit *answerTextEdit = new AutoResizingTextEdit();
        answerTextEdit->setObjectName(QString("openAnswerText_%1").arg(openQuestionCounter));
        answerTextEdit->setHtml(answerText); // Используем setHtml для загрузки HTML

        QPushButton *deleteOpenQuestionButton = new QPushButton("Удалить вопрос");
        connect(deleteOpenQuestionButton, &QPushButton::clicked, [this, newWidget, openQuestionCounter]() {
            removeOpenQuestion(newWidget, openQuestionCounter - 1);
        });

        QPushButton *insertImageButton = new QPushButton("Вставить изображение");
        connect(insertImageButton, &QPushButton::clicked, [this, questionTextEdit]() {
            currentTextEdit = questionTextEdit;
            insertImage();
        });

        QLabel *scoreLabel = new QLabel("Баллы:");
        QLineEdit *scoreLineEdit = new QLineEdit();
        QSpacerItem *spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
        scoreLineEdit->setValidator(new QIntValidator(0, 99, this)); // Только цифры от 0 до 99
        scoreLineEdit->setText(QString::number(score));
        scoreLineEdit->setMaximumWidth(30);

        QHBoxLayout *scoreLayout = new QHBoxLayout();
        scoreLayout->addWidget(scoreLabel);
        scoreLayout->addWidget(scoreLineEdit);
        scoreLayout->addItem(spacer);
        scoreLayout->addWidget(insertImageButton);

        newGridLayout->addLayout(scoreLayout, 3, 0, 1, 3);

        newGridLayout->addWidget(questionLabel, 0, 0, 1, 1);
        newGridLayout->addWidget(deleteOpenQuestionButton, 0, 2, 1, 1, Qt::AlignRight);
        newGridLayout->addWidget(questionTextEdit, 1, 0, 1, 3);
        //newGridLayout->addWidget(insertImageButton, 2, 0, 1, 1);
        newGridLayout->addWidget(answerLabel, 4, 0, 1, 1);
        newGridLayout->addWidget(answerTextEdit, 5, 0, 1, 3);

        ui->verticalLayout_2->addWidget(newWidget);

        OpenQuestionWidget newOpenQuestion;
        newOpenQuestion.widget = newWidget;
        newOpenQuestion.questionTextEdit = questionTextEdit;
        newOpenQuestion.answerTextEdit = answerTextEdit;
        newOpenQuestion.scoreLineEdit = scoreLineEdit;

        openQuestions.append(newOpenQuestion);
        openQuestionCounter++;
    }
}


int MainWindow::findQuestionIndex(QWidget *questionWidget) {
    for (int i = 0; i < questions.size(); ++i) {
        if (questions[i].textEdit->parentWidget() == questionWidget) {
            return i;
        }
    }
    return -1;
}

void MainWindow::on_actionSaveAs_triggered() {
    if (!validateQuestions()) {
        QMessageBox::warning(this, tr("Ошибка"), tr("Некоторые вопросы не имеют правильных ответов."));
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(this, tr("Сохранить базу данных"), "", tr("SQLite Database Files (*.db)"));
    if (fileName.isEmpty())
        return;

    if (connectToDatabase(fileName)) {
        if (createTables()) {
            clearDatabase();
            saveAllQuestionsToDatabase();
            saveScoresToDatabase(); // Сохранение оценок
            currentFileName = fileName;
        }
    }
}

void MainWindow::removeQuestion(QWidget *questionWidget, int questionIndex) {
    questionIndex = findQuestionIndex(questionWidget);

    if (questionIndex >= 0 && questionIndex < questions.size()) {
        ui->verticalLayout_2->removeWidget(questionWidget);
        questionWidget->deleteLater();
        questions.removeAt(questionIndex);

        for (int i = questionIndex; i < questions.size(); ++i) {
            QuestionWidget &question = questions[i];
            question.textEdit->parentWidget()->findChild<QLabel*>()->setText(QString("Вопрос %1").arg(i + 1));
            question.textEdit->parentWidget()->findChild<QPushButton*>(QString("addAnswerButton_%1").arg(i + 2))->setObjectName(QString("addAnswerButton_%1").arg(i + 1));
        }
    }
}

void MainWindow::removeAnswer(QHBoxLayout *answerLayout, QWidget *parentWidget, int row) {
    if (!answerLayout || !parentWidget) return;

    QGridLayout *gridLayoutParent = qobject_cast<QGridLayout*>(parentWidget->layout());
    if (!gridLayoutParent) return;

    while (QLayoutItem* item = answerLayout->takeAt(0)) {
        if (QWidget *widget = item->widget()) {
            widget->deleteLater();
        }
        delete item;
    }

    delete answerLayout;

    gridLayoutParent->removeItem(answerLayout);

    // Поиск индекса вопроса
    int questionIndex = -1;
    for (int i = 0; i < questions.size(); ++i) {
        if (questions[i].textEdit->parentWidget() == parentWidget) {
            questionIndex = i;
            break;
        }
    }

    if (questionIndex >= 0) {
        // Удаление данных из модели
        questions[questionIndex].answers.removeAt(row - 1); // Учитывая, что нумерация строк начинается с 1
    }
}

void MainWindow::on_actionSave_triggered() {
    if (currentFileName.isEmpty()) {
        on_actionSaveAs_triggered(); // Если файл не был сохранен ранее, вызываем диалог сохранения как "Сохранить как"
        return;
    }

    if (!validateQuestions()) {
        QMessageBox::warning(this, tr("Ошибка"), tr("Некоторые вопросы не имеют правильных ответов."));
        return;
    }
    if (connectToDatabase(currentFileName)) {
        if (createTables()) {
            clearDatabase(); // Очищаем базу перед сохранением
            saveAllQuestionsToDatabase();
            saveScoresToDatabase(); // Сохранение оценок
        }
    }
}

void MainWindow::on_actionOpen_triggered() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Открыть базу данных"), "", tr("SQLite Database Files (*.db)"));
    if (fileName.isEmpty())
        return;

    if (connectToDatabase(fileName)) {
        clearAllQuestions(); // Добавляем вызов метода для очистки текущих данных
        loadQuestionsFromDatabase();
        loadScoresFromDatabase(); // Загрузка оценок
        loadOpenQuestionsFromDatabase();
        currentFileName = fileName;
    }
}

void MainWindow::on_actionCreate_triggered() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Создать новую базу данных"), "", tr("SQLite Database Files (*.db)"));
    if (fileName.isEmpty())
        return;

    if (connectToDatabase(fileName)) {
        createTables();
    }
}

bool MainWindow::connectToDatabase(const QString &dbName) {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);

    if (!db.open()) {
        qDebug() << "Error: connection with database failed";
        return false;
    } else {
        qDebug() << "Database: connection ok";
        return true;
    }
}

bool MainWindow::createTables() {
    QSqlQuery query;
    QString createQuestionsTable = "CREATE TABLE IF NOT EXISTS questions ("
                                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                   "question_text TEXT, "
                                   "image BLOB, "
                                   "score INTEGER)"; // Добавлено поле score
    QString createAnswersTable = "CREATE TABLE IF NOT EXISTS answers ("
                                 "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                 "question_id INTEGER, "
                                 "answer_text TEXT, "
                                 "is_correct INTEGER, "
                                 "FOREIGN KEY(question_id) REFERENCES questions(id))";
    QString createOpenQuestionsTable = "CREATE TABLE IF NOT EXISTS open_questions ("
                                       "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                       "question_text TEXT, "
                                       "answer_text TEXT, "
                                       "image BLOB, "
                                       "score INTEGER)"; // Добавлено поле score
    QString createScoresTable = "CREATE TABLE IF NOT EXISTS scores ("
                                "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                "score_satisfactory INTEGER, "
                                "score_good INTEGER, "
                                "score_excellent INTEGER, "
                                "time_test INTEGER)";

    if (!query.exec(createQuestionsTable)) {
        qDebug() << "Couldn't create questions table: " << query.lastError();
        return false;
    }
    if (!query.exec(createAnswersTable)) {
        qDebug() << "Couldn't create answers table: " << query.lastError();
        return false;
    }
    if (!query.exec(createOpenQuestionsTable)) {
        qDebug() << "Couldn't create open questions table: " << query.lastError();
        return false;
    }
    if (!query.exec(createScoresTable)) {
        qDebug() << "Couldn't create scores table: " << query.lastError();
        return false;
    }
    return true;
}

QByteArray imageToByteArray(const QImage &image) {
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG");
    return byteArray;
}

bool MainWindow::insertQuestion(const QString &questionText, int &questionId, int score) {
    QSqlQuery query;
    query.prepare("INSERT INTO questions (question_text, score) VALUES (:question_text, :score)");
    query.bindValue(":question_text", questionText);
    query.bindValue(":score", score);

    qDebug() << "Inserting question with text:" << questionText << "and score:" << score;

    if (!query.exec()) {
        qDebug() << "Couldn't insert question: " << query.lastError();
        return false;
    }

    questionId = query.lastInsertId().toInt(); // Инициализация questionId после успешного вставки
    qDebug() << "Inserted question with ID:" << questionId;
    return true;
}

bool MainWindow::insertAnswer(int questionId, const QString &answerText, bool isCorrect) {
    QSqlQuery query;
    query.prepare("INSERT INTO answers (question_id, answer_text, is_correct) VALUES (:question_id, :answer_text, :is_correct)");
    query.bindValue(":question_id", questionId);
    query.bindValue(":answer_text", answerText);
    query.bindValue(":is_correct", isCorrect);

    qDebug() << "Inserting answer with question ID:" << questionId << ", text:" << answerText << ", is correct:" << isCorrect;

    if (!query.exec()) {
        qDebug() << "Couldn't insert answer: " << query.lastError();
        return false;
    }
    qDebug() << "Inserted answer for question ID:" << questionId;
    return true;
}

void MainWindow::saveAllQuestionsToDatabase() {
    for (const QuestionWidget &question : questions) {
        int questionId;
        int score = question.scoreLineEdit->text().toInt(); // Получаем баллы из поля scoreLineEdit
        qDebug() << "Inserted answer for question ID:";
        if (insertQuestion(question.textEdit->toHtml(), questionId, score)) {
            for (const AnswerWidget &answer : question.answers) {
                insertAnswer(questionId, answer.textEdit->toPlainText(), answer.checkBox->isChecked());
            }
        }
    }
    saveAllOpenQuestionsToDatabase();
}


void MainWindow::saveScoresToDatabase() {
    int scoreSatisfactory = ui->textEditFor3->toPlainText().toInt();
    int scoreGood = ui->textEditFor4->toPlainText().toInt();
    int scoreExcellent = ui->textEditFor5->toPlainText().toInt();
    int timeTest = ui->timeOfTest->toPlainText().toInt();

    QSqlQuery query;
    query.prepare("INSERT OR REPLACE INTO scores (id, score_satisfactory, score_good, score_excellent, time_test) VALUES (1, :score_satisfactory, :score_good, :score_excellent, :time_test)");
    query.bindValue(":score_satisfactory", scoreSatisfactory);
    query.bindValue(":score_good", scoreGood);
    query.bindValue(":score_excellent", scoreExcellent);
    query.bindValue(":time_test", timeTest);

    if (!query.exec()) {
        qDebug() << "Couldn't insert scores: " << query.lastError();
    }
}

void MainWindow::loadQuestionsFromDatabase() {
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

    QuestionWidget newQuestion;
    newQuestion.textEdit = textEdit;

    QPushButton *button = new QPushButton("Добавить\nответ");
    button->setObjectName(QString("addAnswerButton_%1").arg(questionId));
    QPushButton *deleteQuestionButton = new QPushButton("Удалить вопрос");

    connect(deleteQuestionButton, &QPushButton::clicked, [this, newWidget, questionId]() {
        removeQuestion(newWidget, questionId - 1);
    });
    newGridLayout->addWidget(deleteQuestionButton, 0, 2, 1, 1, Qt::AlignRight);
    newGridLayout->addWidget(questionLabel, 0, 0, 1, 2);
    newGridLayout->addWidget(textEdit, 1, 0, 1, 3);
    newGridLayout->addWidget(button, 3, 0, 1, 1, Qt::AlignLeft);

    connect(button, &QPushButton::clicked, this, &MainWindow::addAnswerButton);

    QPushButton *insertImageButton = new QPushButton("Вставить изображение");
    connect(insertImageButton, &QPushButton::clicked, [this, textEdit]() {
        currentTextEdit = textEdit;
        insertImage();
    });



    // Добавляем поле для ввода баллов
    QLabel *scoreLabel = new QLabel("Баллы:");
            QLineEdit *scoreLineEdit = new QLineEdit();
            QSpacerItem *spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
            scoreLineEdit->setValidator(new QIntValidator(0, 99, this)); // Только цифры от 0 до 99
            scoreLineEdit->setText(QString::number(score));
            scoreLineEdit->setMaximumWidth(30);

            QHBoxLayout *scoreLayout = new QHBoxLayout();
            scoreLayout->addWidget(scoreLabel);
            scoreLayout->addWidget(scoreLineEdit);
            scoreLayout->addItem(spacer);
            scoreLayout->addWidget(insertImageButton);

            newGridLayout->addLayout(scoreLayout, 2, 0, 1, 3);

    QSqlQuery answerQuery;
    answerQuery.prepare("SELECT answer_text, is_correct FROM answers WHERE question_id = :question_id");
    answerQuery.bindValue(":question_id", questionId);
    answerQuery.exec();

    int answerCounter = 1;
    while (answerQuery.next()) {
        QString answerText = answerQuery.value(0).toString();
        bool isCorrect = answerQuery.value(1).toBool();

        QCheckBox *checkBox = new QCheckBox();
        checkBox->setChecked(isCorrect);
        AutoResizingTextEdit *answerTextEdit = new AutoResizingTextEdit();
        answerTextEdit->setObjectName(QString("answerText_%1_%2").arg(questionId).arg(answerCounter));
        answerTextEdit->setText(answerText);
        answerTextEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        answerTextEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        answerTextEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        AnswerWidget newAnswer;
        newAnswer.checkBox = checkBox;
        newAnswer.textEdit = answerTextEdit;

        newQuestion.answers.append(newAnswer);

        QHBoxLayout *answerLayout = new QHBoxLayout();
                    answerLayout->addWidget(checkBox);
                    answerLayout->addWidget(answerTextEdit);

        QPushButton *deleteAnswerButton = new QPushButton("Удалить");
                    connect(deleteAnswerButton, &QPushButton::clicked, [this, answerLayout, newWidget, answerCounter]() {
                        removeAnswer(answerLayout, newWidget, answerCounter);
                    });
                    answerLayout->addWidget(deleteAnswerButton);

                    newGridLayout->addLayout(answerLayout, 4 + answerCounter - 1, 0, 1, 3);


        answerCounter++;
    }

    newGridLayout->setColumnStretch(1, 1);
    newWidget->setLayout(newGridLayout);

    ui->verticalLayout_2->addWidget(newWidget);

    newQuestion.scoreLineEdit = scoreLineEdit;
    questions.append(newQuestion);
}

}

void MainWindow::loadScoresFromDatabase() {
    QSqlQuery query("SELECT score_satisfactory, score_good, score_excellent, time_test FROM scores WHERE id = 1");

    if (query.next()) {
        int scoreSatisfactory = query.value(0).toInt();
        int scoreGood = query.value(1).toInt();
        int scoreExcellent = query.value(2).toInt();
        int timeTest = query.value(3).toInt();

        ui->textEditFor3->setPlainText(QString::number(scoreSatisfactory));
        ui->textEditFor4->setPlainText(QString::number(scoreGood));
        ui->textEditFor5->setPlainText(QString::number(scoreExcellent));
        ui->timeOfTest->setPlainText(QString::number(timeTest));
    }
}

void MainWindow::insertImage() {
    if (!currentTextEdit) return;

    QString fileName = QFileDialog::getOpenFileName(this, tr("Выбрать изображение"), "", tr("Images (*.png *.xpm *.jpg *.bmp *.gif)"));
    if (fileName.isEmpty()) return;

    QImage image(fileName);

    // Изменение размера изображения до максимальной ширины, если она превышает 400 пикселей
    const int maxHeight = 400;
    if (image.height() > maxHeight) {
        image = image.scaledToHeight(maxHeight, Qt::SmoothTransformation);
    }

    QTextCursor cursor = currentTextEdit->textCursor();
    //QTextDocument *document = currentTextEdit->document();

    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG");

    QUrl url("data:image/png;base64," + QString(byteArray.toBase64()));

    QTextImageFormat imageFormat;
    imageFormat.setName(url.toString());
    cursor.insertImage(imageFormat);

    // Устанавливаем политику размера на растягивание при необходимости
    currentTextEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

bool MainWindow::validateQuestions() {
    bool allValid = true;
    QStringList errorMessages;

    // Проверка обычных вопросов
    for (const QuestionWidget &question : questions) {
        bool hasCorrectAnswer = false;
        for (const AnswerWidget &answer : question.answers) {
            if (answer.checkBox->isChecked()) {
                hasCorrectAnswer = true;
                break;
            }
        }
        if (!hasCorrectAnswer) {
            errorMessages.append(tr("Каждый вопрос должен иметь хотя бы один правильный ответ."));
            allValid = false;
            break; // Выход из цикла, если найден некорректный вопрос
        }
    }

    // Проверка открытых вопросов
    for (const OpenQuestionWidget &openQuestion : openQuestions) {
        if (openQuestion.answerTextEdit->toPlainText().isEmpty()) {
            errorMessages.append(tr("Открытый вопрос не может быть без ответа."));
            allValid = false;
            break; // Выход из цикла, если найден некорректный открытый вопрос
        }
    }

    // Проверка полей баллов
    if (!validateScores()) {
        allValid = false;
    }

    // Отображение всех собранных сообщений
    if (!allValid && !errorMessages.isEmpty()) {
        QMessageBox::warning(this, tr("Ошибка"), errorMessages.join("\n"));
    }

    return allValid;
}

void MainWindow::clearAllQuestions() {
    // Очистка обычных вопросов
    for (const QuestionWidget &question : questions) {
        QWidget *widget = question.textEdit->parentWidget();
        if (widget) {
            ui->verticalLayout_2->removeWidget(widget);
            widget->deleteLater();
        }
    }
    questions.clear();

    // Очистка открытых вопросов
    for (const OpenQuestionWidget &openQuestion : openQuestions) {
        QWidget *widget = openQuestion.questionTextEdit->parentWidget();
        if (widget) {
            ui->verticalLayout_2->removeWidget(widget);
            widget->deleteLater();
        }
    }
    openQuestions.clear();
}

void MainWindow::clearDatabase() {
    QSqlQuery query;
    qDebug() << "Clearing questions table...";
    if (!query.exec("DELETE FROM questions")) {
        qDebug() << "Error clearing questions table: " << query.lastError();
    }

    qDebug() << "Clearing answers table...";
    if (!query.exec("DELETE FROM answers")) {
        qDebug() << "Error clearing answers table: " << query.lastError();
    }

    qDebug() << "Clearing scores table...";
    if (!query.exec("DELETE FROM scores")) {
        qDebug() << "Error clearing scores table: " << query.lastError();
    }

    qDebug() << "Clearing open_questions table...";
    if (!query.exec("DELETE FROM open_questions")) {
        qDebug() << "Error clearing open_questions table: " << query.lastError();
    }

    qDebug() << "Resetting autoincrement...";
    if (!query.exec("UPDATE sqlite_sequence SET seq=0 WHERE name='questions' OR name='answers' OR name='scores' OR name='open_questions'")) {
        qDebug() << "Error resetting autoincrement for tables: " << query.lastError();
    }
}

