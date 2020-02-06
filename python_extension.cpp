//
// Created by Oleksandr Semeniuta on 06/02/2020.
//

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "stl.h"
#include "shapedist.h"

namespace py = pybind11;

PYBIND11_MODULE(pymeshy, m)
{
    m.def("read_stl_and_generate_d2_samples", read_stl_and_generate_d2_samples);
}