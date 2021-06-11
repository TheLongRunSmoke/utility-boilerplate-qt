#include <gtest/gtest.h>

#include "mainwindow.hpp"

TEST(Smoke, CheckEnvironment) {  // NOLINT(cert-err58-cpp)
    ASSERT_EQ(MainWindow::objectId(), QString::number(1000, 10));
}
