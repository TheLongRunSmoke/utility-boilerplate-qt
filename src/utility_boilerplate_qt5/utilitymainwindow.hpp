#ifndef UMAINWINDOW_H
#define UMAINWINDOW_H

#include <QAction>
#include <QFrame>
#include <QGridLayout>
#include <QMainWindow>
#include <QMenu>
#include <QSessionManager>
#include <QStatusBar>
#include <QToolBar>

#include "settings/settingsdialog.hpp"

/**
 * Base main window class, use instead of QMainWindow.
 *
 * Provide basic functionality including: menus, toolbars, status bar,
 * handling events (including settings change), interface to read and write
 * working file.
 *
 * Using:
 * 1) Inherit from UtilityMainWindow.
 * 2) Initialize UI in constructor, by Qt documentation. Add you widget for
 * example.
 * 3) Override getExtensions(), getFileReadMode(), getFileWriteMode() to specified file
 * types and read-write modes.
 * 4) Override loadFile(fileName) and saveFile(filename) implementing
 * read and write file from disc. See example for basic variant.
 * 5) Delegate cut(), copy(), paste() to your widget.
 *
 * Instantiate and use as normal:
 *  MainWindow mainWin; <- heir of UtilityMainWindow.
 *  mainWin.show();
 */
class UtilityMainWindow : public QMainWindow {
    Q_OBJECT

  public:
    explicit UtilityMainWindow(QWidget* parent = Q_NULLPTR);

    ~UtilityMainWindow() override;

    /**
     * Handle loading of specified file. Reading from disc must implemented in
     * heir.
     */
    virtual void loadFile(const QString& fileName);

    /**
     * Return number to use as object name.
     *
     * SettingsDialog use object name to determinate what entity must received
     * SettingsChange event.
     */
    static QString objectId();

  protected:
    /**
     * Return pointer on window layout where user widget can be placed.
     */
    QGridLayout* getLayout();

    /**
     * Handle close event to ask user to save document if isDocumentModified() is
     * true.
     */
    void closeEvent(QCloseEvent* event) override;

    /**
     * Set current file filename for window.
     *
     * If empty, result of defaultFileName() will be used.
     *
     * @param filePath file path.
     */
    void setCurrentFile(const QString& filePath);

    /**
     * Create basic actions and fill menu and toolbars with it.
     */
    void createActions();

    /**
     * Populate File menu and toolbar with actions like open, save, recent files
     * and so on.
     */
    virtual void createFileActions(QMenu* menu, QToolBar* toolbar);

    /**
     * Populate Edit menu and toolbar with actions like copy, paste and settings.
     */
    virtual void createEditActions(QMenu* menu, QToolBar* toolbar);

    /**
     * Populate Help menu About and About Qt actions.
     */
    virtual void createHelpActions(QMenu* menu);

    /**
     * Default name for newly created document.
     *
     * @return not nullptr.
     */
    virtual QString defaultFileName();

    /**
     * Extensions list for open-save dialogs. See Qt documentation for details.
     */
    virtual QString getExtensions();

    /**
     * File read mode from QFile, use to specified how Qt must read file from
     * disc.
     */
    virtual QIODevice::OpenMode getFileReadMode();

    /**
     * File write mode from QFile, use to specified how Qt must write file to
     * disc.
     */
    virtual QIODevice::OpenMode getFileWriteMode();

    /**
     * Check that file exist and readable.
     *
     * @return true file can be used.
     * @return false file not exist or user do not have permissions to read it.
     */
    virtual bool isFileReadable(const QString& filename);

    /**
     * Check that file writeable.
     *
     * @return true file can be used.
     * @return false file can not be written for some reason.
     */
    virtual bool isFileWritable(const QString& filename);

    /**
     * Clear and reset user's widget before loading new document.
     */
    virtual void clearDocument() = 0;

