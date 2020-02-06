//
// Created by Oleksandr Semeniuta on 05/02/2020.
//

#ifndef MESHY_SHAPEDIST_H
#define MESHY_SHAPEDIST_H

#include "stl.h"

double euclidean_distance(const VectorXd& v1, const VectorXd& v2);

double triangle_area(const Facet& facet);

std::vector<double> cummulative_area(const std::vector<Facet>& facets);

long search_closest(const std::vector<double>& sorted_array, double val);

#endif //MESHY_SHAPEDIST_H