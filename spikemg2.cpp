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

    IndexedMesh im{facets};

    std::vector<Segment> sa = detect_segment_anomalies(im);

    std::vector<Facet> f_out;

    for (auto& segment : sa) {
        std::vector<int> facet_indices = im.segments_adjacency_[segment];

        std::cout << segment.p2() << "-" << segment.p1() << " " << facet_indices.size() << ": ";
        for (int f_idx : facet_indices) {

            f_out.push_back(facets[f_idx]);

            std::cout << f_idx << "(";
            std::cout << im.facets_[f_idx].vertices[0] << ", ";
            std::cout << im.facets_[f_idx].vertices[1] << ", ";
            std::cout << im.facets_[f_idx].vertices[2] << ") ";
        }
        std::cout << "\n";
    }

    write_stl(f_out, "anomalies.stl", "Made by Oleksandr");

    return 0;
}