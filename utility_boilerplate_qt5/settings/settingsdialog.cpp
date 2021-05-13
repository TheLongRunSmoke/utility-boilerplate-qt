#include <QDialogButtonBox>
#include <QPushButton>
#include <QGridLayout>
#include "settingsdialog.hpp"

SettingsDialog::SettingsDialog(QWidget* parent) : QDialog(parent) {

    _settings = new Settings();

    auto* mainLayout = new QVBoxLayout(this);
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);

    auto* layout = new QVBoxLayout();
    for (auto const& it: *_settings->items()){
        layout->addWidget(it->view(this));
    }
    auto* widget = new QWidget();
    widget->setLayout(layout);
    mainLayout->addWidget(widget);

    auto* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    mainLayout->addWidget(buttonBox);

    setLayout(mainLayout);
}

SettingsDialog::~SettingsDialog() {
//    delete _settings;
}
