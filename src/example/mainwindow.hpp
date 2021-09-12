#ifndef UTILITY_BOILERPLATE_QT_MAINWINDOW_HPP
#define UTILITY_BOILERPLATE_QT_MAINWINDOW_HPP

#include <utilitymainwindow.hpp>

#include "texteditor.hpp"

/**
 * Main window of your utility.
 *
 * Inheritance from UtilityMainWindow give you a "ready to go" window
 * with menu, status bar and common operation like creating, opening and saving
 * files.
 */
class MainWindow : public UtilityMainWindow {
    Q_OBJECT

  public:
    explicit MainWindow(QWidget* parent = Q_NULLPTR);

    void loadFile(const QString& fileName) override;

  protected:
    QString getExtensions() override;

    QIODevice::OpenMode getFileReadMode() override;

    QIODevice::OpenMode getFileWriteMode() override;

    bool isDocumentModified() override;

    void clearDocument() override;

    bool saveFile(const QString& fileName) override;

    void showSettings() override;

  protected slots:

    void createEditActions(QMenu* menu, QToolBar* toolbar) override;

    void cut() override;

    void copy() override;

    void paste() override;

  private:
    TextEditor* textEditor;  // <- This is your widget.

    void nop(){};
};

#endif  // UTILITY_BOILERPLATE_QT_MAINWINDOW_HPP
