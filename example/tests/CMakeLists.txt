# Prepare project name.
project(tests)

# Get parent directory and include source of project under test.
set(PARENT_SOURCE_DIR "")
get_parent_dir(${PROJECT_SOURCE_DIR} PARENT_SOURCE_DIR)
include_directories(${PARENT_SOURCE_DIR})
get_parent_dir(${PARENT_SOURCE_DIR} PARENT_SOURCE_DIR)
include_directories(${PARENT_SOURCE_DIR})

# Include Google Test.
include(${PARENT_SOURCE_DIR}/utility_boilerplate_qt5/cmake/gtest.cmake)

# Include QT UI headers.
set(PARENT_UIC_DIR "")
get_parent_dir(${PROJECT_BINARY_DIR} PARENT_UIC_DIR)
get_parent_dir(${PARENT_UIC_DIR} PARENT_UIC_DIR)
include_directories(${PARENT_UIC_DIR}/${CMAKE_PROJECT_NAME}_autogen/include)

# Find tests sources.
file(GLOB TEST_SOURCES
        *.cpp
        *.hpp)

# Create tests project and link with libraries.
add_executable(${PROJECT_NAME}
        ${TEST_SOURCES})

target_link_libraries(${PROJECT_NAME}
        utility_boilerplate_qt5)

target_link_libraries(${PROJECT_NAME}
        gtest
        gtest_main)

# Make it discoverable for CTest.
gtest_discover_tests(${PROJECT_NAME})
