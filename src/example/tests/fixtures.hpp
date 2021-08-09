#include <gtest/gtest.h>

#include <QApplication>
#include "../mainwindow.hpp"

namespace appTestSuit {

    class AppUiFixture : public ::testing::Test {
      protected:
        QApplication* app{};
        MainWindow* window{};
        int argc = 3;
        const char* argv[3] = {"", "--platform", "offscreen"};

        void SetUp() override {
            app = new QApplication(argc, const_cast<char**>(argv));
            window = new MainWindow();
            qInfo("platform: %s", QApplication::platformName().toStdString().c_str());
        }

        void TearDown() override {
            delete window;
            delete app;
        }
    };

}  // namespace appTestSuit
