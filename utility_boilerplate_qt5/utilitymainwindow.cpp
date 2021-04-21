#include <QWidget>
#include <QWindow>
#include <QGridLayout>
#include <QCloseEvent>
#include <QGuiApplication>
#include <QScreen>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QFrame>
#include <QFileDialog>
#include <QMessageBox>
#include "utilitymainwindow.hpp"
#include "settings.hpp"
#include "helpers.hpp"

UtilityMainWindow::UtilityMainWindow(QWidget* parent)
        : QMainWindow(parent) {
    auto* mainFrame = new QFrame(this);
    setCentralWidget(mainFrame);
    mainLayout = new QGridLayout(mainFrame);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    createActions();
    createStatusBar();
    readSettings();

#ifndef QT_NO_SESSIONMANAGER
    QGuiApplication::setFallbackSessionManagementEnabled(false);
    connect(qApp, &QGuiApplication::commitDataRequest,
            this, &UtilityMainWindow::commitData);
#endif

    setCurrentFile(QString());
    setUnifiedTitleAndToolBarOnMac(true);
}

void UtilityMainWindow::loadFile(const QString& fileName) {
    setCurrentFile(fileName);
    Settings().putRecentFile(fileName);
    updateRecentFileActions();
}

QGridLayout* UtilityMainWindow::getLayout() {
    return mainLayout;
}

/**
 *
 *
 * @param filePath
 */
void UtilityMainWindow::setCurrentFile(const QString& filePath) {
    currentFile = filePath;
    QString shownName = currentFile;
    if (shownName.isEmpty())
        shownName = defaultFileName();
    setWindowTitle(shownName.append(" - ").append(QCoreApplication::applicationName()));
    setWindowModified(false);
}

/**
 * Initialize menus and toolbars.
 */
void UtilityMainWindow::createActions() {
    QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
    fileToolBar = addToolBar(tr("File"));
    createFileActions(fileMenu, fileToolBar);
    QMenu* editMenu = menuBar()->addMenu(tr("&Edit"));
    editToolBar = addToolBar(tr("Edit"));
    createEditActions(editMenu, editToolBar);
    menuCleanUp(editMenu, editToolBar);
    QMenu* helpMenu = menuBar()->addMenu(tr("&Help"));
    createHelpActions(helpMenu);
}

/**
 * Create File menu and toolbar.
 *
 * @param menu
 * @param toolbar
 */
void UtilityMainWindow::createFileActions(QMenu* menu, QToolBar* toolbar) {
    addAction(
            tr("&New"),
            tr("Create a new file"),
            &UtilityMainWindow::newFile,
            QKeySequence::New,
            QIcon::fromTheme("document-new", QIcon(":/utility_boilerplate_qt5/ic_new")),
            menu,
            toolbar);
    addAction(
            tr("&Open"),
            tr("Open file"),
            &UtilityMainWindow::open,
            QKeySequence::Open,
            QIcon::fromTheme("document-open", QIcon(":/utility_boilerplate_qt5/ic_open")),
            menu,
            toolbar);
    addAction(
            tr("&Save"),
            tr("Save file"),
            &UtilityMainWindow::save,
            QKeySequence::Save,
            QIcon::fromTheme("document-save", QIcon(":/utility_boilerplate_qt5/ic_save")),
            menu,
            toolbar);
    addAction(
            tr("Save as…"),
            tr("Save file as…"),
            &UtilityMainWindow::saveAs,
            menu);
    addSeparator(menu);
    auto* recentFileAction = addAction(
            tr("R&ecent files…"),
            tr("Open recent files."),
            &UtilityMainWindow::exit,
            menu);
    addSeparator(menu);
    addAction(
            tr("E&xit"),
            tr("Quit"),
            &UtilityMainWindow::exit,
            menu);
    checkForRecentFiles(recentFileAction, menu);
}

