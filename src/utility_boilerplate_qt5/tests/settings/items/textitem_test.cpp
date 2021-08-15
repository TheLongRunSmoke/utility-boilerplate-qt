#include <gtest/gtest.h>
#include "../../fixtures.hpp"

#include <settings/items/textitem.hpp>

namespace ubTestSuit {

    TEST_F(UiFixture, SettingItems_TextItem) {  // NOLINT(cert-err58-cpp)
        auto* item = new TextItem("key", "name");

        EXPECT_EQ(item->key(), "key");

        auto* label = findQWidgetByClass<QLabel>(item->view(window));
        EXPECT_EQ(label->text(), "name");

        delete item;
    }

    TEST_F(UiFixture, SettingItems_TextItem_defaultValue) {  // NOLINT(cert-err58-cpp)
        auto* item = new TextItem("key", "name");

        EXPECT_EQ(item->defaultValue(), "");

        auto* field = findQWidgetByClass<QLineEdit>(item->view(window));
        EXPECT_EQ(field->text(), "");

        delete item;

        item = new TextItem("key", "name", "default");

        EXPECT_EQ(item->defaultValue(), "default");

        field = findQWidgetByClass<QLineEdit>(item->view(window));
        EXPECT_EQ(field->text(), "default");

        item = new TextItem("key", "name", nullptr);

        EXPECT_EQ(item->defaultValue(), "");

        field = findQWidgetByClass<QLineEdit>(item->view(window));
        EXPECT_EQ(field->text(), "");

        delete item;
    }

    TEST_F(UiFixture, SettingItems_TextItem_value) {  // NOLINT(cert-err58-cpp)
        auto* item = new TextItem("key", "name");

        EXPECT_EQ(item->value(), "");

        auto* field = findQWidgetByClass<QLineEdit>(item->view(window));
        EXPECT_EQ(field->text(), "");

        item->setValue("test_text");

        EXPECT_EQ(item->value(), "test_text");

        field = findQWidgetByClass<QLineEdit>(item->view(window));
        EXPECT_EQ(field->text(), "test_text");

        delete item;
    }

}  // namespace ubTestSuit
