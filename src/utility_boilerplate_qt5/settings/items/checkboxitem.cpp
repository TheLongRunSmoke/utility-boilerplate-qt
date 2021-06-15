#include "checkboxitem.hpp"

#include <QComboBox>
#include <debug_new>

CheckBoxItem::CheckBoxItem(QString key, QString name, bool defaultValue, QString toolTip)
    : SimpleSettingItem(std::move(key), std::move(name), std::move(toolTip)),
      _defaultValue(defaultValue) {}

QWidget* CheckBoxItem::view(QWidget* parent) {
    if (_view) return _view;
    _view = new QWidget(parent);
    auto* layout = new QHBoxLayout;
    _field = new QCheckBox(_view);
    _field->setCheckState(boolToState(_defaultValue));
    if (_value != nullptr) {
        _field->setCheckState(valueToState(_value));
    }
    layout->addWidget(_field);
    layout->addWidget(createLabel());
    layout->addStretch();
    _view->setLayout(layout);
    return _view;
}

QString CheckBoxItem::value() {
    if (!_field) return (_value != nullptr) ? _value : stateToValue(boolToState(_defaultValue));
    return stateToValue(_field->checkState());
}

void CheckBoxItem::setValue(QString value) {
    _value = value;
    if (!_field) return;
    _field->setCheckState(valueToState(_value));
}

QString CheckBoxItem::defaultValue() { return stateToValue(boolToState(_defaultValue)); }

Qt::CheckState CheckBoxItem::boolToState(bool isChecked) {
    return isChecked ? Qt::Checked : Qt::Unchecked;
}

QString CheckBoxItem::stateToValue(Qt::CheckState state) {
    if (state == Qt::Checked) return QString("true");
    if (state == Qt::Unchecked) return QString("false");
    return "";
}

Qt::CheckState CheckBoxItem::valueToState(const QString& value) {
    if (value == QString("true")) return Qt::Checked;
    return Qt::Unchecked;
}
