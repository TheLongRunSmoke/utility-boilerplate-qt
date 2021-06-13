#include "textitem.hpp"

#include <debug_new>

TextItem::TextItem(QString key, QString name, QString defaultValue, QString toolTip)
    : SimpleSettingItem<QLineEdit>(std::move(key), std::move(name), std::move(toolTip)),
      _defaultValue{std::move(defaultValue)} {}

QWidget* TextItem::view(QWidget* parent) {
    if (_view) return _view;
    _view = new QWidget(parent);
    auto* layout = new QHBoxLayout;
    _field = new QLineEdit(_view);
    if (_defaultValue != nullptr) {
        _field->setText(defaultValue());
    }
    if (_value != nullptr) {
        _field->setText(_value);
    }
    layout->addWidget(createLabel());
    layout->addWidget(_field);
    layout->addStretch();
    _view->setLayout(layout);
    return _view;
}

QString TextItem::value() {
    if (!_field) return (_value != nullptr) ? _value : _defaultValue;
    return _field->text();
}

void TextItem::setValue(QString value) {
    _value = value;
    if (_value == nullptr) _value = "";
    if (!_field) return;
    _field->setText(_value);
}

QString TextItem::defaultValue() {
    if (_defaultValue == nullptr) return "";
    return _defaultValue;
}
