#include <gtest/gtest.h>
#include "mainwindow.hpp"

TEST(Smoke, CheckEnvironment) { // NOLINT(cert-err58-cpp)
    ASSERT_EQ(MainWindow::objectName(), 1000);
}