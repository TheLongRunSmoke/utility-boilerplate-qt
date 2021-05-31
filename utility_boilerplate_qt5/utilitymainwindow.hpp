#ifndef UMAINWINDOW_H
#define UMAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QStatusBar>
#include <QSessionManager>
#include "settings/settingsdialog.hpp"

class UtilityMainWindow : public QMainWindow {

Q_OBJECT

public:
    explicit UtilityMainWindow(QWidget* parent = Q_NULLPTR);

    virtual void loadFile(const QString& fileName);

    /**
     * Just return number to use as object name.
     */
    static QString objectName();

protected:
    QGridLayout* getLayout();

    void closeEvent(QCloseEvent* event) override;

    /**
     * Set current file filename for window.
     *
     * If empty, result of defaultFileName() will be used.
     *
     * @param filePath file path.
     */
    void setCurrentFile(const QString& filePath);

    void createActions();

    virtual void createFileActions(QMenu* menu, QToolBar* toolbar);

    virtual void createEditActions(QMenu* menu, QToolBar* toolbar);

    virtual void createHelpActions(QMenu* menu);

    virtual QString defaultFileName();

    virtual QString getExtensions();

    virtual QIODevice::OpenMode getFileReadMode();

    virtual QIODevice::OpenMode getFileWriteMode();

    virtual bool isFileReadable(const QString& filename);

    virtual bool isFileWritable(const QString& filename);

    virtual void clearDocument() = 0;

    virtual bool isDocumentModified() = 0;

    virtual bool saveFile(const QString& fileName) = 0;

    virtual void about();

    virtual void showSettings();

    template<typename FuncReference>
    QAction* addAction(
            const QString& name,
            const QString& tip,
            FuncReference method,
            QKeySequence::StandardKey keySequence,
            const QIcon& icon = QIcon(),
            QMenu* menu = nullptr,
            QToolBar* toolbar = nullptr);

    template<typename FuncReference>
    QAction* addAction(
            const QString& name,
            const QString& tip,
            FuncReference method,
            QMenu* menu = nullptr,
            QToolBar* toolbar = nullptr);

    template<typename FuncReference>
    QAction* addActionToPosition(
            int position,
            const QString& name,
            const QString& tip,
            FuncReference method,
            QKeySequence::StandardKey keySequence,
            const QIcon& icon = QIcon(),
            QMenu* menu = nullptr,
            QToolBar* toolbar = nullptr);

    /**
     * Add separator in to menu and/or toolbar.
     *
     * @param menu menu pointer, can be nullptr.
     * @param toolBar toolbar pointer, can be nullptr.
     */
    static void addSeparator(
            QMenu* menu,
            QToolBar* toolBar = nullptr);


protected slots:

    void newFile();

    void open();

    void openRecentFile();

    bool save();

    bool saveAs();

    void updateRecentFiles();

    void checkRecentFilesAvailability();

    void exit();

    virtual void cut();

    virtual void copy();

    virtual void paste();

#ifndef QT_NO_SESSIONMANAGER

    void commitData(QSessionManager&);

    bool event(QEvent* event) override;

#endif

private:
    /**
     * Current working file name.
     */
    QString currentFile;

    QGridLayout* mainLayout;

    QMenu* recentFilesSubmenu;

    void createStatusBar();

    void validateGeometry();

    static bool isOnScreen(int pos, int max);

    void resetWindowGeometry();

    void restoreState();

    void saveState();

    /**
     * Check that working file saved interactively.
     *
     * If file modified, dialog shown and UI locked until user select what to do and file actually saved.
     *
     * @return true if file saved.
     */
    bool isSaved();

    bool isFileAccessibleLike(const QString& filename, QIODevice::OpenMode mode);

};

#endif // UMAINWINDOW_H
