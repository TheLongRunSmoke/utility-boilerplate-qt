#include <gtest/gtest.h>

#include "helpers.hpp"

namespace ubTestSuit {

    TEST(ub_helpers, parseFirstArgumentAsFile) {  // NOLINT(cert-err58-cpp)
        int argc = 3;
        const char* argvN[3] = {"", "--platform", "offscreen"};
        auto* app = new QApplication(argc, const_cast<char**>(argvN));
        QStringList result = ub_helpers::parseFirstArgumentAsFile(*app);
        EXPECT_EQ(result.length(), 0);
        delete app;
        argc = 4;
        const char* argvP[4] = {"", "firstArg.extension", "--platform", "offscreen"};
        app = new QApplication(argc, const_cast<char**>(argvP));
        result = ub_helpers::parseFirstArgumentAsFile(*app);
        EXPECT_EQ(result.length(), 1);
        EXPECT_EQ(result.first(), "firstArg.extension");
    }

}  // namespace ubTestSuit
