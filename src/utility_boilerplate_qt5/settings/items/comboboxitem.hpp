#ifndef UTILITY_BOILERPLATE_QT_COMBOBOXITEM_HPP
#define UTILITY_BOILERPLATE_QT_COMBOBOXITEM_HPP

#include <QComboBox>

#include "abstract/simplesettingitem.hpp"

/**
 * User setting with basic combobox control.
 */
class ComboBoxItem : public SimpleSettingItem<QComboBox> {
  public:
    ComboBoxItem(QString key, QString name, QStringList elements,
                 const QString& defaultValue = nullptr, QString toolTip = nullptr);

    QWidget* view(QWidget* parent) override;

    QString value() override;

    void setValue(QString value) override;

    QString defaultValue() override;

  protected:
    QStringList _elements = QStringList();
    QString _value = nullptr;
    QString _defaultValue = nullptr;
};

#endif  // UTILITY_BOILERPLATE_QT_COMBOBOXITEM_HPP
