#ifndef UTILITY_BOILERPLATE_QT_SETTINGSDIALOG_HPP
#define UTILITY_BOILERPLATE_QT_SETTINGSDIALOG_HPP

#include <QDialog>
#include "settings.hpp"
#include "settingsdialog.hpp"

class SettingsDialog : public QDialog {
Q_OBJECT

public:
    SettingsDialog(Settings* settings, QWidget* parent = Q_NULLPTR);

    ~SettingsDialog();

    void accept() override;

public slots:

    void apply();

private:
    Settings* _settings;
};


#endif //UTILITY_BOILERPLATE_QT_SETTINGSDIALOG_HPP
