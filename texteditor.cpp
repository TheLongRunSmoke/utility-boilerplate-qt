#include "texteditor.hpp"

TextEditor::TextEditor(QWidget *parent)
        : QWidget(parent) {
    ui.setupUi(this);
}

TextEditor::~TextEditor() {
}

void TextEditor::setText(const QString &text) {
    ui.textEdit->setPlainText(text);
}

QString TextEditor::getText() {
    return ui.textEdit->toPlainText();
}

bool TextEditor::isModified() {
    return ui.textEdit->document()->isModified();
}

void TextEditor::clear() {
    ui.textEdit->setPlainText(QString());
}


