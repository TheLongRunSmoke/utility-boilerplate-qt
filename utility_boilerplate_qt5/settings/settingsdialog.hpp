#ifndef UTILITY_BOILERPLATE_QT_SETTINGSDIALOG_HPP
#define UTILITY_BOILERPLATE_QT_SETTINGSDIALOG_HPP

#include <QDialog>
#include "settings.hpp"
#include "settingsdialog.hpp"

class SettingsDialog : public QDialog {
Q_OBJECT

public:
    explicit SettingsDialog(Settings* settings, QWidget* parent = Q_NULLPTR);

    ~SettingsDialog() override;

    void accept() override;

public slots:

    void apply();

protected:
    bool event(QEvent* event) override;

    virtual void retranslateUi();

private:

    Settings* _settings;

    QWidget* _settingsWidget = new QWidget();

    QWidget* createUserSettingsWidget();
};


#endif //UTILITY_BOILERPLATE_QT_SETTINGSDIALOG_HPP
