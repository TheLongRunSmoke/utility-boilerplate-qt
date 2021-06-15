#include "comboboxitem.hpp"

#include <debug_new>

ComboBoxItem::ComboBoxItem(QString key, QString name, QStringList elements,
                           const QString& defaultValue, QString toolTip)
    : SimpleSettingItem(std::move(key), std::move(name), std::move(toolTip)),
      _elements{std::move(elements)} {
    if (_elements.contains(defaultValue, Qt::CaseInsensitive)) _defaultValue = defaultValue;
}

QWidget* ComboBoxItem::view(QWidget* parent) {
    if (_view) return _view;
    _view = new QWidget(parent);
    auto* layout = new QHBoxLayout;
    _field = new QComboBox(_view);
    _field->addItems(_elements);
    if (_field->count() > 0) {
        _field->setCurrentIndex(0);
    }
    if (_defaultValue != nullptr) {
        _field->setCurrentIndex(_elements.indexOf(QRegExp(_defaultValue, Qt::CaseInsensitive)));
    }
    if (_value != nullptr) {
        _field->setCurrentIndex(_elements.indexOf(QRegExp(_value, Qt::CaseInsensitive)));
    }
    layout->addWidget(createLabel());
    layout->addWidget(_field);
    layout->addStretch();
    _view->setLayout(layout);
    return _view;
}

QString ComboBoxItem::value() {
    if (!_field) return (_value != nullptr) ? _value : defaultValue();
    if (_field->count() == 0) return defaultValue();
    return _elements.at(_field->currentIndex());
}

QString ComboBoxItem::defaultValue() {
    if (_defaultValue != nullptr) return _defaultValue;
    if (_elements.isEmpty()) return QString("");
    return _elements.first();
}

void ComboBoxItem::setValue(QString value) {
    if (!_elements.contains(value, Qt::CaseInsensitive)) return;
    _value = value;
    if (!_field) return;
    _field->setCurrentIndex(_elements.indexOf(QRegExp(_value, Qt::CaseInsensitive)));
}
