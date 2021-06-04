#ifndef UTILITY_BOILERPLATE_QT_SETTINGS_HPP
#define UTILITY_BOILERPLATE_QT_SETTINGS_HPP

#include <QSettings>
#include <QApplication>
#include <QStringList>
#include <QTranslator>
#include <memory>
#include "items/abstract/settingitem.hpp"

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

    QString language();

    static void loadTranslation(const QString& language, QTranslator* translator);

protected:

    std::list<user_settings_t> _items = std::list<user_settings_t>();

    /**
     * Initialize, but not load, basic user settings.
     */
    void createUserSettings();

    virtual QString userSectionTag();

    /**
     * Add user setting, that will be shown last in settings window.
     */
    void addUserSetting(SettingItem* pItem);

    /**
     * Add user setting, that will be shown first in settings window.
     */
    void addUserSettingFirst(SettingItem* pItem);

    /**
     * Override to specified own value.
     *
     * Default is 5.
     */
    virtual int recentFilesDefault();

    void readUserSettings();

private:

    static QString path();

    inline static QString windowGeometryKey();

    inline static QString windowStateKey();

    inline static QString recentFilesKey();

    static inline QString fileKey();

    static QString systemLanguage();

    static std::map<QString, QVariant> availableLanguages();

    static const std::map<QString, QString> KNOWN_LANGUAGE;
};

#endif //UTILITY_BOILERPLATE_QT_SETTINGS_HPP
