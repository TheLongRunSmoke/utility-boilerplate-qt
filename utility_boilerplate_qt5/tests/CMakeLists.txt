# Prepare project name.
set(UB_TEST_SUIT ub_qt5_tests)
project(${UB_TEST_SUIT})

# Get parent directory and include source of project under test.
set(PARENT_SOURCE_DIR "")
get_parent_dir(${PROJECT_SOURCE_DIR} PARENT_SOURCE_DIR)
include_directories(${PARENT_SOURCE_DIR})
include_directories(${PARENT_SOURCE_DIR})

# Include Google Test.
include(${PARENT_SOURCE_DIR}/cmake/gtest.cmake)

# Find tests sources.
file(GLOB UB_TEST_SOURCES
        *.cpp
        *.hpp)

# Create tests project and link with libraries.
add_executable(${UB_TEST_SUIT}
        ${UB_TEST_SOURCES})
target_link_libraries(${UB_TEST_SUIT}
        utility_boilerplate_qt5)
target_link_libraries(${UB_TEST_SUIT}
        gtest
        gtest_main)

# Make it discoverable for CTest.
gtest_discover_tests(${UB_TEST_SUIT})
