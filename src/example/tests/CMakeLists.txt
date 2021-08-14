# Include Google Test.
include(../../../cmake/gtest.cmake)

# Include QT UI headers.
include_directories(${PROJECT_BINARY_DIR}/${CMAKE_PROJECT_NAME}_autogen/include)

# Include project source.
include_directories(${PROJECT_SOURCE_DIR}/src/example)

file(
    GLOB
    UTILITY_BOILERPLATE_QT5_SOURCES
    ../../utility_boilerplate_qt5/*.hpp
    ../../utility_boilerplate_qt5/*.cpp
    ../../utility_boilerplate_qt5/settings/*.hpp
    ../../utility_boilerplate_qt5/settings/*.cpp
    ../../utility_boilerplate_qt5/settings/items/*.hpp
    ../../utility_boilerplate_qt5/settings/items/*.cpp
    ../../utility_boilerplate_qt5/settings/items/abstract/*.hpp
)

# Find tests sources.
file(GLOB TEST_SOURCES *.cpp *.hpp)
# Create tests project and link with libraries.
add_executable(tests ${TEST_SOURCES} ${UTILITY_BOILERPLATE_QT5_SOURCES} ${SOURCES})

target_link_libraries(tests utility_boilerplate_qt5)
target_link_libraries(tests gtest_main gtest gcov)

set_target_properties(utility_boilerplate_qt5 PROPERTIES COMPILE_FLAGS "--coverage" LINK_FLAGS "--coverage")

# Make it discoverable for CTest.
add_test(NAME app_tests COMMAND tests)
