#include <gtest/gtest.h>
#include "mainwindow.hpp"

TEST(Smoke, CheckTestEnvironment) { // NOLINT(cert-err58-cpp)
    ASSERT_EQ(MainWindow::WINDOW_ID, 1000);
}