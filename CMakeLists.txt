cmake_minimum_required(VERSION 2.6)

project(SuperMarket)


set (SuperMarket_VERSION_MAJOR 1)
set (SuperMarket_VERSION_MINOR 0)

if(NOT CMAKE_VERSION VERSION_LESS 3.1)
    set(CMAKE_CXX_STANDARD 14)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fprofile-arcs -ftest-coverage")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -fprofile-arcs -ftest-coverage")
endif()

add_subdirectory(src)
add_subdirectory(tests)

enable_testing()
