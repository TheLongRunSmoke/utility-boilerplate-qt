#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QWidget>
#include "ui_texteditor.h"

class TextEditor : public QWidget {
Q_OBJECT

public:
    explicit TextEditor(QWidget* parent = Q_NULLPTR);

    ~TextEditor() override;

    void setText(const QString& text);

    QString getText();

    bool isModified();

    void clear();

    void cut();

    void copy();

    void paste();

private:
    Ui::TextEditor ui;
};

#endif // TEXTEDITOR_H

