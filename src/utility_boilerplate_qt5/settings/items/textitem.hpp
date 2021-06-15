#ifndef UTILITY_BOILERPLATE_QT_TEXTITEM_HPP
#define UTILITY_BOILERPLATE_QT_TEXTITEM_HPP

#include <QLineEdit>

#include "abstract/simplesettingitem.hpp"

class TextItem : public SimpleSettingItem<QLineEdit> {
  public:
    TextItem(QString key, QString name, QString defaultValue = "", QString toolTip = nullptr);

    QWidget* view(QWidget* parent) override;

    QString value() override;

    void setValue(QString value) override;

    QString defaultValue() override;

  private:
    QString _value = "";
    QString _defaultValue = nullptr;
};

#endif  // UTILITY_BOILERPLATE_QT_TEXTITEM_HPP
