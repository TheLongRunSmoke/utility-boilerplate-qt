#ifndef UTILITY_BOILERPLATE_QT_CHECKBOXITEM_HPP
#define UTILITY_BOILERPLATE_QT_CHECKBOXITEM_HPP

#include <QCheckBox>
#include "abstract/simplesettingitem.hpp"

class CheckBoxItem : public SimpleSettingItem<QCheckBox> {
  public:
    CheckBoxItem(QString key, QString name, bool defaultValue = false, QString toolTip = nullptr);

    QWidget* view(QWidget* parent) override;

    QString value() override;

    void setValue(QString value) override;

    QString defaultValue() override;

  protected:
    QString _value = nullptr;
    bool _defaultValue = false;

  private:
    static Qt::CheckState boolToState(bool isChecked);

    static QString stateToValue(Qt::CheckState state);

    static Qt::CheckState valueToState(const QString& value);
};

#endif  // UTILITY_BOILERPLATE_QT_CHECKBOXITEM_HPP
