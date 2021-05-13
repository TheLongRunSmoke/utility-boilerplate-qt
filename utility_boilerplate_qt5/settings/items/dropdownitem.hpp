#ifndef UTILITY_BOILERPLATE_QT_DROPDOWNITEM_HPP
#define UTILITY_BOILERPLATE_QT_DROPDOWNITEM_HPP

#include "settingitem.hpp"
#include <QComboBox>

class DropDownItem : public SettingItem {

public:
    DropDownItem(QString key,
                 QString name,
                 QStringList elements);

    ~DropDownItem() override;

    QWidget* view(QWidget* parent) override;

    QString value() override;

private:
    QWidget* _view = nullptr;
    QComboBox* _comboBox = nullptr;
    QString _name = nullptr;
    QStringList _elements = QStringList();
};

#endif //UTILITY_BOILERPLATE_QT_DROPDOWNITEM_HPP
