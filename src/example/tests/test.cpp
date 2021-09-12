#include <gtest/gtest.h>

#include "fixtures.hpp"
#include "mainwindow.hpp"

namespace appTestSuit {

    /**
     * Check for environment integrity.
     */
    TEST(Smoke, CheckEnvironment) {  // NOLINT(cert-err58-cpp)
        ASSERT_EQ(MainWindow::objectId(), QString::number(1000, 10));
    }

    /**
     * Check that Qt UI platform set correctly.
     */
    TEST_F(AppUiFixture, Smoke) {  // NOLINT(cert-err58-cpp)
        ASSERT_EQ(QApplication::platformName(), "offscreen");
    }

    // FIXME: Not require user action, but hanging in GitHubAction for some reason. @thelongrunsmoke
    TEST_F(AppUiFixture, DISABLED_loadFile) {  // NOLINT(cert-err58-cpp)
        window->loadFile("settings.ini");
        QApplication::exit(0);
    }
}  // namespace appTestSuit
