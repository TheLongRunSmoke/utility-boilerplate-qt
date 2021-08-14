cmake_minimum_required(VERSION 3.14)

project(utility_boilerplate_qt5 VERSION 1.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message("Check subproject Qt requirements...")
find_package(
    Qt5 5.10
    COMPONENTS Core Widgets
    REQUIRED
)
message("Subproject Qt requirements OK")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

include(../../cmake/utils.cmake)

# I use globbing here, because it's a small project and cmake reload do not need any significant time. Headers included to support some IDEs
# that not show files outside of cmake project sources.
file(
    GLOB
    UTILITY_BOILERPLATE_QT5_SOURCES
    utility_boilerplate_qt5.qrc
    *.hpp
    *.cpp
    settings/*.hpp
    settings/*.cpp
    settings/items/*.hpp
    settings/items/*.cpp
    settings/items/abstract/*.hpp
    nvwa/include/debug_new
)

set(UTILITY_BOILERPLATE_QT5_INCLUDES ${PROJECT_SOURCE_DIR} settings settings/items settings/items/abstract nvwa/include)

# If build type not set, let's assume it's a release.
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(BUILD_TYPE_LOWER_CASE "")
to_lower_case(${CMAKE_BUILD_TYPE} BUILD_TYPE_LOWER_CASE)

option(NVWA "Enable NVWA memory leak detection" OFF)
if(WIN32)
    set(NVWA OFF)
endif()

# For debug build add nvwa library.
if(NVWA AND CMAKE_BUILD_TYPE MATCHES Debug)
    message("Including NVWA...")
    if(WIN32)
        message("NVWA not recommended on Windows!")
    endif()
    file(GLOB NVWA_SOURCE nvwa/*.h nvwa/*.cpp)
    list(APPEND UTILITY_BOILERPLATE_QT5_SOURCES ${NVWA_SOURCE})
endif()

add_library(${PROJECT_NAME} STATIC ${UTILITY_BOILERPLATE_QT5_SOURCES})

# Set different output directories for different build types, to prevent any chance of heterotrophic build. Use LIBRARY_OUTPUT_DIRECTORY if
# you want to link dynamically.
set_target_properties(${PROJECT_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${BUILD_TYPE_LOWER_CASE})

# Include nvwa header to use it in angle brackets.
include_directories(${UTILITY_BOILERPLATE_QT5_INCLUDES})
target_include_directories(${PROJECT_NAME} INTERFACE ${UTILITY_BOILERPLATE_QT5_INCLUDES})

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets)

option(CODE_COVERAGE "Enable coverage reporting" OFF)
if(CMAKE_BUILD_TYPE MATCHES Debug
   AND CODE_COVERAGE
   AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang"
)
    include(CTest)
    add_subdirectory(tests)

    target_link_libraries(${PROJECT_NAME} gcov)

    target_compile_options(
        ub_qt5_tests
        PUBLIC -O0 # no optimization
               -g # generate debug info
               --coverage # sets all required flags
    )
    target_link_options(ub_qt5_tests PUBLIC --coverage)
endif()
