#ifndef UTILITY_BOILERPLATE_QT_SPINBOXITEM_HPP
#define UTILITY_BOILERPLATE_QT_SPINBOXITEM_HPP

#include <QSpinBox>

#include "abstract/simplesettingitem.hpp"

class SpinboxItem : public SimpleSettingItem<QSpinBox> {
  public:
    SpinboxItem(QString key, QString name, int min = 0, int max = 10, int defaultValue = 0,
                QString toolTip = nullptr);

    QWidget* view(QWidget* parent) override;

    QString value() override;

    void setValue(QString value) override;

    QString defaultValue() override;

  private:
    QString _value = nullptr;
    QString _defaultValue = nullptr;
    int _min = 0;
    int _max = 10;

    static QString intToValue(int integer);

    static int valueToInt(const QString& value);

    static int validateValue(int value, int min, int max);
};

#endif  // UTILITY_BOILERPLATE_QT_SPINBOXITEM_HPP
