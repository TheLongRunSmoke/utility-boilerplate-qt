#include "fixtures.hpp"

namespace ubTestSuit {

    /**
     * Check that Qt UI platform set correctly.
     */
    TEST_F(UiFixture, Smoke) {  // NOLINT(cert-err58-cpp)
        ASSERT_EQ(QApplication::platformName(), "offscreen");
    }

}  // namespace ubTestSuit
