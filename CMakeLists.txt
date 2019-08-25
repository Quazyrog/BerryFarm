cmake_minimum_required(VERSION 3.0)

project(berryfarm)

add_executable(berryfarm main.cpp)

install(TARGETS berryfarm RUNTIME DESTINATION bin)
