#include "comboboxitemwdata.hpp"

#include <debug_new>

ComboBoxItemWithData::ComboBoxItemWithData(QString key, QString name,
                                           std::map<QString, QVariant> elements,
                                           const QString& defaultValue, QString toolTip)
    : SimpleSettingItem<QComboBox>(std::move(key), std::move(name), std::move(toolTip)),
      _elements{std::move(elements)} {
    auto const& element = _elements.find(defaultValue);
    if (element != _elements.end()) {
        _defaultValue = defaultValue;
    } else {
        _defaultValue = nullptr;
    }
}

QWidget* ComboBoxItemWithData::view(QWidget* parent) {
    if (_view) return _view;
    _view = new QWidget(parent);
    auto* layout = new QHBoxLayout;
    _field = new QComboBox(_view);
    for (const auto& it : _elements) {
        _field->addItem(it.second.toString(), it.first);
    }
    if (_field->count() > 0) {
        _field->setCurrentIndex(0);
    }
    if (_defaultValue != nullptr) {
        _field->setCurrentIndex(_field->findData(_defaultValue));
    }
    if (_value != nullptr) {
        _field->setCurrentIndex(_field->findData(_value));
    }
    layout->addWidget(createLabel());
    layout->addWidget(_field);
    layout->addStretch();
    _view->setLayout(layout);
    return _view;
}

QString ComboBoxItemWithData::value() {
    if (!_field) return (_value != nullptr) ? _value : defaultValue();
    if (_field->count() == 0) return defaultValue();
    return _field->currentData().toString();
}

QString ComboBoxItemWithData::defaultValue() {
    if (_defaultValue != nullptr) return _defaultValue;
    if (_elements.empty()) return QString("");
    return _elements.begin()->first;
}

void ComboBoxItemWithData::setValue(QString value) {
    if (_elements.find(value) == _elements.end()) return;
    _value = value;
    if (!_field) return;
    _field->setCurrentIndex(_field->findData(_value));
}
