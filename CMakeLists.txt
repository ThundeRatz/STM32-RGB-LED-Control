# Name: CMakeLists file
# ThundeRatz Robotics Team
# Brief: This file contains the configuration of the CMake project
## and all the files that you should edit to configure your project
# 09/2024

cmake_minimum_required(VERSION 3.22)

###############################################################################
## CMake Configuration
###############################################################################

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Gets all directories from /lib path
file(GLOB V_GLOB LIST_DIRECTORIES true "lib/*")
foreach(item ${V_GLOB})
	if(IS_DIRECTORY ${item})
		list(APPEND CMAKE_MODULE_PATH ${item}/cmake)
	endif()
endforeach()

# Debug, Release, RelWithDebInfo and MinSizeRel
# @see: https://cmake.org/cmake/help/latest/variable/CMAKE_BUILD_TYPE.html
set(CMAKE_BUILD_TYPE Debug)

###############################################################################
## Project Configuration
###############################################################################

set(CMAKE_PROJECT_NAME rgb_led_control)

# Set the board version to an empty string if your board doesn't have a version
set(BOARD_VERSION v1)

# Device Configuration
set(DEVICE STM32F411CE)

if(BOARD_VERSION STREQUAL "")
    set(PROJECT_RELEASE ${CMAKE_PROJECT_NAME})
else()
    set(PROJECT_RELEASE ${CMAKE_PROJECT_NAME}_${BOARD_VERSION})
endif()
set(TARGET_BOARD target_${PROJECT_RELEASE})

###############################################################################
## Global compilation config
###############################################################################

set(LAUNCH_JSON_PATH ${CMAKE_CURRENT_SOURCE_DIR}/.vscode/launch.json)
set(DEBUG_FILE_NAME ${CMAKE_PROJECT_NAME})

include(cmake/config_validation.cmake)

set(CMAKE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cube)
include(cube/cmake/gcc-arm-none-eabi.cmake)
set(CMAKE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

project(${CMAKE_PROJECT_NAME} C CXX ASM)

include(cmake/workspace.cmake)
include(cmake/targets.cmake)
include(cmake/utilities.cmake)
include(cmake/linter.cmake)

add_subdirectory(cube/cmake/stm32cubemx)

###############################################################################
## Input files
###############################################################################

file(GLOB_RECURSE FORMAT_SOURCES CONFIGURE_DEPENDS "src/*.cpp" "config/*.cpp" "tests/*.cpp")
file(GLOB_RECURSE FORMAT_HEADERS CONFIGURE_DEPENDS "inc/*.hpp" "config/*.hpp" "tests/*.hpp")

targets_generate_format_target(FORMAT_SOURCES FORMAT_HEADERS)

file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS "src/*.cpp")
list(REMOVE_ITEM PROJECT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

file(GLOB_RECURSE PROJECT_TESTS_SOURCES CONFIGURE_DEPENDS "tests/src/*.cpp")
file(GLOB_RECURSE PROJECT_TESTS_BIN CONFIGURE_DEPENDS "tests/bin/*.cpp")

###############################################################################
## Project
###############################################################################

get_target_property(CUBE_INCLUDE_DIRECTORIES stm32cubemx INTERFACE_INCLUDE_DIRECTORIES)
get_target_property(CUBE_SOURCES stm32cubemx INTERFACE_SOURCES)
get_target_property(CUBE_COMPILE_DEFINITIONS stm32cubemx INTERFACE_COMPILE_DEFINITIONS)

# Remove warnings from Cube sources
set_source_files_properties(
    ${CUBE_SOURCES}
    PROPERTIES
    COMPILE_FLAGS "-w"
)

add_library(${PROJECT_NAME}_lib STATIC
    ${PROJECT_SOURCES}
    ${LIB_SOURCES}
)

target_include_directories(${PROJECT_NAME}_lib PUBLIC
    inc
    ${LIB_INCLUDE_DIRECTORIES}
)

target_link_libraries(${PROJECT_NAME}_lib PRIVATE
    stm32cubemx
)

target_precompile_headers(${PROJECT_NAME}_lib PUBLIC
    ${FORCED_INCLUDE_HEADERS}
)

target_include_directories(${PROJECT_NAME}_lib SYSTEM PUBLIC
    ${CUBE_INCLUDE_DIRECTORIES}
)

target_compile_definitions(${PROJECT_NAME}_lib PUBLIC
    ${CUBE_COMPILE_DEFINITIONS}
)

add_library(${PROJECT_NAME} INTERFACE)
target_link_libraries(${PROJECT_NAME} INTERFACE
    "-Wl,--whole-archive" ${PROJECT_NAME}_lib "-Wl,--no-whole-archive"
)
###############################################################################
## Main executable target
###############################################################################

add_executable(${PROJECT_NAME}_main
    src/main.cpp
)

target_include_directories(${PROJECT_NAME}_main PUBLIC
    inc
    config
)

target_link_libraries(${PROJECT_NAME}_main PUBLIC
    ${PROJECT_NAME}
)

stm32_print_size_of_target(${PROJECT_NAME}_main)
stm32_generate_hex_file(${PROJECT_NAME}_main)

targets_generate_vsfiles_target(${PROJECT_NAME}_main)
targets_generate_flash_target(${PROJECT_NAME}_main)
targets_generate_helpme_target()

###############################################################################
## Generate test executables
###############################################################################

foreach(TEST_FILE ${PROJECT_TESTS_BIN})
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WLE)

    add_executable(${TEST_NAME} EXCLUDE_FROM_ALL
        ${TEST_FILE}
        ${PROJECT_TESTS_SOURCES}
    )

    target_include_directories(${TEST_NAME} PUBLIC
        tests/inc
        inc
        config
        ${LIB_INCLUDE_DIRECTORIES}
    )

    target_link_libraries(${TEST_NAME} PUBLIC
        ${PROJECT_NAME}
    )

    stm32_generate_hex_file(${TEST_NAME})

    targets_generate_vsfiles_target(${TEST_NAME})
    targets_generate_flash_target(${TEST_NAME})

endforeach()
