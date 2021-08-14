cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(utility_boilerplate_qt_example VERSION 0.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include formatter support.
add_subdirectory(lib/3rd/Format.cmake)

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(FATAL_ERROR "In-source builds not allowed. Please make a build directory and run CMake from there.")
endif()

message("Check Qt version...")
execute_process(COMMAND qmake --version)
message("Check Qt requirements...")
find_package(
    Qt5 5.10
    COMPONENTS Core Widgets
    REQUIRED
)
message("Main project Qt requirements OK")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

include(./cmake/utils.cmake)

# If build type not set, let's assume it's a release.
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(BUILD_TYPE_LOWER_CASE "")
to_lower_case(${CMAKE_BUILD_TYPE} BUILD_TYPE_LOWER_CASE)

# Set where to find library object.
add_subdirectory(
    ${PROJECT_SOURCE_DIR}/src/utility_boilerplate_qt5 ${PROJECT_SOURCE_DIR}/src/utility_boilerplate_qt5/build/${BUILD_TYPE_LOWER_CASE}
)

# I use globbing here, because it's a small project and cmake reload do not need any significant time. Headers included to support some IDEs
# that not show files outside of cmake project sources. Explicitly include library qrc, otherwise its not be found.
file(GLOB SOURCES src/example/app.qrc src/utility_boilerplate_qt5/utility_boilerplate_qt5.qrc src/example/*.cpp src/example/*.hpp)

add_executable(${PROJECT_NAME} ${SOURCES} src/main.cpp)

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets utility_boilerplate_qt5)

# Collect translations.
file(GLOB_RECURSE I18N_QM *.qm)

# Copy translation to binaries folder.
foreach(FILE_PATH ${I18N_QM})
    get_filename_component(FILE_NAME ${FILE_PATH} NAME)
    configure_file(${FILE_PATH} ${PROJECT_BINARY_DIR}/translations/${FILE_NAME} COPYONLY)
endforeach()

# Add tests package.
option(CODE_COVERAGE "Enable coverage reporting" OFF)
if(CMAKE_BUILD_TYPE MATCHES Debug
   AND CODE_COVERAGE
   AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang"
)
    include(CTest)
    add_subdirectory(src/example/tests)

    target_compile_options(
        tests
        PUBLIC -O0 # no optimization
               -g # generate debug info
               --coverage # sets all required flags
    )
    target_link_options(tests PUBLIC --coverage)
endif()

# Copy dlls and other necessary files. For Windows only.
if(WIN32)
    message("Collecting binaries for Windows...")
    find_program(QT_DEPLOY windeployqt)
    if(QT_DEPLOY)
        add_custom_command(
            TARGET ${PROJECT_NAME}
            POST_BUILD
            COMMAND windeployqt --no-system-d3d-compiler ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.exe
        )
    else()
        message("Windeployqt not found.")
    endif()
endif()
