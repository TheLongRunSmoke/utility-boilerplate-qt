#ifndef UTILITY_BOILERPLATE_QT_TEXTEDITORSETTINGS_HPP
#define UTILITY_BOILERPLATE_QT_TEXTEDITORSETTINGS_HPP

#include <settings/settings.hpp>

/**
 * Application settings.
 *
 * Things like window state, recent files, etc. already included in Settings
 * class.
 *
 * Add parameters that you need using addUserSetting(<some settings item>) in
 * createUserSettings(), than it's can be accessed by Qt value(key).
 *
 * Note, start add userSectionTag() to begin of key.
 */
class TextEditorSettings : public Settings {
    Q_DECLARE_TR_FUNCTIONS(TextEditorSettings)

  public:
    TextEditorSettings();

  protected:
    void createUserSettings() override;
};

#endif  // UTILITY_BOILERPLATE_QT_TEXTEDITORSETTINGS_HPP
