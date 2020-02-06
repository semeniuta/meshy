//
// Created by Oleksandr Semeniuta on 05/02/2020.
//

#include "shapedist.h"

double euclidean_distance(const VectorXd& v1, const VectorXd& v2) {

    auto diff = v1 - v2;
    return diff.norm();

}

double triangle_area(const Facet& facet) {

    auto d1 = euclidean_distance(facet.v1, facet.v2);
    auto d2 = euclidean_distance(facet.v2, facet.v3);
    auto d3 = euclidean_distance(facet.v3, facet.v1);

    auto s = 0.5 * (d1 + d2 + d3);

    auto area = sqrt(s * (s - d1) * (s - d2) * (s - d3));

    return area;

}

std::vector<double> cummulative_area(const std::vector<Facet>& facets) {

    double area_so_far = 0.;
    std::vector<double> arr;

    for (const auto& facet : facets) {

        double a = triangle_area(facet);
        area_so_far += a;
        arr.push_back(area_so_far);

    }

    return arr;

}

long search_closest(const std::vector<double>& sorted_array, double val) {

    auto iter_geq = std::lower_bound(sorted_array.begin(), sorted_array.end(), val);

    double a = *(iter_geq - 1);
    double b = *(iter_geq);

    if (fabs(val - a) < fabs(val - b)) {
        return iter_geq - sorted_array.begin() - 1;
    }

    return iter_geq - sorted_array.begin();

}
