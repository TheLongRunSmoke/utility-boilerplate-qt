cmake_minimum_required(VERSION 3.17)
project(utility_boilerplate_qt5)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

file(GLOB UTILITY_BOILERPLATE_QT5_SOURCES
        utility_boilerplate_qt5.qrc
        *.cpp
        settings/*.cpp)

add_library(utility_boilerplate_qt5 STATIC ${UTILITY_BOILERPLATE_QT5_SOURCES})

target_link_libraries(utility_boilerplate_qt5
        Qt5::Core
        Qt5::Widgets)
