#include "main_screen.h"
#include "ui_main_screen.h"
#include <QFileDialog>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QMessageBox>
#include "test_screen.h"

Main_screen::Main_screen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Main_screen),
    startTestButton(nullptr) // инициализация указателя
{
    ui->setupUi(this);
    connect(ui->chooseTestButton, &QPushButton::clicked, this, &Main_screen::chooseTestButtonClicked);
}

Main_screen::~Main_screen()
{
    db.close();
    delete ui;
}

bool Main_screen::openDatabase(const QString &fileName)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(fileName);

    if (!db.open()) {
        qDebug() << "Ошибка открытия базы данных";
        return false;
    }

    if (!checkDatabaseSchema()) {
        QMessageBox::warning(this, tr("Ошибка базы данных"), tr("База данных не соответствует ожидаемой схеме."));
        db.close();
        return false;
    }

    // Загрузка данных из базы данных
    QSqlQuery query;
    if (query.exec("SELECT score_satisfactory, score_good, score_excellent, time_test FROM scores")) {
        if (query.next()) {
            scoreSatisfactory = query.value(0).toInt();
            scoreGood = query.value(1).toInt();
            scoreExcellent = query.value(2).toInt();
            timeTest = query.value(3).toInt();

            ui->textEditFor3_2->setText(QString::number(scoreSatisfactory));
            ui->textEditFor4_2->setText(QString::number(scoreGood));
            ui->textEditFor5_2->setText(QString::number(scoreExcellent));
            ui->timeOfTest_2->setText(QString::number(timeTest));

            // Проверяем, существует ли кнопка, и если нет, создаем её
            if (!startTestButton) {
                startTestButton = new QPushButton("Начать тестирование", this);
                ui->gridLayout->addWidget(startTestButton);
                connect(startTestButton, &QPushButton::clicked, this, &Main_screen::startTestButtonClicked);
            }
        } else {
            qDebug() << "Данные оценок и времени теста не найдены";
            return false;
        }
    } else {
        qDebug() << "Ошибка выполнения SQL-запроса:" << query.lastError().text();
        return false;
    }

    return true;
}

bool Main_screen::checkDatabaseSchema()
{
    QSqlQuery query;

    // Проверка наличия таблицы scores
    if (!query.exec("SELECT name FROM sqlite_master WHERE type='table' AND name='scores'")) {
        qDebug() << "Ошибка проверки схемы базы данных:" << query.lastError().text();
        return false;
    }

    if (!query.next()) {
        qDebug() << "Таблица scores отсутствует";
        return false;
    }

    // Проверка столбцов в таблице scores
    QStringList requiredColumnsScores = {"score_satisfactory", "score_good", "score_excellent", "time_test"};
    if (!query.exec("PRAGMA table_info(scores)")) {
        qDebug() << "Ошибка получения информации о таблице scores:" << query.lastError().text();
        return false;
    }

    QStringList existingColumnsScores;
    while (query.next()) {
        existingColumnsScores << query.value(1).toString();
    }

    for (const QString &col : requiredColumnsScores) {
        if (!existingColumnsScores.contains(col)) {
            qDebug() << "Таблица scores не соответствует ожидаемой схеме";
            return false;
        }
    }

    // Проверка других таблиц и их столбцов
    struct TableSchema {
        QString tableName;
        QStringList columns;
    };

    QList<TableSchema> tableSchemas = {
        {"questions", {"id", "question_text", "image", "score"}},
        {"answers", {"id", "question_id", "answer_text", "is_correct"}},
        {"open_questions", {"id", "question_text", "answer_text", "image", "score"}}
    };

    for (const TableSchema &schema : tableSchemas) {
        if (!query.exec(QString("SELECT name FROM sqlite_master WHERE type='table' AND name='%1'").arg(schema.tableName))) {
            qDebug() << "Ошибка проверки схемы базы данных:" << query.lastError().text();
            return false;
        }

        if (!query.next()) {
            qDebug() << "Таблица" << schema.tableName << "отсутствует";
            return false;
        }

        if (!query.exec(QString("PRAGMA table_info(%1)").arg(schema.tableName))) {
            qDebug() << "Ошибка получения информации о таблице" << schema.tableName << ":" << query.lastError().text();
            return false;
        }

        QStringList existingColumns;
        while (query.next()) {
            existingColumns << query.value(1).toString();
        }

        for (const QString &col : schema.columns) {
            if (!existingColumns.contains(col)) {
                qDebug() << "Таблица" << schema.tableName << "не соответствует ожидаемой схеме";
                return false;
            }
        }
    }

    return true;
}

void Main_screen::chooseTestButtonClicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Выбрать базу данных теста"),
                                                    QDir::homePath(),
                                                    tr("Файлы баз данных (*.db *.sqlite);;Все файлы (*)"));
    if (!fileName.isEmpty()) {
        if (!openDatabase(fileName)) {
            qDebug() << "Ошибка открытия базы данных";
        }
    }
}

void Main_screen::startTestButtonClicked()
{
    emit startTestClicked(timeTest, db);
}
