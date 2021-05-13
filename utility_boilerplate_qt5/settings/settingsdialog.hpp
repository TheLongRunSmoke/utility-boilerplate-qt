#ifndef UTILITY_BOILERPLATE_QT_SETTINGSDIALOG_HPP
#define UTILITY_BOILERPLATE_QT_SETTINGSDIALOG_HPP

#include <QDialog>
#include "settings.hpp"
#include "settingsdialog.hpp"

class SettingsDialog : public QDialog {
Q_OBJECT

public:
    explicit SettingsDialog(QWidget* parent = Q_NULLPTR);
    ~SettingsDialog();

private:
    Settings* _settings;
};


#endif //UTILITY_BOILERPLATE_QT_SETTINGSDIALOG_HPP
