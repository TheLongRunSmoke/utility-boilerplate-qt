#ifndef UTILITY_BOILERPLATE_QT_SETTINGS_HPP
#define UTILITY_BOILERPLATE_QT_SETTINGS_HPP

#include <QApplication>
#include <QSettings>
#include <QStringList>
#include <QTranslator>
#include <memory>

#include "items/abstract/settingitem.hpp"

/**
 * Base class for application settings.
 *
 * Provide theme, language and recent file limit settings.
 * Override createUserSettings() to add more.
 */
class Settings : public QSettings {
    Q_DECLARE_TR_FUNCTIONS(Settings)

    using user_settings_t = std::unique_ptr<SettingItem>;

    using user_settings_terator_pair_t
        = std::pair<std::list<Settings::user_settings_t>::const_iterator,
                    std::list<Settings::user_settings_t>::const_iterator>;

  public:
    Settings();

    ~Settings() override;

    /**
     * Return saved window size and position.
     *
     * @return nullptr if empty.
     */
    QByteArray windowGeometry();

    /**
     * Save window size and position.
     */
    void setWindowGeometry(const QByteArray& geometry);

    /**
     * Effectively check that application have recently opened files.
     *
     * @return true has not empty list of recent files, false otherwise.
     */
    bool hasRecentFiles();

    /**
     * Read list of recently opened files.
     *
     * @return empty or populated list.
     */
    QStringList recentFiles();

    /**
     * Recent files limit specified by user.
     */
    int recentFilesLimit();

    /**
     * Save path to list of recent opened paths.
     * FIFO logic applied.
     */
    void putRecentFile(const QString& path);

    /**
     * Return iterators to look through settings list.
     * Constants, list can not be changed.
     */
    user_settings_terator_pair_t items();

    /**
     * Initialize empty settings with defaults.
     */
    void initDefaults();

    /**
     * Collect and write to file settings from list, one by one.
     */
    void saveUserSettings();

    /**
     * Read values from a file and initialize user settings.
     */
    void readUserSettings();

    /**
     * Saved style name.
     *
     * @return nullptr if empty.
     */
    QString style();

    /**
     * Saved window state, including toolbars position.
     * Note, toolbar mast have unique name set by setObjectName() to save-restore
     * correctly.
     *
     * @return nullptr if empty.
     */
    QByteArray windowState();

    /**
     * Save window state.
     */
    void setWindowState(const QByteArray& state);

    /**
     * Saved interface language.
     *
     * @return nullptr if empty.
     */
    QString language();

    /**
     * Load application translation.
     *
     * @param language 2 chars code like "en", "ru", etc.
     * @param translator translator object pointer.
     */
    static void loadTranslation(const QString& language, QTranslator* translator);

    /**
     * Recreate settings list to catch translation change.
     */
    virtual void retranslateUi();

  protected:
    /**
     * List of user settings. Initialized in createBasicSettings() and
     * createUserSettings().
     */
    std::list<user_settings_t> _items = std::list<user_settings_t>();

    /**
     * Initialize, but not load, basic user settings.
     */
    void createBasicSettings();

    /**
     * Override this method to add you application setting.
     */
    virtual void createUserSettings(){};

    /**
     * Tag of INI file section where settings from _items stored.
     *
     * Use userSectionTag() + "/" + "<setting_key>" to access.
     */
    virtual QString userSectionTag();

    /**
     * Add user setting, that will be shown last in settings dialog.
     */
    void addUserSetting(SettingItem* pItem);

    /**
     * Add user setting, that will be shown first in settings dialog.
     */
    void addUserSettingFirst(SettingItem* pItem);

    /**
     * Default limit of recent files. Override to specified own value.
     *
     * Default is 5.
     */
    virtual int recentFilesDefault();

  private:
    /**
     * Path to INI file, where setting stored.
     */
    static QString path();

    inline static QString windowGeometryKey();

    inline static QString windowStateKey();

    inline static QString recentFilesKey();

    static inline QString fileKey();

    /**
     * Get system interface language.
     *
     * @return 2 chars code like "en", "ru", etc.
     */
    static QString systemLanguage();

    /**
     * Look through i18n folder and return list of available translations.
     *
     * @return list, guaranty has "en" key. Key is 2 chars language code, value -
     * user-friendly language name.
     */
    static std::map<QString, QVariant> availableLanguages();

    /**
     * Contain localized language name. Key is 2 chars code like "en", "ru", etc.
     *
     * Used to provide user-friendly language name.
     *
     * If this list do not have entry for some key availableLanguages() return
     * english name of that language.
     */
    static const std::map<QString, QString> KNOWN_LANGUAGE;
};

#endif  // UTILITY_BOILERPLATE_QT_SETTINGS_HPP
