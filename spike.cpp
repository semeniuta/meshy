//
// Created by Oleksandr Semeniuta on 05/02/2020.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include "stl.h"
#include "shapedist.h"

using Eigen::VectorXd;

int main(int argc, char **argv) {

    if (argc < 2) {
        std::cout << "Usage: spike model.stl\n";
        return -1;
    }

    auto fname = argv[1];
    std::vector<Facet> facets = read_stl(fname);

    std::cout << facets.size() << std::endl;

    std::cout << facets[0].normal << std::endl;

    std::vector<double> areas(facets.size());
    std::transform(facets.begin(), facets.end(), areas.begin(), &triangle_area);
    std::vector<double> ca = cummulative_area(areas);

    auto idx_closest = search_closest(ca, 20.);
    std::cout << "Closest: " << ca[idx_closest] << std::endl;

    auto res = std::lower_bound(ca.begin(), ca.end(), 20.);

    std::cout << *(res - 1) << ", " << *res << ", " << *(res + 1) << std::endl;

    return 0;
}