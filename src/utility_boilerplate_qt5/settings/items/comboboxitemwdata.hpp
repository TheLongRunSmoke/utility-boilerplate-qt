#ifndef UTILITY_BOILERPLATE_QT_COMBOBOXITEMWDATA_HPP
#define UTILITY_BOILERPLATE_QT_COMBOBOXITEMWDATA_HPP

#include <QComboBox>

#include "abstract/simplesettingitem.hpp"

/**
 * User setting combobox control with data support.
 */
class ComboBoxItemWithData : public SimpleSettingItem<QComboBox> {
  public:
    ComboBoxItemWithData(QString key, QString name, std::map<QString, QVariant> elements,
                         const QString& defaultValue = nullptr, QString toolTip = nullptr);

    QWidget* view(QWidget* parent) override;

    QString value() override;

    void setValue(QString value) override;

    QString defaultValue() override;

  protected:
    std::map<QString, QVariant> _elements{};
    QString _value = nullptr;
    QString _defaultValue = nullptr;
};

#endif  // UTILITY_BOILERPLATE_QT_COMBOBOXITEMWDATA_HPP
