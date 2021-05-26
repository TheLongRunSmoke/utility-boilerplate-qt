#ifndef UTILITY_BOILERPLATE_QT_TEXTITEM_HPP
#define UTILITY_BOILERPLATE_QT_TEXTITEM_HPP

#include "usersettingitem.hpp"
#include <QLineEdit>

class TextItem : public UserSettingItem {
public:
    TextItem(QString key,
             QString name,
             QString defaultValue = "");

    ~TextItem() override;

    QWidget* view(QWidget* parent) override;

    QString value() override;

    void setValue(QString value) override;

    QString defaultValue() override;

private:
    QWidget* _view = nullptr;
    QLineEdit* _lineEdit = nullptr;
    QString _name = nullptr;
    QString _value = "";
    QString _defaultValue = nullptr;
};


#endif //UTILITY_BOILERPLATE_QT_TEXTITEM_HPP
