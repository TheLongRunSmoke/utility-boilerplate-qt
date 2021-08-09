#include <gtest/gtest.h>

#include <QApplication>
#include <QMainWindow>

namespace ubTestSuit {

    class UiFixture : public ::testing::Test {
      protected:
        QApplication* app;
        QMainWindow* window;
        const char* argv[3] = {"", "--platform", "offscreen"};

        void SetUp() override {
            int argc = 3;
            app = new QApplication(argc, const_cast<char**>(argv));
            window = new QMainWindow();
            qInfo("platform: %s", QApplication::platformName().toStdString().c_str());
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
