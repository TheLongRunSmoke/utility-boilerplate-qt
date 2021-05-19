#include <QCoreApplication>
#include "settings.hpp"
#include "items/dropdownitem.hpp"
#include <debug_new>


Settings::Settings() : QSettings(path(), QSettings::IniFormat) {
    _items.push_front(
            std::unique_ptr<SettingItem>(new DropDownItem("theme", tr("Theme"), QStringList())));
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

std::list<std::unique_ptr<SettingItem>> *Settings::items() {
    return &_items;
}

Settings::~Settings() {
    _items.clear();
}