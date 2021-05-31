#include <QCoreApplication>
#include <QStyleFactory>
#include "settings.hpp"
#include "items/textitem.hpp"
#include "items/spinboxitem.hpp"
#include <debug_new>

Settings::Settings() : QSettings(path(), QSettings::IniFormat) {
    createUserSettings();
    readUserSettings();
}

void Settings::createUserSettings() {
    auto* theme = new ComboBoxItem(
            "theme",
            tr("Theme"),
            QStyleFactory::keys(),
            QApplication::style()->objectName(),
            tr("Application theme"));
    addUserSetting(theme);
    auto* recentFilesLimit = new SpinboxItem(
            "recent_files_limit",
            tr("Recent files limit"),
            0,
            10,
            5);
    addUserSetting(recentFilesLimit);
}

void Settings::readUserSettings() {
    for (auto const& it : _items) {
        if (it->isDecoration()) continue;
        auto savedValue = value("User/" + it->key());
        if (savedValue.isNull()) continue;
        it->setValue(savedValue.toString());
    }
}

QByteArray Settings::windowGeometry() {
    return value(windowGeometryKey(), QByteArray()).toByteArray();
}

void Settings::setWindowGeometry(const QByteArray& geometry) {
    setValue(windowGeometryKey(), geometry);
}

QByteArray Settings::windowState() {
    return value(windowStateKey(), QByteArray()).toByteArray();
}

void Settings::setWindowState(const QByteArray& state) {
    setValue(windowStateKey(), state);
}

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

QString Settings::path() {
    return QCoreApplication::applicationDirPath() + "/settings.ini";
}

inline QString Settings::windowGeometryKey() {
    return QString("window_geometry");
}

inline QString Settings::windowStateKey() {
    return QString("window_state");
}

inline QString Settings::recentFilesKey() {
    return QString("RecentFiles");
}

inline QString Settings::fileKey() {
    return QString("file");
}

Settings::user_settings_terator_pair_t Settings::items() {
    return std::make_pair(_items.cbegin(), _items.cend());
}

Settings::~Settings() {
    _items.clear();
}

void Settings::saveUserSettings() {
    beginGroup("User");
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
    beginGroup("User");
    for (auto const& it : _items) {
        if (it->isDecoration()) continue;
        if (value(it->key()).isNull()) {
            setValue(it->key(), it->defaultValue());
        }
    }
    endGroup();
}

QString Settings::style() {
    return value("User/theme", "").toString();
}

int Settings::recentFilesLimit() {
    return value("User/recent_files_limit").toInt();
}
