#ifndef UTILITY_BOILERPLATE_QT_COMBOBOXITEM_HPP
#define UTILITY_BOILERPLATE_QT_COMBOBOXITEM_HPP

#include "usersettingitem.hpp"
#include <QComboBox>

/**
 * User setting with basic combobox control.
 */
class ComboBoxItem : public UserSettingItem {

public:
    ComboBoxItem(QString key,
                 QString name,
                 QStringList elements,
                 const QString &defaultValue = nullptr);

    ~ComboBoxItem() override;

    QWidget *view(QWidget *parent) override;

    QString value() override;

    void setValue(QString value) override;

    QString defaultValue() override;

private:
    QWidget *_view = nullptr;
    QComboBox *_comboBox = nullptr;
    QString _name = nullptr;
    QStringList _elements = QStringList();
    QString _value = nullptr;
    QString _defaultValue = nullptr;
};

#endif //UTILITY_BOILERPLATE_QT_COMBOBOXITEM_HPP
