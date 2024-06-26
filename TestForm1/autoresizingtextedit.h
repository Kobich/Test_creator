#ifndef AUTORESIZINGTEXTEDIT_H
#define AUTORESIZINGTEXTEDIT_H

#include <QTextEdit>

class AutoResizingTextEdit : public QTextEdit {
    Q_OBJECT

public:
    AutoResizingTextEdit(QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void scrollContentsBy(int dx, int dy) override;

private slots:
    void adjustHeight();
};

#endif // AUTORESIZINGTEXTEDIT_H
