# Include Google Test.
include(../../../cmake/gtest.cmake)

# Find tests sources.
file(GLOB_RECURSE UB_TEST_SOURCES *.cpp *.hpp)

# Create tests project and link with libraries.
add_executable(ub_qt5_tests ${UB_TEST_SOURCES})

target_link_libraries(ub_qt5_tests utility_boilerplate_qt5)
target_link_libraries(ub_qt5_tests gtest gtest_main gcov)

# Make it discoverable for CTest.
add_test(NAME utility_boilerplate_qt5_tests COMMAND ub_qt5_tests)
