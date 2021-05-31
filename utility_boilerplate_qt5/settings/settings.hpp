#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QApplication>
#include <memory>
#include "items/abstract/settingitem.hpp"
#include "items/comboboxitem.hpp"

class Settings : public QSettings {

    using user_settings_t = std::unique_ptr<SettingItem>;

    using user_settings_terator_pair_t =
    std::pair<
            std::list<Settings::user_settings_t>::const_iterator,
            std::list<Settings::user_settings_t>::const_iterator>;

public:

    Settings();

    ~Settings() override;

    QByteArray windowGeometry();

    void setWindowGeometry(const QByteArray& geometry);

    bool hasRecentFiles();

    QStringList recentFiles();

    void putRecentFile(const QString& path);

    user_settings_terator_pair_t items();

    /**
     * Initialize empty settings with defaults.
     */
    void initDefaults();

    void saveUserSettings();

    QString style();

    int recentFilesLimit();

    QByteArray windowState();

    void setWindowState(const QByteArray& state);

protected:

    std::list<user_settings_t> _items = std::list<user_settings_t>();

    void createUserSettings();

    /**
     * Add user setting, that will be shown last in settings window.
     */
    void addUserSetting(SettingItem* pItem);

    /**
     * Add user setting, that will be shown first in settings window.
     */
    void addUserSettingFirst(SettingItem* pItem);

private:

    static QString path();

    inline static QString windowGeometryKey();

    inline static QString windowStateKey();

    inline static QString recentFilesKey();

    static inline QString fileKey();

    void readUserSettings();
};

#endif //SETTINGS_H
