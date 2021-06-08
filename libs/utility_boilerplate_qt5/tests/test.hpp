#include <gtest/gtest.h>

#include <QApplication>
#include <QMainWindow>

namespace ubTestSuit {

    class UiFixture : public ::testing::Test {
      protected:
        QApplication *app{};
        QMainWindow *window{};
        char **argv{};

        void SetUp() override {
            int arg = 0;
            app = new QApplication(arg, argv);
            window = new QMainWindow();
        }

        void TearDown() override {
            delete window;
            delete app;
        }
    };

    template <typename T> T *findQWidgetByClass(QWidget *widget) {
        return widget->findChildren<T *>().first();
    }

}  // namespace ubTestSuit
