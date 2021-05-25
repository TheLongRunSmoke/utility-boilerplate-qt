#include "comboboxitem.hpp"

#include <QLabel>
#include <debug_new>
#include <utility>

ComboBoxItem::ComboBoxItem(QString key, QString name, QStringList elements, const QString &defaultValue)
        : UserSettingItem(std::move(key)),
          _name{std::move(name)},
          _elements{std::move(elements)} {
    if (_elements.contains(defaultValue, Qt::CaseInsensitive)) _defaultValue = defaultValue;
}

QWidget *ComboBoxItem::view(QWidget *parent) {
    if (_view) return _view;
    _view = new QWidget(parent);
    auto *layout = new QHBoxLayout;
    _comboBox = new QComboBox(_view);
    _comboBox->addItems(_elements);
    if (_comboBox->count() > 0) {
        _comboBox->setCurrentIndex(0);
    }
    if (_defaultValue != nullptr) {
        _comboBox->setCurrentIndex(_elements.indexOf(QRegExp(_defaultValue, Qt::CaseInsensitive)));
    }
    if (_value != nullptr) {
        _comboBox->setCurrentIndex(_elements.indexOf(QRegExp(_value, Qt::CaseInsensitive)));
    }
    auto *label = new QLabel(_view);
    label->setTextFormat(Qt::TextFormat::PlainText);
    label->setText(_name);
    label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    label->setBuddy(_comboBox);
    layout->addWidget(label);
    layout->addWidget(_comboBox);
    layout->addStretch();
    _view->setLayout(layout);
    return _view;
}

QString ComboBoxItem::value() {
    if (!_comboBox) return defaultValue();
    if (_comboBox->count() == 0) return defaultValue();
    return _elements.at(_comboBox->currentIndex());
}

QString ComboBoxItem::defaultValue() {
    if (_defaultValue != nullptr) return _defaultValue;
    if (_elements.isEmpty()) return QString("");
    return _elements.first();
}

void ComboBoxItem::setValue(QString value) {
    if (!_elements.contains(value, Qt::CaseInsensitive)) return;
    _value = value;
    if (!_comboBox) return;
    _comboBox->setCurrentIndex(_elements.indexOf(_value));
}

ComboBoxItem::~ComboBoxItem() {
    delete _comboBox;
    delete _view;
}
