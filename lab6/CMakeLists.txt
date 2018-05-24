cmake_minimum_required(VERSION 2.8.12.2)

project(Lab5_KMP)

add_library(BohrTree src/BohrTree.cpp)

target_include_directories(BohrTree PUBLIC ./hdr)

set(CMAKE_CXX_FLAGS "-Wall -std=c++11")

add_executable (AKSearch src/AKSearch.cpp)
add_executable (AKJokerSearch src/AKJokerSearch.cpp)

target_link_libraries(AKSearch BohrTree)
target_link_libraries(AKJokerSearch BohrTree)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(AKSearchTest test/AKSearchTest.cpp)
target_link_libraries(AKSearchTest BohrTree)
target_link_libraries(AKSearchTest ${GTEST_LIBRARIES} pthread)

add_executable(AKJokerSearchTest test/AKJokerSearchTest.cpp)
target_link_libraries(AKJokerSearchTest BohrTree)
target_link_libraries(AKJokerSearchTest ${GTEST_LIBRARIES} pthread)

