#ifndef UTILITY_BOILERPLATE_QT_CHECKBOXITEM_HPP
#define UTILITY_BOILERPLATE_QT_CHECKBOXITEM_HPP

#include "usersettingitem.hpp"
#include "QCheckBox"

class CheckBoxItem : public UserSettingItem {

public:
    CheckBoxItem(QString key,
                 QString name,
                 bool defaultValue = false);

    ~CheckBoxItem() override;

    QWidget* view(QWidget* parent) override;

    QString value() override;

    void setValue(QString value) override;

    QString defaultValue() override;

protected:
    QWidget* _view = nullptr;
    QCheckBox* _checkBox = nullptr;
    QString _name = nullptr;
    QString _value = nullptr;
    bool _defaultValue = false;

private:

    static Qt::CheckState boolToState(bool isChecked);

    static QString stateToValue(Qt::CheckState state);

    static Qt::CheckState valueToState(const QString& value);

};


#endif //UTILITY_BOILERPLATE_QT_CHECKBOXITEM_HPP
