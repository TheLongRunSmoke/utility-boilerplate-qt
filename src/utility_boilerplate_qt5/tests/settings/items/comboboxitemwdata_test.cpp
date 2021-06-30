#include "settings/items/comboboxitemwdata.hpp"

#include <gtest/gtest.h>

#include "../../fixtures.hpp"

namespace ubTestSuit {

    TEST_F(UiFixture, SettingItem_ComboBoxItemWithData) {  // NOLINT(cert-err58-cpp)
        std::map<QString, QVariant> map;
        auto* item = new ComboBoxItemWithData("key", "name", map);

        EXPECT_EQ(item->key(), "key");

        auto* label = findQWidgetByClass<QLabel>(item->view(window));
        EXPECT_EQ(label->text(), "name");

        delete item;
    }

    TEST_F(UiFixture,  // NOLINT(cert-err58-cpp)
           SettingItem_ComboBoxItemWithData_defaultValue) {
        std::map<QString, QVariant> map = {
            {"key1", QVariant("data1")}, {"key2", QVariant("data2")}, {"key3", QVariant("data3")}};

        auto* item = new ComboBoxItemWithData("key", "name", map, "key2");

        EXPECT_EQ(item->defaultValue(), "key2");

        auto* field = findQWidgetByClass<QComboBox>(item->view(window));
        EXPECT_EQ(field->currentIndex(), 1);

        delete item;

        item = new ComboBoxItemWithData("key", "name", map);

        EXPECT_EQ(item->defaultValue(), "key1");

        field = findQWidgetByClass<QComboBox>(item->view(window));
        EXPECT_EQ(field->currentIndex(), 0);

        delete item;

        map = {};

        item = new ComboBoxItemWithData("key", "name", map);
        EXPECT_EQ(item->defaultValue(), "");
        delete item;
    }

    TEST_F(UiFixture,  // NOLINT(cert-err58-cpp)
           SettingItem_ComboBoxItemWithData_value) {
        std::map<QString, QVariant> map = {
            {"key1", QVariant("data1")}, {"key2", QVariant("data2")}, {"key3", QVariant("data3")}};

        auto* item = new ComboBoxItemWithData("key", "name", map, "key2");

        EXPECT_EQ(item->value(), "key2");
        auto* field = findQWidgetByClass<QComboBox>(item->view(window));
        EXPECT_EQ(field->currentIndex(), 1);

        item->setValue("key3");
        EXPECT_EQ(item->value(), "key3");
        EXPECT_EQ(field->currentIndex(), 2);

        delete item;

        map = {};

        item = new ComboBoxItemWithData("key", "name", map);
        EXPECT_EQ(item->value(), "");
        delete item;
    }

}  // namespace ubTestSuit