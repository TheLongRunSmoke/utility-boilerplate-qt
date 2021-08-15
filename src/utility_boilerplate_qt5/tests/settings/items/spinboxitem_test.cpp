#include <gtest/gtest.h>
#include "../../fixtures.hpp"

#include <settings/items/spinboxitem.hpp>

namespace ubTestSuit {

    TEST_F(UiFixture, SettingItems_SpinboxItem) {  // NOLINT(cert-err58-cpp)
        auto* item = new SpinboxItem("key", "name");

        EXPECT_EQ(item->key(), "key");

        auto* label = findQWidgetByClass<QLabel>(item->view(window));
        EXPECT_EQ(label->text(), "name");

        delete item;
    }

    TEST_F(UiFixture,  // NOLINT(cert-err58-cpp)
           SettingItems_SpinboxItem_defaultValue) {
        auto* item = new SpinboxItem("key", "name");

        EXPECT_EQ(item->defaultValue(), "0");

        auto* field = findQWidgetByClass<QSpinBox>(item->view(window));
        EXPECT_EQ(field->value(), 0);

        delete item;

        item = new SpinboxItem("key", "name", -5, 5);

        EXPECT_EQ(item->defaultValue(), "0");

        field = findQWidgetByClass<QSpinBox>(item->view(window));
        EXPECT_EQ(field->value(), 0);

        delete item;

        item = new SpinboxItem("key", "name", -5, 5, 2);

        EXPECT_EQ(item->defaultValue(), "2");

        field = findQWidgetByClass<QSpinBox>(item->view(window));
        EXPECT_EQ(field->value(), 2);

        delete item;

        item = new SpinboxItem("key", "name", -5, 5, -5);

        EXPECT_EQ(item->defaultValue(), "-5");

        field = findQWidgetByClass<QSpinBox>(item->view(window));
        EXPECT_EQ(field->value(), -5);

        delete item;

        item = new SpinboxItem("key", "name", -5, 5, -10);

        EXPECT_EQ(item->defaultValue(), "-5");

        field = findQWidgetByClass<QSpinBox>(item->view(window));
        EXPECT_EQ(field->value(), -5);

        delete item;

        item = new SpinboxItem("key", "name", -5, 5, 5);

        EXPECT_EQ(item->defaultValue(), "5");

        field = findQWidgetByClass<QSpinBox>(item->view(window));
        EXPECT_EQ(field->value(), 5);

        delete item;

        item = new SpinboxItem("key", "name", -5, 5, 10);

        EXPECT_EQ(item->defaultValue(), "5");

        field = findQWidgetByClass<QSpinBox>(item->view(window));
        EXPECT_EQ(field->value(), 5);

        delete item;
    }

    TEST_F(UiFixture, SettingItems_SpinboxItem_value) {  // NOLINT(cert-err58-cpp)
        auto* item = new SpinboxItem("key", "name", -10, 20, 8);

        EXPECT_EQ(item->defaultValue(), "8");
        EXPECT_EQ(item->value(), "8");

        auto* field = findQWidgetByClass<QSpinBox>(item->view(window));
        EXPECT_EQ(field->value(), 8);

        item->setValue("15");

        EXPECT_EQ(item->value(), "15");
        field = findQWidgetByClass<QSpinBox>(item->view(window));
        EXPECT_EQ(field->value(), 15);

        item->setValue("25");

        EXPECT_EQ(item->value(), "20");
        field = findQWidgetByClass<QSpinBox>(item->view(window));
        EXPECT_EQ(field->value(), 20);

        item->setValue("-20");

        EXPECT_EQ(item->value(), "-10");
        field = findQWidgetByClass<QSpinBox>(item->view(window));
        EXPECT_EQ(field->value(), -10);

        delete item;
    }

}  // namespace ubTestSuit
