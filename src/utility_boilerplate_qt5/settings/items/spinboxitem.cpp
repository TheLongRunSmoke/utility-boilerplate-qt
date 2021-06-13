#include "spinboxitem.hpp"

#include <debug_new>

SpinboxItem::SpinboxItem(QString key, QString name, int min, int max, int defaultValue,
                         QString toolTip)
    : SimpleSettingItem(std::move(key), std::move(name), std::move(toolTip)), _min{min}, _max{max} {
    _defaultValue = intToValue(validateValue(defaultValue, _min, _max));
}

QWidget* SpinboxItem::view(QWidget* parent) {
    if (_view) return _view;
    _view = new QWidget(parent);
    auto* layout = new QHBoxLayout;
    _field = new QSpinBox(_view);
    _field->setRange(_min, _max);
    if (_defaultValue != nullptr) {
        _field->setValue(valueToInt(defaultValue()));
    }
    if (_value != nullptr) {
        _field->setValue(valueToInt(_value));
    }
    layout->addWidget(createLabel());
    layout->addWidget(_field);
    layout->addStretch();
    _view->setLayout(layout);
    return _view;
}

QString SpinboxItem::value() {
    if (!_field) return (_value != nullptr) ? _value : _defaultValue;
    return intToValue(_field->value());
}

void SpinboxItem::setValue(QString value) {
    if (value == nullptr) _value = intToValue(0);
    int intValue = validateValue(valueToInt(value), _min, _max);
    _value = intToValue(intValue);
    if (!_field) return;
    _field->setValue(valueToInt(_value));
}

QString SpinboxItem::defaultValue() {
    if (_defaultValue == nullptr) return intToValue(0);
    if (_defaultValue.isEmpty()) return intToValue(0);
    return _defaultValue;
}

QString SpinboxItem::intToValue(int integer) { return QString::number(integer, 10); }

int SpinboxItem::valueToInt(const QString& value) {
    if (value == nullptr) return 0;
    bool isOk;
    int result = value.toInt(&isOk, 10);
    if (!isOk) return 0;
    return result;
}

int SpinboxItem::validateValue(int value, int min, int max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}
