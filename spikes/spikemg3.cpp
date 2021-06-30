/**
 * Read an STL file, construct a MeshGraph from it,
 * and demonstrate using breadth-first search (BFS)
 * to select an area around the facet of interest.
 */

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

    auto neighbors = search.facets_around(30);
    std::vector<Facet> facets_around;
    facets_around.reserve(neighbors.size());
    for (int i : neighbors) {
        facets_around.push_back(facets[i]);
    }

    //write_stl(facets_around, "facets_around.stl", "Made by Oleksandr");

    return 0;
}