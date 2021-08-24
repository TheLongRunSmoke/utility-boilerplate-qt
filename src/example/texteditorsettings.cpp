
#include "texteditorsettings.hpp"

#include "settings/items/checkboxitem.hpp"
#include "settings/items/separatoritem.hpp"
#include "settings/items/spinboxitem.hpp"
#include "settings/items/textitem.hpp"

TextEditorSettings::TextEditorSettings() {
    TextEditorSettings::createUserSettings();
    initDefaults();
    readUserSettings();
}

void TextEditorSettings::createUserSettings() {
    // Here some examples of how to use inbuilt controls.
    // To fetch them use value(key(userSectionTag(), <key>)).
    addUserSetting(new SeparatorItem());
    auto* checkBoxFalse = new CheckBoxItem("checkbox_default_false", tr("Default false"));
    addUserSetting(checkBoxFalse);
    auto* checkBoxTrue = new CheckBoxItem("checkbox_default_true", tr("Default true"), true);
    addUserSetting(checkBoxTrue);
    addUserSetting(new SeparatorItem());
    auto* textItem = new TextItem("text_no_default", tr("Default empty"));
    addUserSetting(textItem);
    auto* textItemDef = new TextItem("text_has_default", tr("Has default text"), "some text");
    addUserSetting(textItemDef);
    addUserSetting(new SeparatorItem());
    auto* intSpinBoxDefault = new SpinboxItem("spinbox_def", tr("Spinbox defaults"));
    addUserSetting(intSpinBoxDefault);
    auto* intSpinBox = new SpinboxItem("spinbox", tr("Spinbox"), -5, 5, -1);
    addUserSetting(intSpinBox);
}
