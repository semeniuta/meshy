//
// Created by Oleksandr Semeniuta on 09/04/2020.
//

#include "geometry.h"

double euclidean_distance(const VectorXd& v1, const VectorXd& v2) {

    auto diff = v1 - v2;
    return diff.norm();

}

double triangle_area(const Facet& facet) {

    std::array<double, 3> d = triangle_sides_distances(facet);

    auto s = 0.5 * (d[0] + d[1] + d[2]);

    auto area = sqrt(s * (s - d[0]) * (s - d[1]) * (s - d[2]));

    return area;
}

std::array<double, 3> triangle_sides_distances(const Facet& facet) {

    std::array<double, 3> distances{
            euclidean_distance(facet.v1, facet.v2),
            euclidean_distance(facet.v2, facet.v3),
            euclidean_distance(facet.v3, facet.v1)
    };

    return distances;
}

