set(CMAKE_CXX_COMPILER "g++-8")
cmake_minimum_required(VERSION 3.0)

project(le-prompt)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Wnon-virtual-dtor -Wpedantic")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast -flto")
# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lstdc++fs")

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

include_directories( ${PROJECT_SOURCE_DIR}/src/ )
include_directories( ${PROJECT_SOURCE_DIR}/lib/libgit2/include )
include_directories( ${PROJECT_SOURCE_DIR}/lib/cpptoml/include )

file(GLOB_RECURSE sources src/*.cpp)

add_executable(le-prompt ${sources})
target_link_libraries(le-prompt ${PROJECT_SOURCE_DIR}/lib/libgit2/build/libgit2.a)

add_custom_command(TARGET le-prompt POST_BUILD
    COMMAND strip -SNTXx ${EXECUTABLE_OUTPUT_PATH}/le-prompt
    COMMENT "Stripping binary..."
)
