cmake_minimum_required(VERSION 3.17)

set(TEST_SUIT tests)

project(${TEST_SUIT})

get_filename_component(PARENT_SOURCE_DIR ../ ABSOLUTE)

include(${PARENT_SOURCE_DIR}/utility_boilerplate_qt5/cmake/gtest.cmake)

include_directories(${PARENT_SOURCE_DIR})
include_directories(${PARENT_SOURCE_DIR}/${PROJECT_BINARY_DIR}/utility_boilerplate_qt_autogen/include)

file(GLOB TEST_SOURCES
        *.cpp
        *.hpp)

add_executable(${TEST_SUIT}
        ${TEST_SOURCES})

target_link_libraries(${TEST_SUIT} utility_boilerplate_qt5)
target_link_libraries(${TEST_SUIT} gtest gtest_main)