cmake_minimum_required(VERSION 3.17)
project(utility_boilerplate_qt)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "D:\\Qt\\5.15.0\\mingw81_64\\")

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

add_subdirectory("${PROJECT_SOURCE_DIR}/utility_boilerplate_qt5" "${PROJECT_SOURCE_DIR}/utility_boilerplate_qt5/build")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(
        utility_boilerplate_qt
        main.cpp
        utility_boilerplate_qt.qrc
        utility_boilerplate_qt5/utility_boilerplate_qt5.qrc
        mainwindow.cpp
        texteditor.cpp
        texteditor.ui
)

target_link_libraries(utility_boilerplate_qt
        Qt5::Core
        Qt5::Widgets
        utility_boilerplate_qt5)
