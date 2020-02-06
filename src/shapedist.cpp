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

std::vector<double> cummulative_area(const std::vector<double>& areas) {

    double area_so_far = 0.;
    std::vector<double> ca;

    for (const auto& a : areas) {

        area_so_far += a;
        ca.push_back(area_so_far);

    }

    return ca;

}

long search_closest(const std::vector<double>& sorted_array, double val) {

    auto iter_geq = std::lower_bound(sorted_array.begin(), sorted_array.end(), val);

    if (iter_geq == sorted_array.begin()) {
        return 0;
    }

    double a = *(iter_geq - 1);
    double b = *(iter_geq);

    if (fabs(val - a) < fabs(val - b)) {
        return iter_geq - sorted_array.begin() - 1;
    }

    return iter_geq - sorted_array.begin();

}

VectorXd point_on_surface_of_triangle(const Facet& facet, double r1, double r2) {

    double sqrt_r1 = sqrt(r1);

    double a = 1. - sqrt_r1;
    double b = sqrt_r1 * (1. - r2);
    double c = sqrt_r1 * r2;

    return a * facet.v1 + b * facet.v2 + c * facet.v3;

}

std::vector<double> generate_d2_samples(
        const std::vector<Facet>& facets,
        const std::vector<double>& ca,
        unsigned int n) {

    std::random_device rd{};
    std::default_random_engine generator{rd()};

    double total_area = ca[ca.size() - 1];
    std::uniform_real_distribution<double> distrib_areas{0., total_area};
    std::uniform_real_distribution<double> distrib_r1{0., 1.};
    std::uniform_real_distribution<double> distrib_r2{0., 1.};

    std::vector<double> distances(n);

    for (int i = 0; i < n; i++) {

        double random_area_1 = distrib_areas(generator);
        double random_area_2 = distrib_areas(generator);

        double r1_1 = distrib_r1(generator);
        double r2_1 = distrib_r2(generator);

        double r1_2 = distrib_r1(generator);
        double r2_2 = distrib_r2(generator);

        auto closest_idx_1 = search_closest(ca, random_area_1);
        auto facet_1 = facets[closest_idx_1];

        auto closest_idx_2 = search_closest(ca, random_area_2);
        auto facet_2 = facets[closest_idx_2];

        auto p1 = point_on_surface_of_triangle(facet_1, r1_1, r2_1);
        auto p2 = point_on_surface_of_triangle(facet_2, r1_2, r2_2);

        double dist = euclidean_distance(p1, p2);
        distances[i] = dist;

    }

    return distances;

}
