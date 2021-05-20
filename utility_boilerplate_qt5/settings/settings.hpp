#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QApplication>
#include <QSet>
#include <memory>
#include "items/usersettingitem.hpp"
#include "items/comboboxitem.hpp"

class Settings : public QSettings {

    typedef std::unique_ptr<UserSettingItem> user_settings_uptr;

public:
    Settings();

    ~Settings() override;

    QByteArray geometry();

    void setGeometry(const QByteArray &geometry);

    bool hasRecentFiles();

    QStringList recentFiles();

    void putRecentFile(const QString &path);

    std::list<user_settings_uptr> *items();

    void initDefaults();

    void saveUserSettings();

    QString style();

protected:
    std::list<user_settings_uptr> _items = std::list<user_settings_uptr>();

    void createUserSettings();

    /**
     * Add user setting, that will be shown first in settings window.
     */
    void addUserSettingFirst(UserSettingItem *pItem);

    /**
     * Add user setting, that will be shown last in settings window.
     */
    void addUserSettingLast(UserSettingItem *pItem);

private:

    static QString path();

    inline static QString geometryKey();

    inline static QString recentFilesKey();

    static inline QString fileKey();
};

#endif //SETTINGS_H