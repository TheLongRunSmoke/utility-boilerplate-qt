#include <gtest/gtest.h>
#include "../../fixtures.hpp"

#include <settings/items/comboboxitem.hpp>

namespace ubTestSuit {

    TEST_F(UiFixture, SettingItems_ComboBoxItem) {  // NOLINT(cert-err58-cpp)
        auto* item = new ComboBoxItem("key", "name", QList<QString>());

        EXPECT_EQ(item->key(), "key");

        auto* label = findQWidgetByClass<QLabel>(item->view(window));
        EXPECT_EQ(label->text(), "name");

        delete item;
    }

    TEST_F(UiFixture,  // NOLINT(cert-err58-cpp)
           SettingItems_ComboBoxItem_defaultValue) {
        auto* item = new ComboBoxItem(
            "key", "name", QList<QString>{"first", "default", "second"}, "default");

        EXPECT_EQ(item->defaultValue(), "default");

        auto* field = findQWidgetByClass<QComboBox>(item->view(window));
        EXPECT_EQ(field->currentIndex(), 1);

        delete item;

        item = new ComboBoxItem("key", "name", QList<QString>{"first", "default", "second"});

        EXPECT_EQ(item->defaultValue(), "first");

        field = findQWidgetByClass<QComboBox>(item->view(window));
        EXPECT_EQ(field->currentIndex(), 0);

        delete item;

        item = new ComboBoxItem("key", "name", QList<QString>());
        EXPECT_EQ(item->defaultValue(), "");
        delete item;
    }

    TEST_F(UiFixture, SettingItems_ComboBoxItem_value) {  // NOLINT(cert-err58-cpp)
        auto* item = new ComboBoxItem(
            "key", "name", QList<QString>{"first", "default", "second"}, "default");

        EXPECT_EQ(item->value(), "default");
        auto* field = findQWidgetByClass<QComboBox>(item->view(window));
        EXPECT_EQ(field->currentIndex(), 1);

        item->setValue("second");
        EXPECT_EQ(item->value(), "second");
        EXPECT_EQ(field->currentIndex(), 2);

        delete item;

        item = new ComboBoxItem("key", "name", QList<QString>());
        EXPECT_EQ(item->value(), "");
        delete item;
    }

}  // namespace ubTestSuit
