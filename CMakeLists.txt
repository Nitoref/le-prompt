set(CMAKE_CXX_COMPILER "/usr/local/bin/g++-8")
# set(CMAKE_CXX_COMPILER "clang++")
cmake_minimum_required(VERSION 3.0)

project(powerline)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Wnon-virtual-dtor -Wpedantic")
# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Oz")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti -flto")
# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lgit2")
# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lc++fs")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lstdc++fs")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L /usr/local/Cellar/llvm/8.0.0/lib/")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I /Users/nitoref/Downloads/libgit2-0.28.1/include")



set (EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
include_directories( ${PROJECT_SOURCE_DIR}/src/ )

find_package(nlohmann_json CONFIG QUIET)
if(NOT nlohmann_json_FOUND)
    find_path(NLOHMANN_INCLUDE_DIR nlohmann/json.hpp)
    add_library(nlohmann_json INTERFACE IMPORTED)
    set_target_properties(nlohmann_json PROPERTIES
    	INTERFACE_INCLUDE_DIRECTORIES ${NLOHMANN_INCLUDE_DIR}
    )
endif()

file(GLOB_RECURSE sources src/*.cpp src/segments/*.cpp)
add_executable(powerline ${sources})
target_link_libraries(powerline ${PROJECT_SOURCE_DIR}/lib/libgit2.a)


add_custom_command(TARGET powerline POST_BUILD
    COMMAND strip -SNTXx ${EXECUTABLE_OUTPUT_PATH}/powerline
    COMMENT "Stripping binary..."
)
