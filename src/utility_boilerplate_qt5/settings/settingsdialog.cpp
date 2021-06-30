#include "settingsdialog.hpp"

#include <QDialogButtonBox>
#include <QPushButton>
#include <debug_new>

#include "../events.hpp"
#include "../utilitymainwindow.hpp"

SettingsDialog::SettingsDialog(Settings* settings, QWidget* parent)
    : QDialog(parent), _settings{settings} {
    auto* mainLayout = new QVBoxLayout(this);
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    // Collect user setting controls to layout.
    mainLayout->addWidget(createUserSettingsWidget());
    // Create button box.
    auto* buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel | QDialogButtonBox::Apply, Qt::Horizontal);
    connect(buttonBox->button(QDialogButtonBox::Apply),
            &QPushButton::clicked,
            this,
            &SettingsDialog::apply);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    mainLayout->addWidget(buttonBox);
    // Add layout in to dialog window.
    setLayout(mainLayout);
}

SettingsDialog::~SettingsDialog() {
    delete _settings;
    delete _settingsWidget;
}

void SettingsDialog::accept() {
    apply();
    QDialog::accept();
}

void SettingsDialog::apply() {
    _settings->saveUserSettings();
    // If you have few entities that must be notified about settings changing add
    // it here.
    for (auto const& it : QApplication::topLevelWidgets()) {
        if (it->objectName() == UtilityMainWindow::objectId()) {
            QCoreApplication::sendEvent(it, new SettingsChangedEvent());
        }
    }
}

bool SettingsDialog::event(QEvent* event) {
    if (event->type() == QEvent::LanguageChange) {
        // App translator object change.
        retranslateUi();
    }
    return QWidget::event(event);
}

void SettingsDialog::retranslateUi() {
    _settings->retranslateUi();
    delete layout()->takeAt(0)->widget();
    auto* item = layout()->takeAt(0);
    layout()->addWidget(createUserSettingsWidget());
    layout()->addItem(item);
}

QWidget* SettingsDialog::createUserSettingsWidget() {
    auto* layout = new QVBoxLayout();
    layout->setSpacing(0);
    auto p = _settings->items();
    for (auto const& it = p.first; p.first != p.second; p.first++) {
        layout->addWidget(it->get()->view(this));
    }
    _settingsWidget = new QWidget();
    _settingsWidget->setLayout(layout);
    return _settingsWidget;
}
