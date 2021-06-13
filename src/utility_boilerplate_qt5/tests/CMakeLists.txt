# Include Google Test.
include(../../../cmake/gtest.cmake)

# Find tests sources.
file(GLOB UB_TEST_SOURCES settings/items/*.cpp *.cpp *.hpp)

# Create tests project and link with libraries.
add_executable(ub_qt5_tests ${UB_TEST_SOURCES})

target_link_libraries(ub_qt5_tests utility_boilerplate_qt5)

target_link_libraries(ub_qt5_tests gtest gtest_main gcov)

# Make it discoverable for CTest.
gtest_discover_tests(ub_qt5_tests)

add_custom_command(
    TARGET ub_qt5_tests
    POST_BUILD
    COMMAND windeployqt ${CMAKE_BINARY_DIR}/ub_qt5_tests.exe
)
