#include <gtest/gtest.h>
#include "../fixtures.hpp"

#include <chrono>
#include <thread>

#include "settingsdialog.hpp"

namespace ubTestSuit {

    TEST_F(UiFixture, SettingsDialog_initialization) {  // NOLINT(cert-err58-cpp)
        SettingsDialog settingsDialog(new Settings());
    }

    TEST_F(UiFixture, SettingsDialog_accept_apply) {  // NOLINT(cert-err58-cpp)
        SettingsDialog settingsDialog(new Settings());
        settingsDialog.accept();
        // Wait a moment to let a retranslateUi() to run.
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

}  // namespace ubTestSuit
