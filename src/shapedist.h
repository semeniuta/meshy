//
// Created by Oleksandr Semeniuta on 05/02/2020.
//

#ifndef MESHY_SHAPEDIST_H
#define MESHY_SHAPEDIST_H

#include <random>
#include "stl.h"

double euclidean_distance(const VectorXd& v1, const VectorXd& v2);

double triangle_area(const Facet& facet);

std::vector<double> cummulative_area(const std::vector<double>& areas);

long search_closest(const std::vector<double>& sorted_array, double val);

VectorXd point_on_surface_of_triangle(const Facet& facet, double r1, double r2);

std::vector<double> generate_d2_samples(
        const std::vector<Facet>& facets,
        const std::vector<double>& ca,
        unsigned int n);

#endif //MESHY_SHAPEDIST_H
