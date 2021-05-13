#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QApplication>
#include <QSet>
#include "items/settingitem.hpp"

class Settings : public QSettings
{
public:
	Settings();
	~Settings();
	QByteArray geometry();
	void setGeometry(const QByteArray& geometry);
	bool hasRecentFiles();
	QStringList recentFiles();
	void putRecentFile(const QString& path);
	std::list<SettingItem*>* items();

protected:
    std::list<SettingItem*> _items = std::list<SettingItem*>();

private:
	static QString path();
	inline static QString geometryKey();
	inline static QString recentFilesKey();
	static inline QString fileKey();
};

#endif //SETTINGS_H