//
// Created by Oleksandr Semeniuta on 05/02/2020.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include "stl.h"
#include "shapedist.h"
#include "MeshGraph.h"

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

    auto distances = generate_d2_samples(facets, ca, 100);
    std::sort(distances.begin(), distances.end());

    std::cout << "Distances:\n";
    for (const auto& d : distances) {
        std::cout << d << " ";
    }
    std::cout << std::endl;

    Segment s1{0, 7};
    Segment s2{7, 0};
    Segment s3{4, 1};
    Segment s4{10, 12};

    std::cout << (s1 == s2) << std::endl;
    std::cout << (s1 == s3) << std::endl;

    std::map<Segment, std::vector<int>> m{};
    m[s1] = std::vector<int>{1, 2, 3};
    m[s3] = std::vector<int>{4, 5, 6};

    for (int num : m[s2]) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    IndexedMesh im{facets};

    return 0;
}