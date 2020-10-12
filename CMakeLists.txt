cmake_minimum_required(VERSION 3.0.0)
project(QuadTree VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(QuadTree main.cpp Node.cpp QuadTree.cpp Square.cpp Point.cpp Rectangle.cpp twoVects.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
