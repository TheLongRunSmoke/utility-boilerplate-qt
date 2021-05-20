#include "comboboxitem.hpp"

#include <QLabel>
#include <debug_new>

ComboBoxItem::ComboBoxItem(QString key, QString name, QStringList elements)
        : UserSettingItem(std::move(key)),
          _name{std::move(name)},
          _elements{std::move(elements)} {}

QWidget *ComboBoxItem::view(QWidget *parent) {
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

QString ComboBoxItem::value() {
    if (!_comboBox) return defaultValue();
    if (_comboBox->count() == 0) return defaultValue();
    return _elements.at(_comboBox->currentIndex());
}

ComboBoxItem::~ComboBoxItem() {
    delete _comboBox;
    delete _view;
}

QString ComboBoxItem::defaultValue() {
    if (_elements.isEmpty()) return QString("default");
    return _elements.first();
}
