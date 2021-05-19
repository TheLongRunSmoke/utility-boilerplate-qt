cmake_minimum_required(VERSION 3.17)
project(utility_boilerplate_qt)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

include(${PROJECT_SOURCE_DIR}/utility_boilerplate_qt5/utils.cmake)

# If build type not set, let's assume it's a release.
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()

set(BUILD_TYPE_LOWER_CASE "")
to_lower_case(${CMAKE_BUILD_TYPE} BUILD_TYPE_LOWER_CASE)

# Set where to find library object.
add_subdirectory(
        ${PROJECT_SOURCE_DIR}/utility_boilerplate_qt5
        ${PROJECT_SOURCE_DIR}/utility_boilerplate_qt5/build/${BUILD_TYPE_LOWER_CASE})

# I use globbing here, because it's a small project and cmake reload do not need any significant time.
file(GLOB SOURCES
        utility_boilerplate_qt.qrc
        utility_boilerplate_qt5/utility_boilerplate_qt5.qrc
        *.cpp
        *.hpp)

add_executable(utility_boilerplate_qt ${SOURCES})

target_link_libraries(utility_boilerplate_qt
        Qt5::Core
        Qt5::Widgets
        utility_boilerplate_qt5)