void UtilityMainWindow::createEditActions(QMenu* menu, QToolBar* toolbar) {

#ifndef QT_NO_CLIPBOARD

    addAction(
            tr("Cu&t"),
            tr("Cut the current selection's contents to the clipboard"),
            &UtilityMainWindow::cut,
            QKeySequence::Cut,
            QIcon::fromTheme("edit-cut", QIcon(":/utility_boilerplate_qt5/ic_cut")),
            menu,
            toolbar);
    addAction(
            tr("&Copy"),
            tr("Copy the current selection's contents to the clipboard"),
            &UtilityMainWindow::copy,
            QKeySequence::Copy,
            QIcon::fromTheme("edit-copy", QIcon(":/utility_boilerplate_qt5/ic_copy")),
            menu,
            toolbar);
    addAction(
            tr("&Paste"),
            tr("Paste the clipboard's contents into the current selection"),
            &UtilityMainWindow::paste,
            QKeySequence::Paste,
            QIcon::fromTheme("edit-paste", QIcon(":/utility_boilerplate_qt5/ic_paste")),
            menu,
            toolbar);
    addSeparator(menu, toolbar);

#endif // !QT_NO_CLIPBOARD

}

void UtilityMainWindow::createHelpActions(QMenu* menu) {
    addAction(
            tr("&About"),
            tr("About application."),
            &UtilityMainWindow::about,
            menu);
    addAction(
            tr("About &Qt"),
            tr("Show the Qt library's About box"),
            &QApplication::aboutQt,
            menu);
}

void UtilityMainWindow::checkForRecentFiles(QAction* action, QMenu* menu) {
    auto* settings = new Settings();
    if (!settings->hasRecentFiles()){
        action->setDisabled(true);
        delete settings;
        return;
    }
}

QString UtilityMainWindow::getExtensions() {
    return tr("All files (*.*)");
}

QIODevice::OpenMode UtilityMainWindow::getFileReadMode() {
    return QFile::ReadOnly;
}

QIODevice::OpenMode UtilityMainWindow::getFileWriteMode() {
    return QFile::WriteOnly;
}

bool UtilityMainWindow::isFileReadable(const QString& filename) {
    QFile file(filename);
    if (!file.open(getFileReadMode())) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                                     .arg(QDir::toNativeSeparators(filename), file.errorString()));
        return false;
    }
    return true;
}

void UtilityMainWindow::newFile() {
    if (!isSaved()) return;
    clearDocument();
    setCurrentFile(QString());
}

void UtilityMainWindow::open() {
    if (!isSaved()) return;
    QFileDialog dialog(this);
    dialog.setWindowModality(Qt::WindowModal);
    dialog.setNameFilter(getExtensions());
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    if (dialog.exec() != QDialog::Accepted)
        return;
    QString file = dialog.selectedFiles().first();
    if (!file.isEmpty())
        loadFile(file);
}

void UtilityMainWindow::openRecentFile() {

}

bool UtilityMainWindow::save() {
    if (currentFile.isEmpty()) {
        return saveAs();
    } else {
        return saveFile(currentFile);
    }
}

bool UtilityMainWindow::saveAs() {
    QFileDialog dialog(this);
    dialog.setWindowModality(Qt::WindowModal);
    dialog.setNameFilter(getExtensions());
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    if (dialog.exec() != QDialog::Accepted)
        return false;
    return saveFile(dialog.selectedFiles().first());
}

void UtilityMainWindow::exit() {
    if (isSaved()) QCoreApplication::quit();
}

void UtilityMainWindow::about() {
    QMessageBox::about(this, tr("About Application"),
                       tr("The <b>Application</b> example demonstrates how to "
                          "write modern GUI applications using Qt, with a menu bar, "
                          "toolbars, and a status bar."));
}

void UtilityMainWindow::cut() {

}

void UtilityMainWindow::copy() {

}

void UtilityMainWindow::paste() {

}

/**
 * Check window geometry. If window not on screen reset to default.
 */
void UtilityMainWindow::validateGeometry() {
    const QRect available = QGuiApplication::primaryScreen()->availableVirtualGeometry();
    const QRect win = geometry();
    if (isOnScreen(win.left(), available.width()) ||
        isOnScreen(win.right(), available.width()) ||
        isOnScreen(win.top(), available.height()) ||
        isOnScreen(win.bottom(), available.height())) {
        resetWindowGeometry();
    }
}

/**
 * Evaluate given coordinate to be seen on actual screen.
 *
 * @param pos position to evaluate.
 * @param max maximum coordinate.
 * @return true if on screen.
 */
