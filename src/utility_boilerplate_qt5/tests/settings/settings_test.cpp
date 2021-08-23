#include <gtest/gtest.h>
#include "../fixtures.hpp"

#include "settings.hpp"

namespace ubTestSuit {

    TEST_F(UiFixture, Settings_windowGeometry) {  // NOLINT(cert-err58-cpp)
        Settings settings;
        QByteArray fixture = QByteArray();
        fixture.append("cowcowcow");
        settings.putWindowGeometry(fixture);
        EXPECT_EQ(settings.windowGeometry(), fixture);
    }

    TEST_F(UiFixture, Settings_windowState) {  // NOLINT(cert-err58-cpp)
        Settings settings;
        QByteArray fixture = QByteArray();
        fixture.append("cowcowcow");
        settings.putWindowState(fixture);
        EXPECT_EQ(settings.windowState(), fixture);
    }

    TEST_F(UiFixture, Settings_recentFiles) {  // NOLINT(cert-err58-cpp)
        Settings settings;
        settings.clearRecentFiles();
        settings.setRecentFilesLimit(5);
        EXPECT_EQ(settings.recentFilesLimit(), 5);
        EXPECT_FALSE(settings.hasRecentFiles());
        EXPECT_EQ(settings.recentFiles().size(), 0);
        settings.putRecentFile("test_recent_file");
        EXPECT_TRUE(settings.hasRecentFiles());
        EXPECT_EQ(settings.recentFiles().size(), 1);

        settings.clearRecentFiles();
        settings.setRecentFilesLimit(0);
        EXPECT_FALSE(settings.hasRecentFiles());
        EXPECT_EQ(settings.recentFiles().size(), 0);
        settings.putRecentFile("test_recent_file");
        EXPECT_FALSE(settings.hasRecentFiles());
        EXPECT_EQ(settings.recentFiles().size(), 0);
    }

    TEST_F(UiFixture, Settings_initDefaults) {  // NOLINT(cert-err58-cpp)
        Settings settings;
        settings.initDefaults();
    }

    TEST_F(UiFixture, Settings_loadTranslation) {  // NOLINT(cert-err58-cpp)
        auto* translator = new QTranslator();
        Settings::loadTranslation("en", translator);
        Settings::loadTranslation("ru", translator);
        Settings::loadTranslation("not_exist", translator);
        delete translator;
    }

    TEST_F(UiFixture, Settings_key) {  // NOLINT(cert-err58-cpp)
        EXPECT_EQ(Settings::key("Section", "key"), "Section/key");
    }

    TEST_F(UiFixture, Settings_retranslateUi) {  // NOLINT(cert-err58-cpp)
        Settings settings;
        settings.retranslateUi();
    }

    TEST_F(UiFixture, Settings_saveUserSettings) {  // NOLINT(cert-err58-cpp)
        Settings settings;
        settings.saveUserSettings();
    }

    TEST_F(UiFixture, Settings_items) {  // NOLINT(cert-err58-cpp)
        Settings settings;
        auto p = settings.items();
        for (auto const& it = p.first; p.first != p.second; p.first++) {
            it->get()->view(window);
        }
    }

}  // namespace ubTestSuit
