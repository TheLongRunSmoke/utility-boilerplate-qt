#include <gtest/gtest.h>

#include "mainwindow.hpp"

TEST(Smoke, CheckEnvironment) {  // NOLINT(cert-err58-cpp)
    ASSERT_EQ(MainWindow::objectId(), QString::number(1000, 10));
}

TEST(MainWindow, loadFile) {
    QApplication* app{};
    char** argv{};
    int arg = 0;
    app = new QApplication(arg, argv);
    MainWindow window;
    window.loadFile("settings.ini");
    QApplication::exit(0);
}
