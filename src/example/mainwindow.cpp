#include "mainwindow.hpp"

#include <QDir>
#include <QMessageBox>
#include <QSaveFile>
#include <QTextStream>
#include <debug_new>
#include "texteditorsettings.hpp"

MainWindow::MainWindow(QWidget* parent) : UtilityMainWindow(parent) {
    // Set icon for that window.
    QMainWindow::setWindowIcon(QIcon(":/app/icon"));
    // Init UI.
    textEditor = new TextEditor();
    getLayout()->addWidget(textEditor);
}

void MainWindow::loadFile(const QString& fileName) {
    UtilityMainWindow::loadFile(fileName);
    QFile file(fileName);
    file.open(getFileReadMode());
    QTextStream in(&file);
    textEditor->setText(in.readAll());
    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
}

bool MainWindow::saveFile(const QString& fileName) {
    QString errorMessage;
    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
    QSaveFile file(fileName);
    if (file.open(getFileWriteMode())) {
        QTextStream out(&file);
        out << textEditor->getText();
        if (!file.commit()) {
            errorMessage = tr("Cannot write to file %1:\n%2.")
                               .arg(QDir::toNativeSeparators(fileName), file.errorString());
        }
    } else {
        errorMessage = tr("Cannot open file %1 for writing:\n%2.")
                           .arg(QDir::toNativeSeparators(fileName), file.errorString());
    }
    QGuiApplication::restoreOverrideCursor();
    if (!errorMessage.isEmpty()) {
        QMessageBox::warning(this, tr("Application"), errorMessage);
        return false;
    }
    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}

QString MainWindow::getExtensions() { return tr("Text files(*.txt);;All files (*.*)"); }

QIODevice::OpenMode MainWindow::getFileReadMode() { return QFile::ReadOnly | QFile::Text; }

QIODevice::OpenMode MainWindow::getFileWriteMode() { return QFile::WriteOnly | QFile::Text; }

bool MainWindow::isDocumentModified() { return textEditor->isModified(); }

void MainWindow::clearDocument() { textEditor->clear(); }

/**
 * To support copy-paste functional, pass this call to widget in focus. Only one
 * widget here.
 */
void MainWindow::cut() { textEditor->cut(); }

/**
 * To support copy-paste functional, pass this call to widget in focus. Only one
 * widget here.
 */
void MainWindow::copy() { textEditor->copy(); }

/**
 * To support copy-paste functional, pass this call to widget in focus. Only one
 * widget here.
 */
void MainWindow::paste() { textEditor->paste(); }

void MainWindow::showSettings() { SettingsDialog(new TextEditorSettings()).exec(); }

/**
 * How to add your actions to menus.
 */
void MainWindow::createEditActions(QMenu* menu, QToolBar* toolbar) {
    UtilityMainWindow::createEditActions(menu, toolbar);
    addActionToPosition(0,
                        "first example action",
                        "first example action tip",
                        this,
                        &MainWindow::nop,
                        QKeySequence::UnknownKey,
                        QIcon(),
                        menu);
    addSeparator(menu);
    addAction("last example action",
              "last example action tip",
              this,
              &MainWindow::nop,
              QKeySequence::UnknownKey,
              QIcon(),
              menu);
}
