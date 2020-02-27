//
// Created by Oleksandr Semeniuta on 27/02/2020.
//

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include "stl.h"
#include "MeshGraph.h"

using Eigen::VectorXd;

int main(int argc, char **argv) {

    if (argc < 2) {
        std::cout << "Usage: spikemg2 model.stl\n";
        return -1;
    }

    auto fname = argv[1];
    std::vector<Facet> facets = read_stl(fname);

    MeshGraph mg{facets};

    std::vector<Segment> sa = mg.detect_segment_anomalies();

    for (auto& segment : sa) {
        std::vector<int> facet_indices = mg.get_facets_containing_segment(segment);

        std::cout << segment.p2() << "-" << segment.p1() << " " << facet_indices.size() << ": ";
        for (int f_idx : facet_indices) {
            std::cout << f_idx << "(";
            std::cout << mg.get_facet_vertex(f_idx, 0) << ", ";
            std::cout << mg.get_facet_vertex(f_idx, 1)<< ", ";
            std::cout << mg.get_facet_vertex(f_idx, 2) << ") ";
        }
        std::cout << "\n";
    }

    return 0;
}