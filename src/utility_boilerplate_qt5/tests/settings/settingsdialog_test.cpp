#include <gtest/gtest.h>
#include "../fixtures.hpp"

#include "settingsdialog.hpp"

namespace ubTestSuit {

    TEST_F(UiFixture, SettingsDialog_initialization) {  // NOLINT(cert-err58-cpp)
        SettingsDialog settingsDialog(new Settings());
    }

    TEST_F(UiFixture, SettingsDialog_accept_apply) {  // NOLINT(cert-err58-cpp)
        SettingsDialog settingsDialog(new Settings());
        settingsDialog.accept();
    }

    TEST_F(UiFixture, SettingsDialog_event) {  // NOLINT(cert-err58-cpp)
        SettingsDialog settingsDialog(new Settings());
        QCoreApplication::sendEvent(&settingsDialog, new QEvent(QEvent::LanguageChange));
    }

}  // namespace ubTestSuit
