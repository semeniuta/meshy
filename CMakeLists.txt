cmake_minimum_required(VERSION 3.1)

project(meshy)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(pybind11)

find_package(Eigen3 3.3 REQUIRED NO_MODULE)

file(GLOB SOURCES "src/*.cpp")
include_directories("src")

add_executable(spike "spike.cpp" ${SOURCES})
target_link_libraries(spike Eigen3::Eigen)

add_executable(scaler "scaler.cpp" ${SOURCES})
target_link_libraries(scaler Eigen3::Eigen)

add_executable(spikemg "spikemg.cpp" ${SOURCES})
target_link_libraries(spikemg Eigen3::Eigen)

add_executable(spikernd "spikernd.cpp" ${SOURCES})
target_link_libraries(spikernd Eigen3::Eigen)

pybind11_add_module(pymeshy python_extension.cpp ${SOURCES})
target_link_libraries(pymeshy PRIVATE Eigen3::Eigen)
