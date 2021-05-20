#include <QCoreApplication>
#include "settings.hpp"
#include "items/comboboxitem.hpp"
#include <debug_new>
#include <QStyleFactory>


Settings::Settings() : QSettings(path(), QSettings::IniFormat) {
    createUserSettings();
}

void Settings::createUserSettings() {
    addUserSettingFirst(
            new ComboBoxItem("theme", tr("Theme"), QStyleFactory::keys())
    );
}

QByteArray Settings::geometry() {
    return value(geometryKey(), QByteArray()).toByteArray();
}

void Settings::setGeometry(const QByteArray &geometry) {
    setValue(geometryKey(), geometry);
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

void Settings::putRecentFile(const QString &path) {
    QStringList files = recentFiles();
    if (files.contains(path)) return;
    files.insert(0, path);
    const int count = std::min(files.size(), 5);
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

inline QString Settings::geometryKey() {
    return QString("geometry");
}

inline QString Settings::recentFilesKey() {
    return QString("recent");
}

inline QString Settings::fileKey() {
    return QString("file");
}

std::list<std::unique_ptr<UserSettingItem>> *Settings::items() {
    return &_items;
}

Settings::~Settings() {
    _items.clear();
}

void Settings::saveUserSettings() {
    for (auto const &it : _items) {
        setValue(it->key(), it->value());
    }
}

void Settings::addUserSettingFirst(UserSettingItem *pItem) {
    _items.push_front(std::unique_ptr<UserSettingItem>(pItem));
}

void Settings::addUserSettingLast(UserSettingItem *pItem) {
    _items.push_back(std::unique_ptr<UserSettingItem>(pItem));
}

void Settings::initDefaults() {
    for (auto const &it : _items) {
        if (value(it->key()).isNull()) {
            setValue(it->key(), it->defaultValue());
        }
    }
}

QString Settings::style() {
    return value("theme", "").toString();
}