    /**
     * Check if document was modified.
     *
     * @return true if modified and need saving.
     */
    virtual bool isDocumentModified() = 0;

    /**
     * Write document to specified file on disc.
     *
     * @param fileName must not be nullptr.
     * @return true if wrote successfully
     * @return false if any error occurred.
     */
    virtual bool saveFile(const QString& fileName) = 0;

    /**
     * Call "About" dialog.
     */
    virtual void about();

    /**
     * Call settings dialog.
     */
    virtual void showSettings();

    /**
     * Add action to a menu and/or toolbar.
     *
     * @tparam FuncReference reference to a function that call on action.
     * @param name action name for menu.
     * @param tip action tooltip for status bar.
     * @param method function to call.
     * @param keySequence shortcut.
     * @param icon QIcon object.
     * @param menu pointer to menu object where action be add. Ignored if nullptr.
     * @param toolbar pointer to toolbar object where action be add. Ignored if
     * nullptr.
     * @return pointer to created action.
     */
    template <typename FuncReference> static inline QAction* addAction(
        const QString& name, const QString& tip,
        typename QtPrivate::FunctionPointer<FuncReference>::Object* receiver, FuncReference method,
        QKeySequence::StandardKey keySequence, const QIcon& icon = QIcon(), QMenu* menu = nullptr,
        QToolBar* toolbar = nullptr) {
        // Create action with or without icon.
        auto* action
            = !icon.isNull() ? new QAction(icon, name, receiver) : new QAction(name, receiver);
        action->setStatusTip(tip);
        // Add hotkey if specified.
        if (keySequence != QKeySequence::StandardKey::UnknownKey) action->setShortcuts(keySequence);
        // Connect to slot and add to menu and toolbar, if specified.
        connect(action, &QAction::triggered, receiver, method, Qt::QueuedConnection);
        if (menu != nullptr) menu->addAction(action);
        if (toolbar != nullptr) toolbar->addAction(action);
        return action;
    }

    /**
     * Add action without icon shortcut to a menu and/or toolbar.
     *
     * @tparam FuncReference reference to a function that call on action.
     * @param name action name for menu.
     * @param tip action tooltip for status bar.
     * @param method function to call.
     * @param menu pointer to menu object where action be add. Ignored if nullptr.
     * @param toolbar pointer to toolbar object where action be add. Ignored if
     * nullptr.
     * @return pointer to created action.
     */
    template <typename FuncReference> static inline QAction* addAction(
        const QString& name, const QString& tip,
        typename QtPrivate::FunctionPointer<FuncReference>::Object* receiver, FuncReference method,
        QMenu* menu = nullptr, QToolBar* toolbar = nullptr) {
        return addAction(name,
                         tip,
                         receiver,
                         method,
                         QKeySequence::StandardKey::UnknownKey,
                         QIcon(),
                         menu,
                         toolbar);
    }

