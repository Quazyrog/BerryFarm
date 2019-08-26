cmake_minimum_required(VERSION 3.0)

project(berryfarm)
SET(CMAKE_CXX_COMPILER "clang++")
SET(CMAKE_CXX_FLAGS "-std=c++17")
SET(COMMON_SOURCE_FILES
        Model/Species.cpp
        Model/World.cpp
        Model/Buildings.cpp)

add_executable(berryfarm Main.cpp ${COMMON_SOURCE_FILES})

add_executable(test TestMain.cpp ${COMMON_SOURCE_FILES})
find_package(GTest REQUIRED)
target_include_directories(test PUBLIC ${GTEST_INCLUDE_DIRS})
target_link_libraries(test "${GTEST_BOTH_LIBRARIES}")

install(TARGETS berryfarm RUNTIME DESTINATION bin)
