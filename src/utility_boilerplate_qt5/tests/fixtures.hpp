#include <gtest/gtest.h>

#include <QApplication>
#include <QMenuBar>

#include "helpers.hpp"
#include "utilitymainwindow.hpp"

namespace ubTestSuit {

    /**
     * Mock class for testing UtilityMainWindow that is virtual.
     */
    class TestUtilityMainWindow : public UtilityMainWindow {
        Q_OBJECT
      public:
        explicit TestUtilityMainWindow(QWidget* parent = Q_NULLPTR) : UtilityMainWindow(parent){};

        void updateRecentFiles_test() { updateRecentFiles(); }

        void checkRecentFilesAvailability_test() { checkRecentFilesAvailability(); }

        void newFile_test() { newFile(); }

      protected:
        void clearDocument() override {}

        bool isDocumentModified() override { return false; }

        bool saveFile(const QString& fileName) override { return true; }
    };

    /**
     * Fixture to test UI related things.
     * Take a note, this use default QApplication and QMainWindow classes.
     */
    class UiFixture : public ::testing::Test {
      protected:
        QApplication* app;
        TestUtilityMainWindow* window;
        // Explicitly run it in offscreen, to make it work in GitHub Actions.
        int argc = 3;
        const char* argv[3] = {"", "--platform", "offscreen"};

        void SetUp() override {
            app = new QApplication(argc, const_cast<char**>(argv));
            window = new TestUtilityMainWindow();
        }

        void TearDown() override {
            delete window;
            delete app;
        }
    };

    /**
     * Search child widget by class.
     *
     * @tparam T widget class to find.
     * @param widget parent widget.
     */
    template <typename T> T* findQWidgetByClass(QWidget* widget) {
        return widget->findChildren<T*>().first();
    }

}  // namespace ubTestSuit
