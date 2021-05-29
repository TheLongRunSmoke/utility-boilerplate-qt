#include "spinboxitem.hpp"
#include <QLabel>
#include <debug_new>
#include <utility>

SpinboxItem::SpinboxItem(
        QString key,
        QString name,
        int min,
        int max,
        int defaultValue)
        : UserSettingItem(std::move(key)),
          _name{std::move(name)},
          _min{min},
          _max{max} {
    if (defaultValue < _min || defaultValue > _max) {
        _defaultValue = intToValue(0);
    } else {
        _defaultValue = intToValue(defaultValue);
    }
}

SpinboxItem::~SpinboxItem() {
    delete _spinBox;
    delete _view;
}

QWidget* SpinboxItem::view(QWidget* parent) {
    if (_view) return _view;
    _view = new QWidget(parent);
    auto* layout = new QHBoxLayout;
    _spinBox = new QSpinBox(_view);
    _spinBox->setRange(_min, _max);
    if (_defaultValue != nullptr) {
        _spinBox->setValue(valueToInt(defaultValue()));
    }
    if (_value != nullptr) {
        _spinBox->setValue(valueToInt(_value));
    }
    auto* label = new QLabel(_view);
    label->setTextFormat(Qt::TextFormat::PlainText);
    label->setText(_name);
    label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    label->setBuddy(_spinBox);
    layout->addWidget(label);
    layout->addWidget(_spinBox);
    layout->addStretch();
    _view->setLayout(layout);
    return _view;
}

QString SpinboxItem::value() {
    if (!_spinBox) return _defaultValue;
    return intToValue(_spinBox->value());
}

void SpinboxItem::setValue(QString value) {
    _value = value;
    if (_value == nullptr) _value = intToValue(0);
    if (valueToInt(_value) < _min || valueToInt(_value) > _max) _value = intToValue(0);
    if (!_spinBox) return;
    _spinBox->setValue(valueToInt(_value));
}

QString SpinboxItem::defaultValue() {
    if (_defaultValue == nullptr) return intToValue(0);
    if (_defaultValue.isEmpty()) return intToValue(0);
    return _defaultValue;
}

QString SpinboxItem::intToValue(int integer) {
    return QString::number(integer, 10);
}

int SpinboxItem::valueToInt(const QString& value) {
    if (value == nullptr) return 0;
    bool isOk;
    int result = value.toInt(&isOk, 10);
    if (!isOk) return 0;
    return result;
}
