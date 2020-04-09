//
// Created by Oleksandr Semeniuta on 05/02/2020.
//

#ifndef MESHY_SHAPEDIST_H
#define MESHY_SHAPEDIST_H

#include <random>
#include <algorithm>
#include "stl.h"
#include "geometry.h"

struct ThreePointsMeasurements {
    std::vector<double> area;
    std::vector<double> theta_1;
    std::vector<double> theta_2;
    std::vector<double> theta_3;
    std::vector<double> d1;
    std::vector<double> d2;
    std::vector<double> d3;
};

std::vector<double> cummulative_area(const std::vector<double>& areas);

long search_closest(const std::vector<double>& sorted_array, double val);

VectorXd point_on_surface_of_triangle(const Facet& facet, double r1, double r2);

std::vector<std::vector<VectorXd>> generate_random_points(
        const std::vector<Facet>& facets,
        const std::vector<double>& ca,
        unsigned int n,
        unsigned int n_points_per_iter,
        int random_state=-1);

std::vector<double> generate_d2_samples(
        const std::vector<Facet>& facets,
        const std::vector<double>& ca,
        unsigned int n,
        int random_state=-1);

ThreePointsMeasurements generate_three_points_samples(
        const std::vector<Facet>& facets,
        const std::vector<double>& ca,
        unsigned int n,
        int random_state=-1);

std::vector<double> read_stl_and_generate_d2_samples(const std::string& fname, int n_samples, int random_state=-1);

std::vector<double> generate_d2_samples_for_facets(const std::vector<Facet>& facets, int n_samples, int random_state=-1);

std::vector<std::vector<VectorXd>> generate_random_points_for_facets(const std::vector<Facet>& facets, int n_samples, int n_points, int random_state=-1);

ThreePointsMeasurements generate_three_points_samples_for_facets(const std::vector<Facet>& facets, int n_samples, int random_state=-1);

#endif //MESHY_SHAPEDIST_H
