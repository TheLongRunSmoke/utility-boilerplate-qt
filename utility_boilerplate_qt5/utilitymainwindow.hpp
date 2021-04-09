#ifndef UMAINWINDOW_H
#define UMAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QStatusBar>
#include <QSessionManager>

class UtilityMainWindow : public QMainWindow {

Q_OBJECT

public:
    explicit UtilityMainWindow(QWidget* parent = Q_NULLPTR);

    virtual void loadFile(const QString& fileName);

protected:
    QGridLayout* getLayout();

    void closeEvent(QCloseEvent* event) override;

    void setCurrentFile(const QString& fileName);

    void createActions();

    virtual void createFileActions(QMenu* menu, QToolBar* toolbar);

    virtual void createEditActions(QMenu* menu, QToolBar* toolbar);

    virtual void createHelpActions(QMenu* menu);

    virtual QString getExtensions();

    virtual QIODevice::OpenMode getFileReadMode();

    virtual QIODevice::OpenMode getFileWriteMode();

    virtual bool isFileReadable(QString filename);

    virtual void clearDocument() = 0;

    virtual bool isDocumentModified() = 0;

    virtual bool saveFile(const QString& fileName) = 0;

    template<typename FuncReference>
    void addAction(
            const QIcon& icon,
            const QString& name,
            const QString& tip,
            QKeySequence::StandardKey keySequence,
            FuncReference method,
            QMenu* menu,
            QToolBar* toolbar);

    template<typename FuncReference>
    void addActionToPosition(
            QIcon icon,
            QString name,
            QString tip,
            QKeySequence::StandardKey keySequence,
            int position,
            FuncReference method,
            QMenu* menu,
            QToolBar* toolbar);

protected slots:

    void newFile();

    void open();

    void openRecentFile();

    bool save();

    bool saveAs();

    void about();

    virtual void cut();

    virtual void copy();

    virtual void paste();

#ifndef QT_NO_SESSIONMANAGER

    void commitData(QSessionManager&);

#endif

private:
    QString currentFile;
    QGridLayout* mainLayout;
    QToolBar* fileToolBar{};
    QToolBar* editToolBar{};

    void createStatusBar();

    void validateGeometry();

    bool isOnScreen(int pos, int max);

    void resetWindowGeometry();

    void readSettings();

    void writeSettings();

    bool isSaved();

    QAction* recentFileActs[5]{};
    QAction* recentFileSeparator{};
    QAction* recentFileSubMenuAct{};

    void updateRecentFileActions();

    void setRecentFilesVisible(bool visible);

    struct WrongMenuPosition;
};

#endif // UMAINWINDOW_H