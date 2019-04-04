cmake_minimum_required(VERSION 3.0)

project(powerline)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Oz -Wall -fno-rtti -lgit2")

set (EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

message(${PROJECT_SOURCE_DIR})
message(${EXECUTABLE_OUTPUT_PATH})

include_directories( ${PROJECT_SOURCE_DIR}/src/ )
add_library(utils.o utils.cpp)
# add_executable(test main.cpp)

find_package(git2)

# add_library(utils.o utils.cpp)
# install(TARGETS powerline DESTINATION bin)


# message(${CMAKE_HOME_DIRECTORY})
# message(${CMAKE_BINARY_DIR})
# message(${CMAKE_SOURCE_DIR})
