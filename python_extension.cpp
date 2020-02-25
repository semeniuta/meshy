//
// Created by Oleksandr Semeniuta on 06/02/2020.
//

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/eigen.h>

#include "stl.h"
#include "shapedist.h"

namespace py = pybind11;

PYBIND11_MODULE(pymeshy, m)
{
    m.def("read_stl_and_generate_d2_samples", &read_stl_and_generate_d2_samples,
          py::arg("fname"),
          py::arg("n_samples"),
          py::arg("random_state") = -1);

    m.def("generate_d2_samples_for_facets", &generate_d2_samples_for_facets,
          py::arg("facets"),
          py::arg("n_samples"),
          py::arg("random_state") = -1);

    m.def("read_stl", read_stl);

    m.def("transform_facets", transform_facets);

    py::class_<Facet>(m, "Facet")
            .def_readonly("normal", &Facet::normal)
            .def_readonly("v1", &Facet::v1)
            .def_readonly("v2", &Facet::v2)
            .def_readonly("v3", &Facet::v3);

}