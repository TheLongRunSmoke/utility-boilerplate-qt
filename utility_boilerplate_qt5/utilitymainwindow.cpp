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
#include "settings/settingschangedevent.hpp"
#include <debug_new>
#include <QProcess>

UtilityMainWindow::UtilityMainWindow(QWidget* parent)
        : QMainWindow(parent) {
    Settings settings;
    // Set language.
    Settings::loadTranslation(settings.language(), _translator);
    // Set object name, to easily identified this window.
    setObjectName(UtilityMainWindow::objectName());
    auto* mainFrame = new QFrame(this);
    setCentralWidget(mainFrame);
    mainLayout = new QGridLayout(mainFrame);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    createActions();
    createStatusBar();
    restoreState();

#ifndef QT_NO_SESSIONMANAGER
    QGuiApplication::setFallbackSessionManagementEnabled(false);
    connect(qApp, &QGuiApplication::commitDataRequest,
            this, &UtilityMainWindow::commitData);
#endif

    setCurrentFile(QString());
    setUnifiedTitleAndToolBarOnMac(true);
}


UtilityMainWindow::~UtilityMainWindow() {
    QApplication::removeTranslator(_translator);
    _translator->deleteLater();
    menuBar()->clear();
    delete recentFilesSubmenu;
    removeToolBar(_editToolBar);
    delete _editToolBar;
    removeToolBar(_fileToolBar);
    delete _fileToolBar;
    delete mainLayout;
}

bool UtilityMainWindow::event(QEvent* event) {
    if (event->type() == SettingsChangedEvent::type()) {
        Settings settings;
        // Set style.
        QApplication::setStyle(settings.style());
        // Set language.
        Settings::loadTranslation(settings.language(), _translator);
        return true;
    } else if (event->type() == QEvent::LanguageChange) {
        // App translator object change.
        retranslateUi();
    } else if (event->type() == QEvent::LocaleChange) {
        // Stub! There is no points to change app localization on system locale change.
    }
    return QMainWindow::event(event);
}

void UtilityMainWindow::loadFile(const QString& fileName) {
    if (!isFileReadable(fileName)) return;
    setCurrentFile(fileName);
    Settings().putRecentFile(fileName);
}

QGridLayout* UtilityMainWindow::getLayout() {
    return mainLayout;
}

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
    auto* fileMenu = menuBar()->addMenu(tr("&File"));
    _fileToolBar = addToolBar(tr("File"));
    // Do not forget to set a unique name for a toolbar,
    // otherwise window state can't be restored correctly.
    _fileToolBar->setObjectName("file_toolbar");
    createFileActions(fileMenu, _fileToolBar);

    auto* editMenu = menuBar()->addMenu(tr("&Edit"));
    _editToolBar = addToolBar(tr("Edit"));
    _editToolBar->setObjectName("edit_toolbar");
    createEditActions(editMenu, _editToolBar);

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
    connect(menu, &QMenu::aboutToShow, this, &UtilityMainWindow::checkRecentFilesAvailability);
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
    recentFilesSubmenu = menu->addMenu(tr("R&ecent files…"));
    connect(recentFilesSubmenu, &QMenu::aboutToShow, this, &UtilityMainWindow::updateRecentFiles);
    addSeparator(menu);
    addAction(
            tr("E&xit"),
            tr("Quit"),
            &UtilityMainWindow::exit,
            menu);
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

    addAction(
            tr("Se&ttings"),
            tr("Show application settings."),
            &UtilityMainWindow::showSettings,
            menu);

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

void UtilityMainWindow::updateRecentFiles() {
    const QStringList recentFiles = Settings().recentFiles();
    recentFilesSubmenu->clear();
    for (int i = 0; i < recentFiles.size(); ++i) {
        const QString fileName = QFileInfo(recentFiles.at(i)).fileName();
        auto* action = new QAction(
                tr("&%1 %2").arg(i + 1).arg(fileName),
                this);
        action->setData(recentFiles.at(i));
        connect(action, &QAction::triggered, this, &UtilityMainWindow::openRecentFile);
        recentFilesSubmenu->addAction(action);
    }
}

