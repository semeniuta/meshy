//
// Created by Oleksandr Semeniuta on 09/04/2020.
//

#ifndef MESHY_GEOMETRY_H
#define MESHY_GEOMETRY_H

#include "stl.h"
#include <array>
#include <cmath>

double euclidean_distance(const VectorXd& v1, const VectorXd& v2);

double triangle_area(const VectorXd& v1, const VectorXd& v2, const VectorXd& v3);

double facet_area(const Facet& facet);

std::array<double, 3> triangle_sides_distances(const VectorXd& v1, const VectorXd& v2, const VectorXd& v3);

double angle_cos_between_two_vectors(const VectorXd& v1, const VectorXd& v2);

std::array<double, 3> triangle_angles_cos(const std::vector<VectorXd>& points);

MatrixXd rotation_matrix_x(double angle);

MatrixXd rotation_matrix_y(double angle);

MatrixXd rotation_matrix_z(double angle);

#endif //MESHY_GEOMETRY_H
