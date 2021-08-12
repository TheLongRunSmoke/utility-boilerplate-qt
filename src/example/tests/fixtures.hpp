#include <gtest/gtest.h>

#include <QApplication>
#include "../mainwindow.hpp"

namespace appTestSuit {

    /**
     * Fixture to test app UI related things.
     */
    class AppUiFixture : public ::testing::Test {
      protected:
        QApplication* app{};
        MainWindow* window{};
        // Explicitly run it in offscreen, to make it work in GitHub Actions.
        int argc = 3;
        const char* argv[3] = {"", "--platform", "offscreen"};

        void SetUp() override {
            app = new QApplication(argc, const_cast<char**>(argv));
            window = new MainWindow();
        }

        void TearDown() override {
            delete window;
            delete app;
        }
    };

}  // namespace appTestSuit
