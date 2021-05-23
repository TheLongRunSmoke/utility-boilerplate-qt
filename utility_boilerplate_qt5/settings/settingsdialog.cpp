#include <QDialogButtonBox>
#include <QPushButton>
#include <QGridLayout>
#include "settingsdialog.hpp"
#include "settingschangedevent.hpp"
#include <debug_new>

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent) {
    _settings = new Settings();
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    // Collect user setting controls to layout.
    auto *layout = new QVBoxLayout();
    auto p = _settings->items();
    for (auto const &it = p.first; p.first != p.second; p.first++) {
        layout->addWidget(it->get()->view(this));
    }
    auto *widget = new QWidget();
    widget->setLayout(layout);
    mainLayout->addWidget(widget);
    // Create button box.
    auto *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    mainLayout->addWidget(buttonBox);
    // Add layout in to dialog window.
    setLayout(mainLayout);
}

SettingsDialog::~SettingsDialog() {
    delete _settings;
}

void SettingsDialog::accept() {
    _settings->saveUserSettings();
    qDebug("%d", QApplication::topLevelWidgets().length());
    QCoreApplication::sendEvent(QApplication::topLevelWidgets().at(0), new SettingsChangedEvent());
    QDialog::accept();
}
