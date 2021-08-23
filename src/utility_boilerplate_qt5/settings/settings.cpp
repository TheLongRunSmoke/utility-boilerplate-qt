#include "settings.hpp"

#include <QDir>
#include <QStyleFactory>
#include <QtDebug>
#include <debug_new>
#include <stdexcept>

#include "items/comboboxitem.hpp"
#include "items/comboboxitemwdata.hpp"
#include "items/spinboxitem.hpp"

const std::map<QString, QString> Settings::KNOWN_LANGUAGE = {{"en", "English"}, {"ru", "Русский"}};

Settings::Settings() : QSettings(path(), QSettings::IniFormat) {
    createBasicSettings();
    readUserSettings();
}

void Settings::createBasicSettings() {
    auto* language = new ComboBoxItemWithData(
        languageKey(), tr("Language"), availableLanguages(), systemLanguage());
    addUserSetting(language);
    auto* theme = new ComboBoxItem(themeKey(),
                                   tr("Theme"),
                                   QStyleFactory::keys(),
                                   QApplication::style()->objectName(),
                                   tr("Application theme"));
    addUserSetting(theme);
    auto* recentFilesLimit = new SpinboxItem(
        recentFilesLimitKey(), tr("Recent files limit"), 0, 10, recentFilesDefault());
    addUserSetting(recentFilesLimit);
}

void Settings::retranslateUi() {
    _items.clear();
    createBasicSettings();
    createUserSettings();
    readUserSettings();
}

void Settings::readUserSettings() {
    for (auto const& it : _items) {
        if (it->isDecoration()) continue;
        auto savedValue = value(key(userSectionTag(), it->key()));
        if (savedValue.isNull()) continue;
        it->setValue(savedValue.toString());
    }
}

QByteArray Settings::windowGeometry() {
    return value(windowGeometryKey(), QByteArray()).toByteArray();
}

void Settings::putWindowGeometry(const QByteArray& geometry) {
    setValue(windowGeometryKey(), geometry);
}

QByteArray Settings::windowState() { return value(windowStateKey(), QByteArray()).toByteArray(); }

void Settings::putWindowState(const QByteArray& state) { setValue(windowStateKey(), state); }

bool Settings::hasRecentFiles() {
    const int count = beginReadArray(recentFilesKey());
    endArray();
    return count > 0;
}

QStringList Settings::recentFiles() {
    QStringList result = QStringList();
    const int count = beginReadArray(recentFilesKey());
    for (int i = 0; i < count; i++) {
        setArrayIndex(i);
        result.append(value(fileKey()).toString());
    }
    endArray();
    return result;
}

void Settings::putRecentFile(const QString& path) {
    QStringList files = recentFiles();
    if (files.contains(path)) return;
    files.insert(0, path);
    const int count = std::min(files.size(), recentFilesLimit());
    beginWriteArray(recentFilesKey());
    for (int i = 0; i < count; ++i) {
        setArrayIndex(i);
        setValue(fileKey(), files.at(i));
    }
    endArray();
}

void Settings::clearRecentFiles() { remove(recentFilesKey()); }

void Settings::setRecentFilesLimit(int value) {
    setValue(key(userSectionTag(), recentFilesLimitKey()), std::max(value, 0));
}

QString Settings::key(const QString& sectionTag, const QString& key) {
    return QString("%1/%2").arg(sectionTag, key);
}

QString Settings::path() { return QCoreApplication::applicationDirPath() + "/settings.ini"; }

inline QString Settings::themeKey() { return {"theme"}; }

inline QString Settings::languageKey() { return {"language"}; }

inline QString Settings::windowGeometryKey() { return {"window_geometry"}; }

inline QString Settings::windowStateKey() { return {"window_state"}; }

inline QString Settings::recentFilesKey() { return {"RecentFiles"}; }

inline QString Settings::fileKey() { return {"file"}; }

Settings::user_settings_terator_pair_t Settings::items() {
    return std::make_pair(_items.cbegin(), _items.cend());
}

