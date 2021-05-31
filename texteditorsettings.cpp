
#include "texteditorsettings.hpp"
#include "utility_boilerplate_qt5/settings/items/spinboxitem.hpp"
#include "utility_boilerplate_qt5/settings/items/separatoritem.hpp"
#include "utility_boilerplate_qt5/settings/items/textitem.hpp"
#include "utility_boilerplate_qt5/settings/items/checkboxitem.hpp"

TextEditorSettings::TextEditorSettings() {
    addTextEditorSettings();
}

void TextEditorSettings::addTextEditorSettings() {
    Settings::createUserSettings();
    addUserSetting(new SeparatorItem());
    auto* checkBoxFalse = new CheckBoxItem(
            "checkbox_default_false",
            tr("Default false"));
    addUserSetting(checkBoxFalse);
    auto* checkBoxTrue = new CheckBoxItem(
            "checkbox_default_true",
            tr("Default true"),
            true);
    addUserSetting(checkBoxTrue);
    addUserSetting(new SeparatorItem());
    auto* textItem = new TextItem(
            "text_no_default",
            tr("Default empty"));
    addUserSetting(textItem);
    auto* textItemDef = new TextItem(
            "text_has_default",
            tr("Has default text"),
            "some text");
    addUserSetting(textItemDef);
    addUserSetting(new SeparatorItem());
    auto* intSpinBoxDefault = new SpinboxItem(
            "spinbox_def",
            tr("Spinbox defaults"));
    addUserSetting(intSpinBoxDefault);
    auto* intSpinBox = new SpinboxItem(
            "spinbox",
            tr("Spinbox"),
            -5,
            5,
            -1);
    addUserSetting(intSpinBox);
}