void UtilityMainWindow::checkRecentFilesAvailability() {
    recentFilesSubmenu->setEnabled(Settings().hasRecentFiles());
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

bool UtilityMainWindow::isFileAccessibleLike(const QString& filename, const QIODevice::OpenMode mode) {
    QFile file(filename);
    if (!file.open(mode)) {
        QMessageBox::warning(this, tr("Error"),
                             tr("Cannot open file %1 %2")
                                     .arg(QDir::toNativeSeparators(filename), file.errorString()));
        return false;
    }
    return true;
}

bool UtilityMainWindow::isFileReadable(const QString& filename) {
    return isFileAccessibleLike(filename, getFileReadMode());
}

bool UtilityMainWindow::isFileWritable(const QString& filename) {
    return isFileAccessibleLike(filename, getFileWriteMode());
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
    if (!isSaved()) return;
    if (const auto* action = qobject_cast<const QAction*>(sender()))
        loadFile(action->data().toString());
}

bool UtilityMainWindow::save() {
    if (currentFile.isEmpty()) {
        return saveAs();
    } else {
        if (!isFileWritable(currentFile)) return false;
        if (saveFile(currentFile)) {
            loadFile(currentFile);
            return true;
        } else {
            return false;
        }
    }
}

bool UtilityMainWindow::saveAs() {
    QFileDialog dialog(this);
    dialog.setWindowModality(Qt::WindowModal);
    dialog.setNameFilter(getExtensions());
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    if (dialog.exec() != QDialog::Accepted)
        return false;
    QString file = dialog.selectedFiles().first();
    if (saveFile(file)) {
        loadFile(file);
        return true;
    } else {
        return false;
    }
}

void UtilityMainWindow::exit() {
    if (isSaved()) QCoreApplication::quit();
}

void UtilityMainWindow::about() {
    QMessageBox about;
    about.setTextFormat(Qt::RichText);
    about.setStandardButtons(QMessageBox::Ok);
    about.setWindowTitle(tr("About Utility Boilerplate Qt"));
    about.setText(tr("This is example shows how to crate simple utility application "
                     "using Utility Boilerplate Qt5. For details see\n"
                     "<a href='https://github.com/TheLongRunSmoke/utility-boilerplate-qt'>"
                     "https://github.com/TheLongRunSmoke/utility-boilerplate-qt</a>"));
    about.exec();
}

/**
 * Cut operation slot. Can't be pure virtual, due Qt restriction.
 */
void UtilityMainWindow::cut() {
    QMessageBox::warning(this, tr("Warning"),
                         tr("Not implemented yet. Override UtilityMainWindow::cut() slot before using."));
}

/**
 * Copy operation slot. Can't be pure virtual, due Qt restriction.
 */
void UtilityMainWindow::copy() {
    QMessageBox::warning(this, tr("Warning"),
                         tr("Not implemented yet. Override UtilityMainWindow::copy() slot before using."));
}

/**
 * Paste operation slot. Can't be pure virtual, due Qt restriction.
 */
void UtilityMainWindow::paste() {
    QMessageBox::warning(this, tr("Warning"),
                         tr("Not implemented yet. Override UtilityMainWindow::paste() slot before using."));
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
void UtilityMainWindow::restoreState() {
    Settings settings;
    const QByteArray windowGeometry = settings.windowGeometry();
    if (windowGeometry.isEmpty()) {
        resetWindowGeometry();
    } else {
        restoreGeometry(windowGeometry);
        validateGeometry();
    }
    const QByteArray windowState = settings.windowState();
    if (windowState.isEmpty()) return;
    QMainWindow::restoreState(windowState, 0);
}

void UtilityMainWindow::saveState() {
    Settings settings;
    settings.setWindowGeometry(saveGeometry());
    settings.setWindowState(QMainWindow::saveState(0));
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
    if (!isDocumentModified())return true;
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
    saveState();
    if (isSaved()) {
        event->accept();
    } else {
        event->ignore();
    }
    QWidget::closeEvent(event);
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
    connect(action, &QAction::triggered, this, method, Qt::QueuedConnection);
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
QAction*
UtilityMainWindow::addActionToPosition(int position, const QString& name, const QString& tip, FuncReference method,
                                       QKeySequence::StandardKey keySequence, const QIcon& icon, QMenu* menu,
                                       QToolBar* toolbar) {
    // Create action with or without icon.
    auto* action = !icon.isNull() ? new QAction(icon, name, this) : new QAction(name, this);
    action->setStatusTip(tip);
    // Add hotkey if specified.
    if (keySequence != QKeySequence::StandardKey::UnknownKey)
        action->setShortcuts(keySequence);
    // Connect to slot and add to menu and toolbar, if specified.
    connect(action, &QAction::triggered, this, method, Qt::QueuedConnection);
    if (menu != nullptr) {
        auto* beforeAction = menu->actions().at(position);
        menu->insertAction(beforeAction, action);
    }
    if (toolbar != nullptr) {
        auto* beforeAction = toolbar->actions().at(position);
        toolbar->insertAction(beforeAction, action);
    }
    return action;
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

void UtilityMainWindow::showSettings() {
    SettingsDialog(new Settings()).exec();
}

QString UtilityMainWindow::objectName() {
    return QString::number(1000, 10);
}

void UtilityMainWindow::retranslateUi() {
    // Clear menu and toolbars.
    menuBar()->clear();
    removeToolBar(_fileToolBar);
    removeToolBar(_editToolBar);
    // Recreate.
    createActions();
}
