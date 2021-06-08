# Prepare project name.
project(ub_qt5_tests)

# Get parent directory and include source of project under test.
set(PARENT_SOURCE_DIR "")
get_parent_dir(${PROJECT_SOURCE_DIR} PARENT_SOURCE_DIR)
include_directories(${PARENT_SOURCE_DIR})

# Include Google Test.
include(../../../cmake/gtest.cmake)

# Find tests sources.
file(GLOB UB_TEST_SOURCES settings/items/*.cpp *.cpp *.hpp)

# Create tests project and link with libraries.
add_executable(${PROJECT_NAME} ${UB_TEST_SOURCES})
target_link_libraries(${PROJECT_NAME} utility_boilerplate_qt5)
target_link_libraries(${PROJECT_NAME} gtest gtest_main gcov)

# Make it discoverable for CTest.
gtest_discover_tests(${PROJECT_NAME})
