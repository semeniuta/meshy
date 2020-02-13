//
// Created by Oleksandr Semeniuta on 12/02/2020.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include "stl.h"
#include "MeshGraph.h"

using Eigen::VectorXd;


int main(int argc, char **argv) {

    if (argc < 2) {
        std::cout << "Usage: spikemg model.stl\n";
        return -1;
    }

    auto fname = argv[1];
    std::vector<Facet> facets = read_stl(fname);

    auto all_vertices = gather_vertices(facets);
    std::sort(all_vertices.begin(), all_vertices.end(), create_comparator_joint());

    std::cout << "\nSorted vertices:\n"<< std::endl;
    for (int i = 0; i < 20; i++) {
        const auto& v = all_vertices[i].v;
        int fid = all_vertices[i].facet.facet_id;
        std::cout << v(0) << " " << v(1) << " " << v(2);
        std::cout << "(" << fid << ")" << std::endl;
    }

    auto vaggr = aggregate_vertices(all_vertices);

    std::cout << "\nAggregated vertices:\n"<< std::endl;
    for (int i = 0; i < 20; i++) {
        const auto& v = vaggr[i].v;
        std::cout << v(0) << " " << v(1) << " " << v(2);

        std::cout << " (";
        for (const auto& f : vaggr[i].facets) {
            std::cout << f.facet_id << "[" << f.vertex_id_within_facet << "] ";
        }
        std::cout << ")"<< std::endl;

    }

    std::vector<IndexedFacet> indexed_facets = gather_indexed_facets(vaggr, facets);

    return 0;
}