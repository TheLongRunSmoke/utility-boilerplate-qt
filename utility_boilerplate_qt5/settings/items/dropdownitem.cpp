#include "dropdownitem.hpp"

#include <QLabel>

DropDownItem::DropDownItem(QString key, QString name, QStringList elements)
        : SettingItem(std::move(key)),
          _name{std::move(name)},
          _elements{std::move(elements)} {}

QWidget *DropDownItem::view(QWidget *parent) {
    if (_view) return _view;
    _view = new QWidget(parent);
    auto *layout = new QHBoxLayout;
    _comboBox = new QComboBox(_view);
    _comboBox->addItems(_elements);
    if (_comboBox->count() > 0) {
        _comboBox->setCurrentIndex(0);
    }
    auto *label = new QLabel(_view);
    label->setTextFormat(Qt::TextFormat::PlainText);
    label->setText(_name);
    label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    label->setBuddy(_comboBox);
    layout->addWidget(label);
    layout->addWidget(_comboBox);
    _view->setLayout(layout);
    return _view;
}

QString DropDownItem::value() {
    if (!_comboBox) return _elements.first();
    return _elements.at(_comboBox->currentIndex());
}

DropDownItem::~DropDownItem() {
    delete _view;
    delete _comboBox;
}