Settings::~Settings() { _items.clear(); }

void Settings::saveUserSettings() {
    beginGroup(userSectionTag());
    for (auto const& it : _items) {
        if (it->isDecoration()) continue;
        setValue(it->key(), it->value());
    }
    endGroup();
}

void Settings::addUserSettingFirst(SettingItem* pItem) {
    _items.push_front(std::unique_ptr<SettingItem>(pItem));
}

void Settings::addUserSetting(SettingItem* pItem) {
    _items.push_back(std::unique_ptr<SettingItem>(pItem));
}

void Settings::initDefaults() {
    beginGroup(userSectionTag());
    for (auto const& it : _items) {
        if (it->isDecoration()) continue;
        if (value(it->key()).isNull()) {
            setValue(it->key(), it->defaultValue());
        }
    }
    endGroup();
}

QString Settings::style() { return value(key(userSectionTag(), themeKey()), "").toString(); }

inline QString Settings::recentFilesLimitKey() { return {"recent_files_limit"}; }

int Settings::recentFilesLimit() {
    return value(key(userSectionTag(), recentFilesLimitKey())).toInt();
}

int Settings::recentFilesDefault() { return 5; }

QString Settings::userSectionTag() { return {"User"}; }

QString Settings::systemLanguage() {
    QString defaultLocale = QLocale::system().name();        // Something like "en_US".
    defaultLocale.truncate(defaultLocale.lastIndexOf('_'));  // Simplified to "en".
    return defaultLocale;
}

std::map<QString, QVariant> Settings::availableLanguages() {
    // English inbuilt to sources and don't require QM file.
    auto const& en = KNOWN_LANGUAGE.find("en");
#ifndef NDEBUG
    assert(en != KNOWN_LANGUAGE.end() && "Settings::KNOWN_LANGUAGE missing 'en' entry.");
#endif
    std::map<QString, QVariant> result = {{en->first, en->second}};
    QDir dir(QApplication::applicationDirPath());
    dir.cd(translationsDirectory());
    QStringList fileNames = dir.entryList(QStringList("appcomp_*.qm"));
    for (auto const& it : fileNames) {
        QString locale = it;
        locale.truncate(locale.lastIndexOf('.'));
        locale.remove(0, locale.lastIndexOf('_') + 1);
        QString lang;
        try {
            lang = KNOWN_LANGUAGE.at(locale);
        } catch (std::out_of_range& ex) {
            // If out of range then use Qt, not localized name for language.
            lang = QLocale::languageToString(QLocale(locale).language());
        }
        result[locale] = lang;
    }
    return result;
}

QString Settings::language() { return value(key(userSectionTag(), languageKey())).toString(); }

void Settings::loadTranslation(const QString& language, QTranslator* translator) {
    if (translator->objectName() == language) return;
    QApplication::removeTranslator(translator);
    QLocale locale = QLocale(language);
    QLatin1String filename("appcomp");
    // Search app translation in local directory.
    bool isLoaded = tryingToLoadTranslation(
        translator,
        locale,
        filename,
        QString("Complete translation for %1 load successfully"),
        QString("Can't load complete translation for %1. Searching for basic Qt translation..."));
    if (!isLoaded) {
        tryingToLoadTranslation(translator,
                                locale,
                                QLatin1String("qt"),
                                QString("Basic translation for %1 load successfully"),
                                QString("Can't load any translation for %1"));
    }
    translator->setObjectName(language);
    // Set translation.
    QApplication::installTranslator(translator);
}

bool Settings::tryingToLoadTranslation(QTranslator* translator, const QLocale& locale,
                                       QLatin1String filename, const QString& successMessage,
                                       const QString& failMessage) {
    bool isLoaded = translator->load(locale, filename, QLatin1String("_"), translationsDirectory());
    if (isLoaded) {
        qInfo() << successMessage.arg(locale.name());
    } else {
        qWarning() << failMessage.arg(locale.name());
    }
    return isLoaded;
}

QLatin1String Settings::translationsDirectory() { return QLatin1String("translations"); }
