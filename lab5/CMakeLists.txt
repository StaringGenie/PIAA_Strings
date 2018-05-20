cmake_minimum_required(VERSION 2.8.12.2)

project(Lab5_KMP)

add_library(KMPfunc src/KMPfunc.cpp)

target_include_directories(KMPfunc PUBLIC ./hdr)

set(CMAKE_CXX_FLAGS "-Wall -std=c++11")

add_executable (SubstrSrch src/SubstrSrch.cpp)
add_executable (CycleShiftSrch src/CycleShiftSrch.cpp)
add_executable (CheckOperations src/CheckOperations.cpp)

target_link_libraries(CheckOperations KMPfunc)
target_link_libraries(SubstrSrch KMPfunc)
target_link_libraries(CycleShiftSrch KMPfunc)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(ShiftTest test/ShiftTest.cpp)
target_link_libraries(ShiftTest KMPfunc)
target_link_libraries(ShiftTest ${GTEST_LIBRARIES} pthread)

add_executable(SubstrSrchTest test/SubstrSrchTest.cpp)
target_link_libraries(SubstrSrchTest KMPfunc)
target_link_libraries(SubstrSrchTest ${GTEST_LIBRARIES} pthread)

