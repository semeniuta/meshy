//
// Created by Oleksandr Semeniuta on 11/03/2020.
//

#include <iostream>
#include <vector>
#include "stl.h"
#include "MeshGraph.h"
#include "BreadthFirstSearch.h"

using Eigen::VectorXd;

int main(int argc, char **argv) {

    if (argc < 2) {
        std::cout << "Usage: spikemg3 model.stl\n";
        return -1;
    }

    auto fname = argv[1];
    std::vector<Facet> facets = read_stl(fname);

    IndexedMesh im{facets};

    std::cout << "Number of facets: " << im.facets_.size() << "\n";
    std::cout << "Number of vertices: " << im.vertices_.size() << "\n";
    std::cout << "Number of segments: " << im.segments_adjacency_.size() << "\n";

    MeshGraph mg = build_mesh_graph(im);

    BreadthFirstSearch search{mg};

    search.bfs(0);

    return 0;
}