set(UB_TEST_SUIT ub_qt5_tests)
project(${UB_TEST_SUIT})

get_filename_component(PARENT_SOURCE_DIR ../ ABSOLUTE)

include(${PARENT_SOURCE_DIR}/cmake/gtest.cmake)

include_directories(${PARENT_SOURCE_DIR})

file(GLOB UB_TEST_SOURCES
        *.cpp
        *.hpp)

add_executable(${UB_TEST_SUIT}
        ${UB_TEST_SOURCES})

target_link_libraries(${UB_TEST_SUIT} utility_boilerplate_qt5)
target_link_libraries(${UB_TEST_SUIT} gtest gtest_main)

gtest_discover_tests(${UB_TEST_SUIT})