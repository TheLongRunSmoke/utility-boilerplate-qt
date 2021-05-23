#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QApplication>
#include <memory>
#include "items/usersettingitem.hpp"
#include "items/comboboxitem.hpp"

class Settings : public QSettings {

    using user_settings_t = std::unique_ptr<UserSettingItem>;

    using user_settings_terator_pair_t =
    std::pair<
            std::list<Settings::user_settings_t>::const_iterator,
            std::list<Settings::user_settings_t>::const_iterator
    >;

public:

    Settings();

    ~Settings() override;

    QByteArray geometry();

    void setGeometry(const QByteArray &geometry);

    bool hasRecentFiles();

    QStringList recentFiles();

    void putRecentFile(const QString &path);

    user_settings_terator_pair_t items();

    /**
     * Initialize empty settings with defaults.
     */
    void initDefaults();

    void saveUserSettings();

    QString style();

protected:

    std::list<user_settings_t> _items = std::list<user_settings_t>();

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