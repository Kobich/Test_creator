#include "AutoResizingTextEdit.h"
#include <QWheelEvent>

AutoResizingTextEdit::AutoResizingTextEdit(QWidget *parent) : QTextEdit(parent) {
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    connect(this, &QTextEdit::textChanged, this, &AutoResizingTextEdit::adjustHeight);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void AutoResizingTextEdit::resizeEvent(QResizeEvent *event) {
    QTextEdit::resizeEvent(event); // Вызываем реализацию базового класса
    adjustHeight();
}

void AutoResizingTextEdit::wheelEvent(QWheelEvent *event) {
    // Не вызываем базовую реализацию, чтобы предотвратить прокрутку
    event->ignore();
}

// Переопределяем события прокрутки для вертикального и горизонтального прокрутки
void AutoResizingTextEdit::scrollContentsBy(int dx, int dy) {
    // Ничего не делаем, чтобы предотвратить прокрутку
    Q_UNUSED(dx);
    Q_UNUSED(dy);
}

void AutoResizingTextEdit::adjustHeight() {
    document()->setTextWidth(width());
    QSize newSize(document()->size().toSize());
    setMinimumHeight(newSize.height() + 15);
}
