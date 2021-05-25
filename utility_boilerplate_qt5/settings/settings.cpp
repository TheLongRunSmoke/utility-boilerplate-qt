#include <QCoreApplication>
#include <QStyleFactory>
#include "settings.hpp"
#include "items/comboboxitem.hpp"
#include "items/checkboxitem.hpp"
#include "items/separatoritem.hpp"
#include <debug_new>

Settings::Settings() : QSettings(path(), QSettings::IniFormat) {
    createUserSettings();
    readUserSettings();
}

void Settings::createUserSettings() {
    auto *item = new ComboBoxItem(
            "theme",
            tr("Theme"),
            QStyleFactory::keys(),
            QApplication::style()->objectName());
    addUserSettingFirst(item);
    addUserSettingLast(new SeparatorItem());
    auto *checkBoxFalse = new CheckBoxItem(
            "checkbox_default_false",
            tr("Default false"));
    addUserSettingLast(checkBoxFalse);
    auto *checkBoxTrue = new CheckBoxItem(
            "checkbox_default_true",
            tr("Default true"),
            true);
    addUserSettingLast(checkBoxTrue);
}

void Settings::readUserSettings() {
    for (auto const &it : _items) {
        if (it->key().isEmpty()) continue;
        auto savedValue = value("User/" + it->key());
        if (savedValue.isNull()) continue;
        it->setValue(savedValue.toString());
    }
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
    return QString("Recent");
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
    for (auto const &it : _items) {
        if (it->key().isEmpty()) continue;
        setValue(it->key(), it->value());
    }
    endGroup();
}

void Settings::addUserSettingFirst(UserSettingItem *pItem) {
    _items.push_front(std::unique_ptr<UserSettingItem>(pItem));
}

void Settings::addUserSettingLast(UserSettingItem *pItem) {
    _items.push_back(std::unique_ptr<UserSettingItem>(pItem));
}

void Settings::initDefaults() {
    beginGroup("User");
    for (auto const &it : _items) {
        if (it->key().isEmpty()) continue;
        if (value(it->key()).isNull()) {
            setValue(it->key(), it->defaultValue());
        }
    }
    endGroup();
}

QString Settings::style() {
    return value("User/theme", "").toString();
}


