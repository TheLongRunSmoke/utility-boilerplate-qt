#ifndef UTILITY_BOILERPLATE_QT_SETTINGSDIALOG_HPP
#define UTILITY_BOILERPLATE_QT_SETTINGSDIALOG_HPP

#include <QDialog>

#include "settings.hpp"
#include "settingsdialog.hpp"

/**
 * Settings dialog.
 *
 * Load and show settings from argument.
 *
 * Use:
 *  SettingsDialog(new Settings()).exec();
 */
class SettingsDialog : public QDialog {
    Q_OBJECT

  public:
    explicit SettingsDialog(Settings* settings, QWidget* parent = Q_NULLPTR);

    ~SettingsDialog() override;

    /**
     * Apply all settings in window.
     */
    void accept() override;

  public slots:

    /**
     * Apply all settings and close dialog,
     */
    void apply();

  protected:
    /**
     * Handle events.
     *
     * Process QEvent::LanguageChange here.
     *
     * See Qt documentation for details.
     *
     * @return true if event fully handled and must not appear anywhere else.
     * @return false event can be passed next by hierarchy.
     */
    bool event(QEvent* event) override;

    /**
     * Call UI retranslation.
     */
    virtual void retranslateUi();

  private:
    /**
     * Settings object form arguments.
     */
    Settings* _settings;

    /**
     * Widget that contain all settings controls.
     */
    QWidget* _settingsWidget = new QWidget();

    /**
     * Collect settings controls from _settings and create widget with it.
     */
    QWidget* createUserSettingsWidget();
};

#endif  // UTILITY_BOILERPLATE_QT_SETTINGSDIALOG_HPP
