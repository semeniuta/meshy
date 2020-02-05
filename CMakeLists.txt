cmake_minimum_required(VERSION 3.1)

project(meshy)

set(CMAKE_CXX_STANDARD 14)

file(GLOB SOURCES "src/*.cpp")
include_directories("src")

add_executable(mystl "mystl.cpp" ${SOURCES})
