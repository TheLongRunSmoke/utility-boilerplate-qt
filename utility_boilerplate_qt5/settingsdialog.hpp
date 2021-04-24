#ifndef UTILITY_BOILERPLATE_QT_SETTINGSDIALOG_HPP
#define UTILITY_BOILERPLATE_QT_SETTINGSDIALOG_HPP

#include <QDialog>
#include "settingsdialog.hpp"
#include "settingswidget.hpp"

class SettingsDialog : public QDialog {
Q_OBJECT

public:
    explicit SettingsDialog(QWidget* parent = Q_NULLPTR);

private:
    SettingsWidget settingsWidget;
};


#endif //UTILITY_BOILERPLATE_QT_SETTINGSDIALOG_HPP
