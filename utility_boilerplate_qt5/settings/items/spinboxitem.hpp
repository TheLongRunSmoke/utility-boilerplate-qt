#ifndef UTILITY_BOILERPLATE_QT_SPINBOXITEM_HPP
#define UTILITY_BOILERPLATE_QT_SPINBOXITEM_HPP

#include "usersettingitem.hpp"
#include <QSpinBox>

class SpinboxItem : public UserSettingItem {
public:
    SpinboxItem(QString key,
                QString name,
                int min = 0,
                int max = 10,
                int defaultValue = 0);

    ~SpinboxItem() override;

    QWidget* view(QWidget* parent) override;

    QString value() override;

    void setValue(QString value) override;

    QString defaultValue() override;

private:
    QWidget* _view = nullptr;
    QSpinBox* _spinBox = nullptr;
    QString _name = nullptr;
    QString _value = nullptr;
    QString _defaultValue = nullptr;
    int _min = 0;
    int _max = 10;

    static QString intToValue(int integer);

    static int valueToInt(const QString& value);
};


#endif //UTILITY_BOILERPLATE_QT_SPINBOXITEM_HPP
