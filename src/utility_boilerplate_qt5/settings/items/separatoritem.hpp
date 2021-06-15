#ifndef UTILITY_BOILERPLATE_QT_SEPARATORITEM_HPP
#define UTILITY_BOILERPLATE_QT_SEPARATORITEM_HPP

#include <QWidget>

#include "abstract/settingitem.hpp"

class SeparatorItem : public SettingItem {
  public:
    SeparatorItem() : SettingItem(nullptr){};

    ~SeparatorItem() override;

    QWidget* view(QWidget* parent) override;

    QString value() override { return ""; };

    void setValue(QString value) override{};

    QString defaultValue() override { return ""; };

  private:
    QWidget* _view = nullptr;
};

#endif  // UTILITY_BOILERPLATE_QT_SEPARATORITEM_HPP
