cmake_minimum_required(VERSION 3.0)

project(powerline)
file(GLOB_RECURSE sources  src/*.cpp src/segments/*.cpp)
add_executable(powerline ${sources})

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Oz -Wall -fno-rtti -lgit2")

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBGIT2 REQUIRED libgit2)

set (EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

include_directories( ${PROJECT_SOURCE_DIR}/src/ )

add_custom_command(TARGET powerline POST_BUILD
    COMMAND strip -SNTXx ${EXECUTABLE_OUTPUT_PATH}/powerline
    COMMENT "Stripping binary..."
)
