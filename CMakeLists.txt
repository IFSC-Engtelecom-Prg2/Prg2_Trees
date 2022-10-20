cmake_minimum_required(VERSION 3.14)
project(Prg2_Trees)

set(CMAKE_CXX_STANDARD 17)
include_directories(.)

add_executable(Prg2_demo main.cpp prglib.h libs/nodo_arvore.h libs/nodo_arvore-impl.h)
target_link_libraries(Prg2_demo -L${CMAKE_SOURCE_DIR}/libs prglib)

add_subdirectory(googletest)
include_directories(googletest/include googletest .)
add_executable(runTest test.cpp prglib.h)
target_link_libraries(runTest gtest gtest_main)