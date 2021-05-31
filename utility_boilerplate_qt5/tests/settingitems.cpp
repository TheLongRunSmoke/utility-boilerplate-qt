#include <gtest/gtest.h>

#include "test.hpp"
#include <settings/items/checkboxitem.hpp>
#include <settings/items/comboboxitem.hpp>
#include <settings/items/separatoritem.hpp>
#include <settings/items/spinboxitem.hpp>
#include <settings/items/textitem.hpp>

namespace ubTestSuit {

    template<typename T>
    T* findQWidgetByClass(QWidget* widget) {
        return widget->findChildren<T*>().first();
    }

    // CheckBoxItem /////////////

    TEST_F(UiFixture, SettingItems_CheckBoxItem) { // NOLINT(cert-err58-cpp)
        auto* item = new CheckBoxItem(
                "key",
                "name");

        EXPECT_EQ(item->key(), "key");

        auto* label = findQWidgetByClass<QLabel>(item->view(window));
        EXPECT_EQ(label->text(), "name");

        delete item;
    }

    TEST_F(UiFixture, SettingItems_CheckBoxItem_defaultValue) { // NOLINT(cert-err58-cpp)
        auto* item = new CheckBoxItem(
                "key",
                "name");

        EXPECT_EQ(item->defaultValue(), "false");
        auto* field = findQWidgetByClass<QCheckBox>(item->view(window));
        EXPECT_EQ(field->checkState(), Qt::Unchecked);

        delete item;

        item = new CheckBoxItem(
                "key",
                "name",
                false);

        EXPECT_EQ(item->defaultValue(), "false");
        field = findQWidgetByClass<QCheckBox>(item->view(window));
        EXPECT_EQ(field->checkState(), Qt::Unchecked);

        delete item;

        item = new CheckBoxItem(
                "key",
                "name",
                true);

        EXPECT_EQ(item->defaultValue(), "true");
        field = findQWidgetByClass<QCheckBox>(item->view(window));
        EXPECT_EQ(field->checkState(), Qt::Checked);

        delete item;
    }

    TEST_F(UiFixture, SettingItems_CheckBoxItem_value) { // NOLINT(cert-err58-cpp)
        auto* item = new CheckBoxItem(
                "key",
                "name");

        EXPECT_EQ(item->value(), "false");
        auto* field = findQWidgetByClass<QCheckBox>(item->view(window));
        EXPECT_EQ(field->checkState(), Qt::Unchecked);

        delete item;

        item = new CheckBoxItem(
                "key",
                "name",
                false);

        EXPECT_EQ(item->value(), "false");
        field = findQWidgetByClass<QCheckBox>(item->view(window));
        EXPECT_EQ(field->checkState(), Qt::Unchecked);

        delete item;

        item = new CheckBoxItem(
                "key",
                "name",
                true);

        EXPECT_EQ(item->value(), "true");
        field = findQWidgetByClass<QCheckBox>(item->view(window));
        EXPECT_EQ(field->checkState(), Qt::Checked);

        item->setValue("false");
        EXPECT_EQ(item->value(), "false");
        field = findQWidgetByClass<QCheckBox>(item->view(window));
        EXPECT_EQ(field->checkState(), Qt::Unchecked);

        delete item;
    }

    // ComboBoxItem /////////////

    TEST_F(UiFixture, SettingItems_ComboBoxItem) { // NOLINT(cert-err58-cpp)
        auto* item = new ComboBoxItem(
                "key",
                "name",
                QStringList::fromStdList(std::list<QString>{}));

        EXPECT_EQ(item->key(), "key");

        auto* label = findQWidgetByClass<QLabel>(item->view(window));
        EXPECT_EQ(label->text(), "name");

        delete item;
    }

    TEST_F(UiFixture, SettingItems_ComboBoxItem_defaultValue) { // NOLINT(cert-err58-cpp)
        auto* item = new ComboBoxItem(
                "key",
                "name",
                QStringList::fromStdList(std::list<QString>{"first", "default", "second"}),
                "default");

        EXPECT_EQ(item->defaultValue(), "default");

        auto* field = findQWidgetByClass<QComboBox>(item->view(window));
        EXPECT_EQ(field->currentIndex(), 1);

        delete item;

        item = new ComboBoxItem(
                "key",
                "name",
                QStringList::fromStdList(std::list<QString>{"first", "default", "second"}));

        EXPECT_EQ(item->defaultValue(), "first");

        field = findQWidgetByClass<QComboBox>(item->view(window));
        EXPECT_EQ(field->currentIndex(), 0);

        delete item;

        item = new ComboBoxItem(
                "key",
                "name",
                QStringList::fromStdList(std::list<QString>{}));
        EXPECT_EQ(item->defaultValue(), "");
        delete item;
    }

    TEST_F(UiFixture, SettingItems_ComboBoxItem_value) { // NOLINT(cert-err58-cpp)
        auto* item = new ComboBoxItem(
                "key",
                "name",
                QStringList::fromStdList(std::list<QString>{"first", "default", "second"}),
                "default");

        EXPECT_EQ(item->value(), "default");
        auto* field = findQWidgetByClass<QComboBox>(item->view(window));
        EXPECT_EQ(field->currentIndex(), 1);

        item->setValue("second");
        EXPECT_EQ(item->value(), "second");
        EXPECT_EQ(field->currentIndex(), 2);

        delete item;

        item = new ComboBoxItem(
                "key",
                "name",
                QStringList::fromStdList(std::list<QString>{}));
        EXPECT_EQ(item->value(), "");
        delete item;
    }

