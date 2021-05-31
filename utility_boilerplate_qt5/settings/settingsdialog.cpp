#include <QDialogButtonBox>
#include <QPushButton>
#include <QGridLayout>
#include "settingsdialog.hpp"
#include "settingschangedevent.hpp"
#include "../utilitymainwindow.hpp"
#include <debug_new>

SettingsDialog::SettingsDialog(
        Settings* settings,
        QWidget* parent)
        : QDialog(parent),
          _settings{settings} {
    auto* mainLayout = new QVBoxLayout(this);
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    // Collect user setting controls to layout.
    auto* layout = new QVBoxLayout();
    layout->setSpacing(0);
    auto p = _settings->items();
    for (auto const& it = p.first; p.first != p.second; p.first++) {
        layout->addWidget(it->get()->view(this));
    }
    auto* widget = new QWidget();
    widget->setLayout(layout);
    mainLayout->addWidget(widget);
    // Create button box.
    auto* buttonBox = new QDialogButtonBox(
            QDialogButtonBox::Ok |
            QDialogButtonBox::Cancel |
            QDialogButtonBox::Apply,
            Qt::Horizontal);
    connect(buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, this, &SettingsDialog::apply);
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
    apply();
    QDialog::accept();
}

void SettingsDialog::apply() {
    _settings->saveUserSettings();
    // If you have few entities that must be notified about settings changing add it here.
    for (auto const& it: QApplication::topLevelWidgets()) {
        if (it->objectName() == UtilityMainWindow::objectName()) {
            QCoreApplication::sendEvent(it, new SettingsChangedEvent());
        }
    }
}
