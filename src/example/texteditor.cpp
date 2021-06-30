#include "texteditor.hpp"
#include "events.hpp"

#include <debug_new>
#include <utilitymainwindow.hpp>

TextEditor::TextEditor(QWidget* parent) : QWidget(parent) {
    ui.setupUi(this);
    connect(ui.textEdit->document(),
            &QTextDocument::modificationChanged,
            this,
            &TextEditor::modificationChanged,
            Qt::QueuedConnection);
}

void TextEditor::setText(const QString& text) {
    ui.textEdit->setPlainText(text);
    ui.textEdit->document()->modificationChanged(false);
}

QString TextEditor::getText() { return ui.textEdit->toPlainText(); }

bool TextEditor::isModified() { return ui.textEdit->document()->isModified(); }

void TextEditor::clear() { ui.textEdit->setPlainText(QString()); }

void TextEditor::cut() { ui.textEdit->cut(); }

void TextEditor::copy() { ui.textEdit->copy(); }

void TextEditor::paste() { ui.textEdit->paste(); }

void TextEditor::modificationChanged(bool isModified) {
    // Notify window about document change.
    for (auto const& it : QApplication::topLevelWidgets()) {
        if (it->objectName() == UtilityMainWindow::objectId()) {
            QCoreApplication::sendEvent(it, new DocumentModifiedEvent(isModified));
        }
    }
}
