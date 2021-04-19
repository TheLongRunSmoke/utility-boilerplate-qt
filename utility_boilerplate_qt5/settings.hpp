#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QApplication>

class Settings : public QSettings
{
public:
	Settings();
	QByteArray geometry();
	void setGeometry(const QByteArray& geometry);
	bool hasRecentFiles();
	QStringList recentFiles();
	void putRecentFile(const QString& path);
private:
	static QString path();
	inline static QString geometryKey();
	inline static QString recentFilesKey();
	static inline QString fileKey();
};

#endif //SETTINGS_H