    /**
     * Add action to a menu and/or toolbar in to position.
     *
     * @tparam FuncReference reference to a function that call on action.
     * @param position place to insert action in menu and/or toolbar.
     * @param name action name for menu.
     * @param tip action tooltip for status bar.
     * @param method function to call.
     * @param keySequence shortcut.
     * @param icon QIcon object.
     * @param menu pointer to menu object where action be add. Ignored if nullptr.
     * @param toolbar pointer to toolbar object where action be add. Ignored if
     * nullptr.
     * @return pointer to created action.
     */
    template <typename FuncReference> static inline QAction* addActionToPosition(
        int position, const QString& name, const QString& tip,
        typename QtPrivate::FunctionPointer<FuncReference>::Object* receiver, FuncReference method,
        QKeySequence::StandardKey keySequence, const QIcon& icon = QIcon(), QMenu* menu = nullptr,
        QToolBar* toolbar = nullptr) {
        // Create action with or without icon.
        auto* action
            = !icon.isNull() ? new QAction(icon, name, receiver) : new QAction(name, receiver);
        action->setStatusTip(tip);
        // Add hotkey if specified.
        if (keySequence != QKeySequence::StandardKey::UnknownKey) action->setShortcuts(keySequence);
        // Connect to slot and add to menu and toolbar, if specified.
        connect(action, &QAction::triggered, receiver, method, Qt::QueuedConnection);
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

    /**
     * Add separator in to menu and/or toolbar.
     *
     * @param menu menu pointer, can be nullptr.
     * @param toolBar toolbar pointer, can be nullptr.
     */
    static void addSeparator(QMenu* menu, QToolBar* toolBar = nullptr);

  protected slots:

    /**
     * Create new document. Current document can be interactively saved.
     */
    void newFile();

    /**
     * Open document. Current document can be interactively saved.
     */
    void open();

    /**
     * Open document from recent list. Current document can be interactively
     * saved.
     */
    void openRecentFile();

    /**
     * Save document.
     * @return true if no errors occurred.
     */
    bool save();

    /**
     * Save document as a new file and open it.
     *
     * @return true if no errors occurred.
     */
    bool saveAs();

    /**
     * Read recent file list an populate menu.
     */
    void updateRecentFiles();

    /**
     * Enable/disable recent files submenu.
     */
    void checkRecentFilesAvailability();

    /**
     * Exit application.
     */
    void exit();

    /**
     * Cut selection from active widget in to clipboard. Must be implemented
     * first.
     */
    virtual void cut();

    /**
     * Copy selection from active widget in to clipboard. Must be implemented
     * first.
     */
    virtual void copy();

    /**
     * Paste from clipboard to selections in active widget. Must be implemented
     * first.
     */
    virtual void paste();

    /**
     * Handle events.
     *
     * SettingsChangedEvent, QEvent::LanguageChange and others, processed here.
     *
     * See Qt documentation for details.
     *
     * @return true if event fully handled and must not appear anywhere else.
     * @return false event can be passed next by hierarchy.
     */
    bool event(QEvent* event) override;

#ifndef QT_NO_SESSIONMANAGER

    /**
     * Handle user session. Will non-interactively save document if modified.
     */
    void commitData(QSessionManager&);

#endif

  private:
    /**
     * Current working file name.
     */
    QString _currentFile;

    /**
     * Window layout.
     */
    QGridLayout* _mainLayout;

    /**
     * Recent files submenu.
     */
    QMenu* _recentFilesSubmenu{};

    /**
     * Current application translation object.
     */
    QTranslator* _translator = new QTranslator();

    /**
     * Toolbars. Keep pointer as class member to make possible to change translate
     * on-fly.
     */
    QToolBar* _fileToolBar{};
    QToolBar* _editToolBar{};

    /**
     * Initialize a window status bar.
     */
    void createStatusBar();

    /**
     * Check that window can be seen on current screen, reset geometry otherwise.
     */
    void validateGeometry();

    /**
     * Simply check position to be visible on screen.
     *
     * @param pos position.
     * @param max resolution in particular direction.
     * @return true if on screen.
     */
    static bool isOnScreen(int pos, int max);

    /**
     * Reset window size to be screen quarter and place in to the screen center.
     */
    void resetWindowGeometry();

    /**
     * Restore window state, ex. last toolbars positions.
     */
    void restoreState();

    /**
     * Save window state, ex. toolbars positions.
     */
    void saveState();

    /**
     * Interactively check that working file saved.
     *
     * If file modified, dialog shown and UI locked until user select what to do
     * and file actually saved.
     *
     * @return true if file saved or not modified.
     */
    bool isSaved();

    /**
     * Check that file can be opened in specified mode.
     */
    bool isFileAccessibleLike(const QString& filename, QIODevice::OpenMode mode);

    /**
     * Call UI retranslation. Do it by hand or use ui->retranslateUi().
     */
    virtual void retranslateUi();
};

#endif  // UMAINWINDOW_H
