#include <QWidget>
#include <QGridLayout>
#include <QCloseEvent>
#include <QGuiApplication>
#include <QSettings>
#include <QScreen>
#include <QString>
#include <QMenu>
#include <QStatusBar>
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

void UtilityMainWindow::setCurrentFile(const QString& fileName) {
    currentFile = fileName;
    setWindowModified(false);
    QString shownName = currentFile;
    if (shownName.isEmpty())
        shownName = "untitled";
    setWindowFilePath(shownName);
    currentFile = fileName;
    setWindowTitle(currentFile);
}

void UtilityMainWindow::createActions() {
    QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
    fileToolBar = addToolBar(tr("File"));
    addAction(
            QIcon::fromTheme("document-new", QIcon(":/utility_boilerplate_qt5/ic_new")),
            tr("&New"),
            tr("Create a new file"),
            QKeySequence::New,
            &UtilityMainWindow::newFile,
            fileMenu,
            fileToolBar);
    addAction(
            QIcon::fromTheme("document-open", QIcon(":/utility_boilerplate_qt5/ic_open")),
            tr("&Open"),
            tr("Open file"),
            QKeySequence::Open,
            &UtilityMainWindow::open,
            fileMenu,
            fileToolBar);
}

void UtilityMainWindow::createFileActions(QMenu* menu, QToolBar* toolbar) {

}

void UtilityMainWindow::createEditActions(QMenu* menu, QToolBar* toolbar) {

}

void UtilityMainWindow::createHelpActions(QMenu* menu) {

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

bool UtilityMainWindow::isFileReadable(const QString filename) {
//    QFile file(fileName);
//    if (!file.open(QFile::ReadOnly | QFile::Text)) {
//        QMessageBox::warning(this, tr("Application"),
//                             tr("Cannot read file %1:\n%2.")
//                                     .arg(QDir::toNativeSeparators(fileName), file.errorString()));
//        return;
//    }
    return true;
}

void UtilityMainWindow::newFile() {
    if (!isSaved()) return;
    clearDocument();
    setCurrentFile(QString());
}

void UtilityMainWindow::open() {
    if (!isSaved()) return;
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty())
        loadFile(fileName);
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
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    if (dialog.exec() != QDialog::Accepted)
        return false;
    return saveFile(dialog.selectedFiles().first());
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
    const QRect available = screen()->availableVirtualGeometry();
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
    const QRect availableGeometry = screen()->availableGeometry();
    resize(availableGeometry.width() / 3, availableGeometry.height() / 2);
    // Place window in screen center.
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
//    if (manager.allowsInteraction()) {
//        if (!maybeSave())
//            manager.cancel();
//    } else {
//        // Non-interactive: save without asking
//        //if (textEdit->document()->isModified())
//        //	save();
//    }
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
    if (isSaved()) {
        writeSettings();
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
void UtilityMainWindow::addAction(const QIcon& icon, const QString& name, const QString& tip,
                                  const QKeySequence::StandardKey keySequence, const FuncReference method,
                                  QMenu* menu, QToolBar* toolbar) {
    auto* action = new QAction(icon, name, this);
    action->setStatusTip(tip);
    action->setShortcuts(keySequence);
    connect(action, &QAction::triggered, this, method);
    menu->addAction(action);
    toolbar->addAction(action);
}

template<typename FuncReference>
void UtilityMainWindow::addActionToPosition(const QIcon icon, const QString name, const QString tip,
                                            const QKeySequence::StandardKey keySequence, const int position,
                                            const FuncReference method, QMenu* menu, QToolBar* toolbar) {

}
