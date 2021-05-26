#ifndef UTILITY_BOILERPLATE_QT_SEPARATORITEM_HPP
#define UTILITY_BOILERPLATE_QT_SEPARATORITEM_HPP

#include <QWidget>
#include "usersettingitem.hpp"

class SeparatorItem : public UserSettingItem {

public:
    SeparatorItem() : UserSettingItem(nullptr){};

    ~SeparatorItem() override;

    QWidget *view(QWidget *parent) override;

    QString value() override { return ""; };

    void setValue(QString value) override {};

    QString defaultValue() override { return ""; };

private:
    QWidget *_view = nullptr;

};


#endif //UTILITY_BOILERPLATE_QT_SEPARATORITEM_HPP
