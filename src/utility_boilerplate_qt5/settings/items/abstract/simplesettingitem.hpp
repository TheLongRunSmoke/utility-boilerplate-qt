#ifndef UTILITY_BOILERPLATE_QT_SIMPLESETTINGITEM_HPP
#define UTILITY_BOILERPLATE_QT_SIMPLESETTINGITEM_HPP

#include <QLabel>
#include <QLayout>
#include <QString>
#include <QWidget>
#include <debug_new>
#include <utility>

#include "settingitem.hpp"

/**
 * Template for simple setting item, that contain one field and label.
 */
template <typename T, typename std::enable_if<std::is_base_of<QWidget, T>::value>::type* = nullptr>
class SimpleSettingItem : public SettingItem {
  public:
    SimpleSettingItem(QString key, QString name, QString toolTip)
        : SettingItem(std::move(key)), _name{std::move(name)}, _toolTip{std::move(toolTip)} {};

    ~SimpleSettingItem() override {
        delete _field;
        delete _view;
    };

  protected:
    QWidget* _view = nullptr;
    T* _field = nullptr;
    QString _name = nullptr;
    QString _toolTip = nullptr;

    QWidget* createLabel() {
        auto* label = new QLabel(_view);
        label->setTextFormat(Qt::TextFormat::PlainText);
        label->setText(_name);
        label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        label->setBuddy(_field);
        label->setToolTip(_toolTip);
        return label;
    };
};

#endif  // UTILITY_BOILERPLATE_QT_SIMPLESETTINGITEM_HPP
