#ifndef UTILITY_BOILERPLATE_QT_COMBOBOXITEM_HPP
#define UTILITY_BOILERPLATE_QT_COMBOBOXITEM_HPP

#include "usersettingitem.hpp"
#include <QComboBox>

/**
 * Basic combo box control.
 */
class ComboBoxItem : public UserSettingItem {

public:
    ComboBoxItem(QString key,
                 QString name,
                 QStringList elements);

    ~ComboBoxItem() override;

    QWidget *view(QWidget *parent) override;

    QString value() override;

private:
    QWidget *_view = nullptr;
    QComboBox *_comboBox = nullptr;
    QString _name = nullptr;
    QStringList _elements = QStringList();

    QString defaultValue() override;
};

#endif //UTILITY_BOILERPLATE_QT_COMBOBOXITEM_HPP
