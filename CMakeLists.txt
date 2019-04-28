set(CMAKE_CXX_COMPILER "g++-8")
cmake_minimum_required(VERSION 3.0)

project(powerline)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Wnon-virtual-dtor -Wpedantic")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast")
# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Os")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -flto")
# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")
# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lprofiler")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lstdc++fs")


set (EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)


include_directories( ${PROJECT_SOURCE_DIR}/src/ )
# include_directories( ${PROJECT_SOURCE_DIR}/lib/ )
include_directories( ${PROJECT_SOURCE_DIR}/lib/libgit2/include )
include_directories( ${PROJECT_SOURCE_DIR}/lib/cpptoml/include )


file(GLOB_RECURSE sources src/*.cpp)

add_executable(powerline ${sources})
target_link_libraries(powerline ${PROJECT_SOURCE_DIR}/lib/libgit2.a)


add_custom_command(TARGET powerline POST_BUILD
    COMMAND strip -SNTXx ${EXECUTABLE_OUTPUT_PATH}/powerline
    COMMENT "Stripping binary..."
)
