#include <gtest/gtest.h>

#include "mainwindow.hpp"
#include "../utility_boilerplate_qt5/tests/fixtures.hpp"


TEST(Smoke, CheckEnvironment) {  // NOLINT(cert-err58-cpp)
    ASSERT_EQ(MainWindow::objectId(), QString::number(1000, 10));
}

TEST_F(UiFixture, loadFile) {
    window->loadFile("settings.ini");
    QApplication::exit(0);
}

