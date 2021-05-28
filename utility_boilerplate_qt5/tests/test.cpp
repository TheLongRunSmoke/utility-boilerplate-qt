#include <gtest/gtest.h>

#include <QStringList>
#include <settings/items/comboboxitem.hpp>

namespace ub_test_suit {

    TEST(SettingItems, ComboBox_defaultValue) { // NOLINT(cert-err58-cpp)
        auto* item = new ComboBoxItem(
                "key",
                "name",
                QStringList::fromStdList(std::list<QString>{"first", "default", "second"}),
                "default");

        EXPECT_EQ(item->defaultValue(), "default");
        EXPECT_EQ(item->value(), "default");

        delete item;
    }

    TEST(SettingItems, ComboBox_value) { // NOLINT(cert-err58-cpp)
        auto* item = new ComboBoxItem(
                "key",
                "name",
                QStringList::fromStdList(std::list<QString>{"first", "default", "second"}),
                "default");

        EXPECT_EQ(item->value(), "default");
        item->setValue("first");
        EXPECT_EQ(item->value(), "first");

        delete item;
    }

}