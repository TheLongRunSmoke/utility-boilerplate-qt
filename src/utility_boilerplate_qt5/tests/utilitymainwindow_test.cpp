#include <gtest/gtest.h>
#include "events.hpp"
#include "fixtures.hpp"

#include "utilitymainwindow.hpp"

namespace ubTestSuit {

    TEST_F(UiFixture, UtilityMainWindow_initialization) {  // NOLINT(cert-err58-cpp)
        EXPECT_EQ(window->objectId(), "1000");
    }

    TEST_F(UiFixture, UtilityMainWindow_event) {  // NOLINT(cert-err58-cpp)
        QCoreApplication::sendEvent(window, new SettingsChangedEvent());
        EXPECT_FALSE(window->isWindowModified());
        QCoreApplication::sendEvent(window, new DocumentModifiedEvent(true));
        EXPECT_TRUE(window->isWindowModified());
        QCoreApplication::sendEvent(window, new QEvent(QEvent::LanguageChange));
        QCoreApplication::sendEvent(window, new QEvent(QEvent::LocaleChange));
    }

    TEST_F(UiFixture, UtilityMainWindow_update) {  // NOLINT(cert-err58-cpp)
        QCoreApplication::sendEvent(window, new SettingsChangedEvent());
        EXPECT_FALSE(window->isWindowModified());
        QCoreApplication::sendEvent(window, new DocumentModifiedEvent(true));
        EXPECT_TRUE(window->isWindowModified());
        QCoreApplication::sendEvent(window, new QEvent(QEvent::LanguageChange));
        QCoreApplication::sendEvent(window, new QEvent(QEvent::LocaleChange));
    }

    TEST_F(UiFixture, UtilityMainWindow_updateRecentFiles) {  // NOLINT(cert-err58-cpp)
        Settings settings;
        settings.putRecentFile("test.test");
        window->updateRecentFiles_test();
    }

    TEST_F(UiFixture, UtilityMainWindow_checkRecentFilesAvailability) {  // NOLINT(cert-err58-cpp)
        window->checkRecentFilesAvailability_test();
    }

    TEST_F(UiFixture, UtilityMainWindow_newFile) {  // NOLINT(cert-err58-cpp)
        window->newFile_test();
    }

}  // namespace ubTestSuit
