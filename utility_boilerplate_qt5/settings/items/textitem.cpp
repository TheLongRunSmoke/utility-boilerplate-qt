#include "textitem.hpp"

#include <utility>
#include <QLabel>
#include <debug_new>

TextItem::TextItem(
        QString key,
        QString name,
        QString defaultValue)
        : UserSettingItem(std::move(key)),
          _name{std::move(name)},
          _defaultValue{std::move(defaultValue)} {}

TextItem::~TextItem() {
    delete _lineEdit;
    delete _view;
}

QWidget* TextItem::view(QWidget* parent) {
    if (_view) return _view;
    _view = new QWidget(parent);
    auto* layout = new QHBoxLayout;
    _lineEdit = new QLineEdit(_view);
    if (_defaultValue != nullptr) {
        _lineEdit->setText(defaultValue());
    }
    if (_value != nullptr) {
        _lineEdit->setText(_value);
    }
    auto* label = new QLabel(_view);
    label->setTextFormat(Qt::TextFormat::PlainText);
    label->setText(_name);
    label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    label->setBuddy(_lineEdit);
    layout->addWidget(label);
    layout->addWidget(_lineEdit);
    layout->addStretch();
    _view->setLayout(layout);
    return _view;
}

QString TextItem::value() {
    if (!_lineEdit) return defaultValue();
    return _lineEdit->text();
}

void TextItem::setValue(QString value) {
    _value = value;
    if (_value == nullptr) _value = "";
    if (!_lineEdit) return;
    _lineEdit->setText(_value);

}

QString TextItem::defaultValue() {
    if (_defaultValue == nullptr) return "";
    return _defaultValue;
}
