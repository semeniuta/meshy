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

std::vector<std::vector<VectorXd>> generate_random_points(
        const std::vector<Facet>& facets,
        const std::vector<double>& ca,
        unsigned int n,
        unsigned int n_points_per_iter,
        int random_state) {

    std::random_device rd{};
    std::default_random_engine generator{rd()};

    if (random_state != -1) {
        generator.seed(random_state);
    }

    double total_area = ca[ca.size() - 1];
    std::uniform_real_distribution<double> distrib_areas{0., total_area};
    std::uniform_real_distribution<double> distrib_r1{0., 1.};
    std::uniform_real_distribution<double> distrib_r2{0., 1.};

    std::vector<std::vector<VectorXd>> sampled_points(n);

    for (int i = 0; i < n; i++) {

        sampled_points[i].reserve(n_points_per_iter);

        for (int j = 0; j < n_points_per_iter; j++) {

            double random_area = distrib_areas(generator);

            double r1 = distrib_r1(generator);
            double r2 = distrib_r2(generator);

            auto closest_idx = search_closest(ca, random_area);
            auto facet = facets[closest_idx];

            auto p = point_on_surface_of_triangle(facet, r1, r2);

            sampled_points[i].push_back(p);
        }

    }

    return sampled_points;

}

std::vector<double> generate_d2_samples(
        const std::vector<Facet>& facets,
        const std::vector<double>& ca,
        unsigned int n,
        int random_state) {

    auto sampled_points = generate_random_points(facets, ca, n, 2, random_state);

    std::vector<double> distances(n);

    for (int i = 0; i < n; i++) {

        auto p1 = sampled_points[i][0];
        auto p2 = sampled_points[i][1];

        double dist = euclidean_distance(p1, p2);
        distances[i] = dist;

    }

    return distances;

}

std::vector<double> read_stl_and_generate_d2_samples(const std::string& fname, int n_samples, int random_state) {

    std::vector<Facet> facets = read_stl(fname);
    return generate_d2_samples_for_facets(facets, n_samples, random_state);

}

std::vector<double> generate_d2_samples_for_facets(const std::vector<Facet>& facets, int n_samples, int random_state) {

    std::vector<double> areas(facets.size());
    std::transform(facets.begin(), facets.end(), areas.begin(), &triangle_area);
    std::vector<double> ca = cummulative_area(areas);

    return generate_d2_samples(facets, ca, n_samples, random_state);

}

std::vector<std::vector<VectorXd>> generate_random_points_for_facets(const std::vector<Facet>& facets, int n_samples, int n_points, int random_state) {

    std::vector<double> areas(facets.size());
    std::transform(facets.begin(), facets.end(), areas.begin(), &triangle_area);
    std::vector<double> ca = cummulative_area(areas);

    return generate_random_points(facets, ca, n_samples, n_points, random_state);

}
