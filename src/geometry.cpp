//
// Created by Oleksandr Semeniuta on 09/04/2020.
//

#include "geometry.h"

double euclidean_distance(const VectorXd& v1, const VectorXd& v2) {

    auto diff = v1 - v2;
    return diff.norm();

}

double triangle_area(const VectorXd& v1, const VectorXd& v2, const VectorXd& v3) {

    std::array<double, 3> d = triangle_sides_distances(v1, v2, v3);

    auto s = 0.5 * (d[0] + d[1] + d[2]);

    auto area = sqrt(s * (s - d[0]) * (s - d[1]) * (s - d[2]));

    return area;
}

double facet_area(const Facet& facet) {

    return triangle_area(facet.v1, facet.v2, facet.v3);

}

std::array<double, 3> triangle_sides_distances(const VectorXd& v1, const VectorXd& v2, const VectorXd& v3) {

    std::array<double, 3> distances{
            euclidean_distance(v1, v2),
            euclidean_distance(v2, v3),
            euclidean_distance(v3, v1)
    };

    return distances;
}

double angle_cos_between_two_vectors(const VectorXd& v1, const VectorXd& v2) {

    return v1.dot(v2) / (v1.norm() * v2.norm());

}

std::array<double, 3> triangle_angles_cos(const std::vector<VectorXd>& points) {

    struct other_indices {
        int j1;
        int j2;
    };

    std::array<double, 3> res{};

    for (int i = 0; i < 3; i++) {

        other_indices other{};

        switch (i) {
            case 0:
                other = {1, 2};
                break;
            case 1:
                other = {0, 2};
                break;
            case 2:
                other = {0, 1};
                break;
            default:
                break;
        }

        VectorXd v1 = points[other.j1] - points[i];
        VectorXd v2 = points[other.j2] - points[i];

        res[i] = angle_cos_between_two_vectors(v1, v2);

    }

    return res;

}

