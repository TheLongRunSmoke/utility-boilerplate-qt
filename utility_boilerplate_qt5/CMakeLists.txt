cmake_minimum_required(VERSION 3.17)
project(utility_boilerplate_qt5)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message("Check subproject Qt requirements...")
find_package(Qt5 5.10 COMPONENTS Core Widgets REQUIRED)
message("Subproject Qt requirements OK")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

include(utils.cmake)

# I use globbing here, because it's a small project and cmake reload do not need any significant time.
file(GLOB UTILITY_BOILERPLATE_QT5_SOURCES
        utility_boilerplate_qt5.qrc
        *.cpp
        *.hpp
        settings/*.*
        settings/items/*.*
        nvwa/include/debug_new)

# If build type not set, let's assume it's a release.
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()

set(BUILD_TYPE_LOWER_CASE "")
to_lower_case(${CMAKE_BUILD_TYPE} BUILD_TYPE_LOWER_CASE)

# For debug build add nvwa library.
if (CMAKE_BUILD_TYPE MATCHES Debug)
    file(GLOB NVWA_SOURCE
            nvwa/*.*)
    list(APPEND UTILITY_BOILERPLATE_QT5_SOURCES
            ${NVWA_SOURCE})
endif ()

add_library(utility_boilerplate_qt5 STATIC
        ${UTILITY_BOILERPLATE_QT5_SOURCES})

# Set different output directories for different build types, to prevent any chance of heterotrophic build.
# Use LIBRARY_OUTPUT_DIRECTORY if you want to link dynamically.
set_target_properties(utility_boilerplate_qt5 PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY
        ${PROJECT_BINARY_DIR}/${BUILD_TYPE_LOWER_CASE})

# Include nvwa header to use it in angle brackets.
include_directories(nvwa/include)
target_include_directories(utility_boilerplate_qt5 INTERFACE nvwa/include)

target_link_libraries(utility_boilerplate_qt5
        Qt5::Core
        Qt5::Widgets)