bool UtilityMainWindow::isOnScreen(int pos, int max) {
    return pos < 0 || pos > max;
}

/**
 * Reset window size and position to defaults.
 */
void UtilityMainWindow::resetWindowGeometry() {
    // Take screen geometry.
    const QRect availableGeometry = QGuiApplication::primaryScreen()->availableGeometry();
    // Set window size as a screen quarter...
    resize(availableGeometry.width() / 2, availableGeometry.height() / 2);
    // ... and place in screen center.
    move((availableGeometry.width() - width()) / 2,
         (availableGeometry.height() - height()) / 2);
}

/**
 * Read and apply setting.
 */
void UtilityMainWindow::readSettings() {
    Settings settings;
    const QByteArray geometry = settings.geometry();
    if (geometry.isEmpty()) {
        resetWindowGeometry();
    } else {
        restoreGeometry(geometry);
        validateGeometry();
    }
}

void UtilityMainWindow::writeSettings() {
    Settings settings;
    settings.setGeometry(saveGeometry());
}

#ifndef QT_NO_SESSIONMANAGER

void UtilityMainWindow::commitData(QSessionManager& manager) {
    if (manager.allowsInteraction()) {
        if (!isSaved())
            manager.cancel();
    } else {
        // Non-interactive: save without asking
        if (isDocumentModified())
            save();
    }
}

#endif

bool UtilityMainWindow::isSaved() {
    if (!isDocumentModified())
        return true;
    const QMessageBox::StandardButton ret
            = QMessageBox::warning(this, tr("Application"),
                                   tr("The document has been modified.\n"
                                      "Do you want to save your changes?"),
                                   QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    switch (ret) {
        case QMessageBox::Save:
            return save();
        case QMessageBox::Cancel:
            return false;
        default:
            break;
    }
    return true;
}

void UtilityMainWindow::closeEvent(QCloseEvent* event) {
    writeSettings();
    if (isSaved()) {
        event->accept();
    } else {
        event->ignore();
    }
    QWidget::closeEvent(event);
}

void UtilityMainWindow::updateRecentFileActions() {

}

void UtilityMainWindow::setRecentFilesVisible(bool visible) {

}

void UtilityMainWindow::createStatusBar() {
    statusBar()->showMessage(tr("Ready"), 3000);
}

template<typename FuncReference>
QAction* UtilityMainWindow::addAction(const QString& name, const QString& tip,
                                      const FuncReference method, const QKeySequence::StandardKey keySequence,
                                      const QIcon& icon, QMenu* menu, QToolBar* toolbar) {
    // Create action with or without icon.
    auto* action = !icon.isNull() ? new QAction(icon, name, this) : new QAction(name, this);
    action->setStatusTip(tip);
    // Add hotkey if specified.
    if (keySequence != QKeySequence::StandardKey::UnknownKey)
        action->setShortcuts(keySequence);
    // Connect to slot and add to menu and toolbar, if specified.
    connect(action, &QAction::triggered, this, method);
    if (menu != nullptr) menu->addAction(action);
    if (toolbar != nullptr) toolbar->addAction(action);
    return action;
}

template<typename FuncReference>
QAction* UtilityMainWindow::addAction(const QString& name, const QString& tip, FuncReference method, QMenu* menu,
                                      QToolBar* toolbar) {
    return addAction(name, tip, method, QKeySequence::StandardKey::UnknownKey, QIcon(), menu, toolbar);
}

template<typename FuncReference>
void UtilityMainWindow::addActionToPosition(const QIcon icon, const QString name, const QString tip,
                                            const QKeySequence::StandardKey keySequence, const int position,
                                            const FuncReference method, QMenu* menu, QToolBar* toolbar) {

}

QString UtilityMainWindow::defaultFileName() {
    return "untitled";
}

void UtilityMainWindow::addSeparator(QMenu* menu, QToolBar* toolBar) {
    if (menu != nullptr)
        menu->addSeparator();
    if (toolBar != nullptr)
        toolBar->addSeparator();
}

void UtilityMainWindow::menuCleanUp(QMenu* menu, QToolBar* toolbar) {
    if (menu->isEmpty()) menu->setVisible(false);
    if (toolbar == nullptr) return;
    if (toolbar->actions().isEmpty()) toolbar->setVisible(false);
}

