#include <gtest/gtest.h>

#include <QApplication>
#include "../mainwindow.hpp"

namespace appTestSuit {

    class AppUiFixture : public ::testing::Test {
      protected:
        QApplication* app{};
        MainWindow* window{};
        const char* argv[2] = {"--platform", "offscreen"};

        void SetUp() override {
            int arg = 2;
            app = new QApplication(arg, const_cast<char**>(argv));
            window = new MainWindow();
        }

        void TearDown() override {
            delete window;
            delete app;
        }
    };

}  // namespace appTestSuit
