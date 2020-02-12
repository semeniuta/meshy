//
// Created by Oleksandr Semeniuta on 12/02/2020.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <functional>
#include "stl.h"
#include "shapedist.h"
#include "MeshGraph.h"

using Eigen::VectorXd;
using EigenComparator = std::function<bool(const VectorXd&, const VectorXd&)>;

std::vector<VectorXd> gather_vertices(const std::vector<Facet>& facets) {

    std::vector<VectorXd> vertices;

    for (const auto& f : facets) {
        vertices.push_back(f.v1);
        vertices.push_back(f.v2);
        vertices.push_back(f.v3);
    }

    return vertices;

}

EigenComparator create_comparator(unsigned int index) {
    return [index](const VectorXd& v1, const VectorXd& v2) -> bool {
        return v1(index) < v2(index);
    };
}

EigenComparator create_comparator_joint(double tol=1e-6) {
    return [tol](const VectorXd& v1, const VectorXd& v2) -> bool {

        if (fabs(v1(0) - v2(0)) > tol) {
            return v1(0) < v2(0);
        }

        if (fabs(v1(1) - v2(1)) > tol) {
            return v1(1) < v2(1);
        }

        return v1(2) < v2(2);

    };
}

int main(int argc, char **argv) {

    if (argc < 2) {
        std::cout << "Usage: spike model.stl\n";
        return -1;
    }

    auto fname = argv[1];
    std::vector<Facet> facets = read_stl(fname);

    auto all_vertices = gather_vertices(facets);
    std::sort(all_vertices.begin(), all_vertices.end(), create_comparator_joint());

    for (int i = 0; i < 100; i++) {
        const auto& v = all_vertices[i];
        std::cout << v(0) << " " << v(1) << " " << v(2) << std::endl;
    }

    return 0;
}