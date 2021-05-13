cmake_minimum_required(VERSION 3.17)
project(utility_boilerplate_qt5)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# I use glob here, because it's a small project and cmake reload do not need any significant time.
file(GLOB UTILITY_BOILERPLATE_QT5_SOURCES
        utility_boilerplate_qt5.qrc
        *.cpp
        *.hpp
        settings/*.cpp
        settings/*.hpp
        settings/items/*.cpp
        settings/items/*.hpp)

add_library(utility_boilerplate_qt5 STATIC ${UTILITY_BOILERPLATE_QT5_SOURCES})

target_link_libraries(utility_boilerplate_qt5
        Qt5::Core
        Qt5::Widgets)
