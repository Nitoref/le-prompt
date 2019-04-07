cmake_minimum_required(VERSION 3.0)

project(powerline)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Oz -Wall -Wextra -fno-rtti -lgit2")
set (EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
include_directories( ${PROJECT_SOURCE_DIR}/src/ )

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBGIT2 REQUIRED libgit2)

find_package(nlohmann_json CONFIG QUIET)
if(NOT nlohmann_json_FOUND)
    find_path(NLOHMANN_INCLUDE_DIR nlohmann/json.hpp)
    add_library(nlohmann_json INTERFACE IMPORTED)
    set_target_properties(nlohmann_json PROPERTIES
    	INTERFACE_INCLUDE_DIRECTORIES ${NLOHMANN_INCLUDE_DIR}
    )
endif()

file(GLOB_RECURSE sources  src/*.cpp src/segments/*.cpp)
add_executable(powerline ${sources})

add_custom_command(TARGET powerline POST_BUILD
    COMMAND strip -SNTXx ${EXECUTABLE_OUTPUT_PATH}/powerline
    COMMENT "Stripping binary..."
)
