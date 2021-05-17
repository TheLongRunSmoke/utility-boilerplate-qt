#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QApplication>
#include <QSet>
#include <memory>
#include "items/settingitem.hpp"

class Settings : public QSettings
{
public:
	Settings();
	~Settings() override;
	QByteArray geometry();
	void setGeometry(const QByteArray& geometry);
	bool hasRecentFiles();
	QStringList recentFiles();
	void putRecentFile(const QString& path);
	std::list<std::unique_ptr<SettingItem>>* items();

protected:
    std::list<std::unique_ptr<SettingItem>> _items = std::list<std::unique_ptr<SettingItem>>();

private:
	static QString path();
	inline static QString geometryKey();
	inline static QString recentFilesKey();
	static inline QString fileKey();
};

#endif //SETTINGS_H