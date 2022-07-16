cmake_minimum_required(VERSION 3.1)

project(meshy)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(pybind11)

include_directories("eigen-3.3.7")

file(GLOB SOURCES "src/*.cpp")
include_directories("src")

add_executable(scaler "scaler.cpp" ${SOURCES})

add_executable(rotate "rotate.cpp" ${SOURCES})

add_executable(stats "apps/stats.cpp" ${SOURCES})

pybind11_add_module(pymeshy python_extension.cpp ${SOURCES})

add_executable(spike "spikes/spike.cpp" ${SOURCES})
add_executable(spikemg "spikes/spikemg.cpp" ${SOURCES})
add_executable(spikemg2 "spikes/spikemg2.cpp" ${SOURCES})
add_executable(spikemg3 "spikes/spikemg3.cpp" ${SOURCES})
add_executable(spikernd "spikes/spikernd.cpp" ${SOURCES})
