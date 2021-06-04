cmake_minimum_required(VERSION 3.14)

project(utility_boilerplate_qt VERSION 0.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message("Check Qt version...")
execute_process(COMMAND qmake --version)
message("Check Qt requirements...")
find_package(Qt5 5.10 COMPONENTS Core Widgets REQUIRED)
message("Main project Qt requirements OK")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

include(${PROJECT_SOURCE_DIR}/utility_boilerplate_qt5/cmake/utils.cmake)

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
# Headers included to support some IDEs that not show files outside of cmake project sources.
file(GLOB SOURCES
        utility_boilerplate_qt.qrc
        utility_boilerplate_qt5/utility_boilerplate_qt5.qrc
        *.cpp
        *.hpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
        Qt5::Core
        Qt5::Widgets
        utility_boilerplate_qt5)

# Collect translations.
file(GLOB_RECURSE I18N_QM
        *.qm)

# Copy translation to binaries folder.
foreach (FILE_PATH ${I18N_QM})
    get_filename_component(FILE_NAME ${FILE_PATH} NAME)
    configure_file(${FILE_PATH}
            ${PROJECT_BINARY_DIR}/i18n/${FILE_NAME}
            COPYONLY)
endforeach ()

# Add tests package.
include(CTest)
add_subdirectory(tests)
