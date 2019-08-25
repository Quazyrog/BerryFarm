cmake_minimum_required(VERSION 3.0)

project(berryfarm)
SET(CMAKE_CXX_COMPILER "clang++")
SET(CMAKE_CXX_FLAGS "-std=c++17")

add_executable(berryfarm Main.cpp
    Model/Species.cpp)

install(TARGETS berryfarm RUNTIME DESTINATION bin)
