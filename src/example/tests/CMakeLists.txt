# Include Google Test.
include(../../../cmake/gtest.cmake)

# Include QT UI headers.
include_directories(${PROJECT_BINARY_DIR}/${CMAKE_PROJECT_NAME}_autogen/include)

# Include project source.
include_directories(${PROJECT_SOURCE_DIR}/src/example)
file(GLOB APP_SOURCE ${PROJECT_SOURCE_DIR}/src/example/*.cpp)

message(${PROJECT_SOURCE_DIR})

file(
    GLOB
    UTILITY_BOILERPLATE_QT5_SOURCES
    ${PROJECT_SOURCE_DIR}/src/utility_boilerplate_qt5/*.hpp
    ${PROJECT_SOURCE_DIR}/src/utility_boilerplate_qt5/*.cpp
    ${PROJECT_SOURCE_DIR}/src/utility_boilerplate_qt5/settings/*.hpp
    ${PROJECT_SOURCE_DIR}/src/utility_boilerplate_qt5/settings/*.cpp
    ${PROJECT_SOURCE_DIR}/src/utility_boilerplate_qt5/settings/items/*.hpp
    ${PROJECT_SOURCE_DIR}/src/utility_boilerplate_qt5/settings/items/*.cpp
    ${PROJECT_SOURCE_DIR}/src/utility_boilerplate_qt5/settings/items/abstract/*.hpp
)

# Find tests sources.
file(GLOB TEST_SOURCES *.cpp *.hpp)

# Create tests project and link with libraries.
add_executable(tests ${TEST_SOURCES} ${APP_SOURCE} ${UTILITY_BOILERPLATE_QT5_SOURCES})

target_link_libraries(tests utility_boilerplate_qt5)
target_link_libraries(tests gtest gtest_main gcov)

# Make it discoverable for CTest.
gtest_discover_tests(tests)
