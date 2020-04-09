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

    m.def("generate_random_points_for_facets", &generate_random_points_for_facets,
          py::arg("facets"),
          py::arg("n_samples"),
          py::arg("n_points"),
          py::arg("random_state") = -1);

    m.def("generate_three_points_samples_for_facets", &generate_three_points_samples_for_facets,
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

    py::class_<ThreePointsMeasurements>(m, "ThreePointsMeasurements")
            .def_readonly("area", &ThreePointsMeasurements::area)
            .def_readonly("theta_1", &ThreePointsMeasurements::theta_1)
            .def_readonly("theta_2", &ThreePointsMeasurements::theta_2)
            .def_readonly("theta_3", &ThreePointsMeasurements::theta_3)
            .def_readonly("d1", &ThreePointsMeasurements::d1)
            .def_readonly("d2", &ThreePointsMeasurements::d2)
            .def_readonly("d3", &ThreePointsMeasurements::d3);

}