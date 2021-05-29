#include "texteditor.hpp"
#include <debug_new>

TextEditor::TextEditor(QWidget* parent)
        : QWidget(parent) {
    ui.setupUi(this);
}

TextEditor::~TextEditor() {
}

void TextEditor::setText(const QString& text) {
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

void TextEditor::cut() {
    ui.textEdit->cut();
}

void TextEditor::copy() {
    ui.textEdit->copy();
}

void TextEditor::paste() {
    ui.textEdit->paste();
}


