#include <gtest/gtest.h>

#include <QApplication>
#include <QMainWindow>

namespace ubTestSuit {

    /**
     * Fixture to test UI related things.
     * Take a note, this use default QApplication and QMainWindow classes.
     */
    class UiFixture : public ::testing::Test {
      protected:
        QApplication* app;
        QMainWindow* window;
        // Explicitly run it in offscreen, to make it work in GitHub Actions.
        int argc = 3;
        const char* argv[3] = {"", "--platform", "offscreen"};

        void SetUp() override {
            app = new QApplication(argc, const_cast<char**>(argv));
            window = new QMainWindow();
        }

        void TearDown() override {
            delete window;
            delete app;
        }
    };

    template <typename T> T* findQWidgetByClass(QWidget* widget) {
        return widget->findChildren<T*>().first();
    }

}  // namespace ubTestSuit
