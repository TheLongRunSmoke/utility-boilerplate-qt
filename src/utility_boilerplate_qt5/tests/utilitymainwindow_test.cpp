#include <gtest/gtest.h>
#include "fixtures.hpp"

#include "utilitymainwindow.hpp"

namespace ubTestSuit {

    TEST_F(UiFixture, UtilityMainWindow_initialization) {  // NOLINT(cert-err58-cpp)
        EXPECT_EQ(window->objectId(), "1000");
    }

}  // namespace ubTestSuit
