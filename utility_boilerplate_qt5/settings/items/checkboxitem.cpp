#include "checkboxitem.hpp"
#include <QLabel>
#include <debug_new>
#include <utility>

CheckBoxItem::CheckBoxItem(
        QString key,
        QString name,
        bool defaultValue)
        : UserSettingItem(std::move(key)),
          _name(std::move(name)),
          _defaultValue(defaultValue) {}

CheckBoxItem::~CheckBoxItem() {
    delete _checkBox;
    delete _view;
}

QWidget* CheckBoxItem::view(QWidget* parent) {
    if (_view) return _view;
    _view = new QWidget(parent);
    auto* layout = new QHBoxLayout;
    _checkBox = new QCheckBox(_view);
    _checkBox->setCheckState(boolToState(_defaultValue));
    if (_value != nullptr) {
        _checkBox->setCheckState(valueToState(_value));
    }
    layout->addWidget(_checkBox);
    auto* label = new QLabel(_view);
    label->adjustSize();
    label->setTextFormat(Qt::TextFormat::PlainText);
    label->setText(_name);
    label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    label->setBuddy(_checkBox);
    layout->addWidget(label);
    layout->addStretch();
    _view->setLayout(layout);
    return _view;
}

QString CheckBoxItem::value() {
    return stateToValue(_checkBox->checkState());
}

void CheckBoxItem::setValue(QString value) {
    _value = value;
    if (!_checkBox) return;
    _checkBox->setCheckState(valueToState(_value));
}

QString CheckBoxItem::defaultValue() {
    return stateToValue(boolToState(_defaultValue));
}

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
