#include <gtest/gtest.h>

#include "fixtures.hpp"
#include "mainwindow.hpp"

namespace appTestSuit {

    TEST(Smoke, CheckEnvironment) {  // NOLINT(cert-err58-cpp)
        ASSERT_EQ(MainWindow::objectId(), QString::number(1000, 10));
    }

    TEST_F(AppUiFixture, Smoke) {  // NOLINT(cert-err58-cpp)
        ASSERT_EQ(QApplication::platformName(), "offscreen");
    }

    TEST_F(AppUiFixture, loadFile) {
        window->loadFile("settings.ini");
        QApplication::exit(0);
    }
}  // namespace appTestSuit
