#include <QDialogButtonBox>
#include <QPushButton>
#include <QGridLayout>
#include "settingsdialog.hpp"
#include <debug_new>

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent) {

    _settings = new Settings();

    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);

    auto *layout = new QVBoxLayout();
    auto p = _settings->items();
    for (; p.first != p.second; p.first++) {
        layout->addWidget(p.first->get()->view(this));
    }
    auto *widget = new QWidget();
    widget->setLayout(layout);
    mainLayout->addWidget(widget);

    auto *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    mainLayout->addWidget(buttonBox);

    setLayout(mainLayout);
}

SettingsDialog::~SettingsDialog() {
    delete _settings;
}

void SettingsDialog::accept() {
    _settings->saveUserSettings();
    QDialog::accept();
}
