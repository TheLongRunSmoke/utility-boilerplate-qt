#ifndef UTILITY_BOILERPLATE_QT_TEXTEDITORSETTINGS_HPP
#define UTILITY_BOILERPLATE_QT_TEXTEDITORSETTINGS_HPP

#include "utility_boilerplate_qt5/settings/settings.hpp"

/**
 * Application settings.
 *
 * Things like window state, recent files, etc. already included in Settings class.
 *
 * Add parameters that you need using addUserSetting(<some settings item>) in constructor,
 * than it's can be accessed by Qt value(key).
 * Note, when you set item key, add "User/" to retrieved value.
 *
 */
class TextEditorSettings : public Settings {
Q_OBJECT

public:
    TextEditorSettings();

private:
    /**
     * Add some examples settings.
     */
    void addTextEditorSettings();
};


#endif //UTILITY_BOILERPLATE_QT_TEXTEDITORSETTINGS_HPP
