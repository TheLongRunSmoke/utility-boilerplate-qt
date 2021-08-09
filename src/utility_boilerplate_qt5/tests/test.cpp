#include "fixtures.hpp"

namespace ubTestSuit {
    TEST_F(UiFixture, Smoke) {  // NOLINT(cert-err58-cpp)
        ASSERT_EQ(QApplication::platformName(), "offscreen");
    }
}  // namespace ubTestSuit
