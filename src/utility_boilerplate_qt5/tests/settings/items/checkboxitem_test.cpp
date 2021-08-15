#include <gtest/gtest.h>
#include "../../fixtures.hpp"

#include <settings/items/checkboxitem.hpp>

namespace ubTestSuit {

    TEST_F(UiFixture, SettingItems_CheckBoxItem) {  // NOLINT(cert-err58-cpp)
        auto* item = new CheckBoxItem("key", "name");

        EXPECT_EQ(item->key(), "key");

        auto* label = findQWidgetByClass<QLabel>(item->view(window));
        EXPECT_EQ(label->text(), "name");

        delete item;
    }

    TEST_F(UiFixture, SettingItems_CheckBoxItem_defaultValue) {  // NOLINT(cert-err58-cpp)
        auto* item = new CheckBoxItem("key", "name");

        EXPECT_EQ(item->defaultValue(), "false");
        auto* field = findQWidgetByClass<QCheckBox>(item->view(window));
        EXPECT_EQ(field->checkState(), Qt::Unchecked);

        delete item;

        item = new CheckBoxItem("key", "name", false);

        EXPECT_EQ(item->defaultValue(), "false");
        field = findQWidgetByClass<QCheckBox>(item->view(window));
        EXPECT_EQ(field->checkState(), Qt::Unchecked);

        delete item;

        item = new CheckBoxItem("key", "name", true);

        EXPECT_EQ(item->defaultValue(), "true");
        field = findQWidgetByClass<QCheckBox>(item->view(window));
        EXPECT_EQ(field->checkState(), Qt::Checked);

        delete item;
    }

    TEST_F(UiFixture, SettingItems_CheckBoxItem_value) {  // NOLINT(cert-err58-cpp)
        auto* item = new CheckBoxItem("key", "name");

        EXPECT_EQ(item->value(), "false");
        auto* field = findQWidgetByClass<QCheckBox>(item->view(window));
        EXPECT_EQ(field->checkState(), Qt::Unchecked);

        delete item;

        item = new CheckBoxItem("key", "name", false);

        EXPECT_EQ(item->value(), "false");
        field = findQWidgetByClass<QCheckBox>(item->view(window));
        EXPECT_EQ(field->checkState(), Qt::Unchecked);

        delete item;

        item = new CheckBoxItem("key", "name", true);

        EXPECT_EQ(item->value(), "true");
        field = findQWidgetByClass<QCheckBox>(item->view(window));
        EXPECT_EQ(field->checkState(), Qt::Checked);

        item->setValue("false");
        EXPECT_EQ(item->value(), "false");
        field = findQWidgetByClass<QCheckBox>(item->view(window));
        EXPECT_EQ(field->checkState(), Qt::Unchecked);

        delete item;
    }
}  // namespace ubTestSuit