    // SeparatorItem /////////////

    TEST_F(UiFixture, SettingItems_SeparatorItem) { // NOLINT(cert-err58-cpp)
        auto* item = new SeparatorItem();

        EXPECT_EQ(item->key(), nullptr);

        QWidget* widget = item->view(window);
        EXPECT_NE(widget, nullptr);

        delete item;
    }

    // SpinBoxItem /////////////

    TEST_F(UiFixture, SettingItems_SpinboxItem) { // NOLINT(cert-err58-cpp)
        auto* item = new SpinboxItem(
                "key",
                "name");

        EXPECT_EQ(item->key(), "key");

        auto* label = findQWidgetByClass<QLabel>(item->view(window));
        EXPECT_EQ(label->text(), "name");

        delete item;
    }

    TEST_F(UiFixture, SettingItems_SpinboxItem_defaultValue) { // NOLINT(cert-err58-cpp)
        auto* item = new SpinboxItem(
                "key",
                "name");

        EXPECT_EQ(item->defaultValue(), "0");

        auto* field = findQWidgetByClass<QSpinBox>(item->view(window));
        EXPECT_EQ(field->value(), 0);

        delete item;

        item = new SpinboxItem(
                "key",
                "name",
                -5,
                5);

        EXPECT_EQ(item->defaultValue(), "0");

        field = findQWidgetByClass<QSpinBox>(item->view(window));
        EXPECT_EQ(field->value(), 0);

        delete item;

        item = new SpinboxItem(
                "key",
                "name",
                -5,
                5,
                2);

        EXPECT_EQ(item->defaultValue(), "2");

        field = findQWidgetByClass<QSpinBox>(item->view(window));
        EXPECT_EQ(field->value(), 2);

        delete item;

        item = new SpinboxItem(
                "key",
                "name",
                -5,
                5,
                -5);

        EXPECT_EQ(item->defaultValue(), "-5");

        field = findQWidgetByClass<QSpinBox>(item->view(window));
        EXPECT_EQ(field->value(), -5);

        delete item;

        item = new SpinboxItem(
                "key",
                "name",
                -5,
                5,
                -10);

        EXPECT_EQ(item->defaultValue(), "-5");

        field = findQWidgetByClass<QSpinBox>(item->view(window));
        EXPECT_EQ(field->value(), -5);

        delete item;

        item = new SpinboxItem(
                "key",
                "name",
                -5,
                5,
                5);

        EXPECT_EQ(item->defaultValue(), "5");

        field = findQWidgetByClass<QSpinBox>(item->view(window));
        EXPECT_EQ(field->value(), 5);

        delete item;

        item = new SpinboxItem(
                "key",
                "name",
                -5,
                5,
                10);

        EXPECT_EQ(item->defaultValue(), "5");

        field = findQWidgetByClass<QSpinBox>(item->view(window));
        EXPECT_EQ(field->value(), 5);

        delete item;
    }

    TEST_F(UiFixture, SettingItems_SpinboxItem_value) { // NOLINT(cert-err58-cpp)
        auto* item = new SpinboxItem(
                "key",
                "name",
                -10,
                20,
                8);

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

    // TextItem /////////////

    TEST_F(UiFixture, SettingItems_TextItem) { // NOLINT(cert-err58-cpp)
        auto* item = new TextItem(
                "key",
                "name");

        EXPECT_EQ(item->key(), "key");

        auto* label = findQWidgetByClass<QLabel>(item->view(window));
        EXPECT_EQ(label->text(), "name");

        delete item;
    }

    TEST_F(UiFixture, SettingItems_TextItem_defaultValue) { // NOLINT(cert-err58-cpp)
        auto* item = new TextItem(
                "key",
                "name");

        EXPECT_EQ(item->defaultValue(), "");

        auto* field = findQWidgetByClass<QLineEdit>(item->view(window));
        EXPECT_EQ(field->text(), "");

        delete item;

        item = new TextItem(
                "key",
                "name",
                "default");

        EXPECT_EQ(item->defaultValue(), "default");

        field = findQWidgetByClass<QLineEdit>(item->view(window));
        EXPECT_EQ(field->text(), "default");

        item = new TextItem(
                "key",
                "name",
                nullptr);

        EXPECT_EQ(item->defaultValue(), "");

        field = findQWidgetByClass<QLineEdit>(item->view(window));
        EXPECT_EQ(field->text(), "");

        delete item;
    }

    TEST_F(UiFixture, SettingItems_TextItem_value) { // NOLINT(cert-err58-cpp)
        auto* item = new TextItem(
                "key",
                "name");

        EXPECT_EQ(item->value(), "");

        auto* field = findQWidgetByClass<QLineEdit>(item->view(window));
        EXPECT_EQ(field->text(), "");

        item->setValue("test_text");

        EXPECT_EQ(item->value(), "test_text");

        field = findQWidgetByClass<QLineEdit>(item->view(window));
        EXPECT_EQ(field->text(), "test_text");

        delete item;
    }
}
