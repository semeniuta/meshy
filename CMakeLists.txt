cmake_minimum_required(VERSION 3.1)

project(meshy)

set(CMAKE_CXX_STANDARD 14)

find_package(Eigen3 3.3 REQUIRED NO_MODULE)

file(GLOB SOURCES "src/*.cpp")
include_directories("src")

add_executable(spike "spike.cpp" ${SOURCES})
target_link_libraries(spike Eigen3::Eigen)
