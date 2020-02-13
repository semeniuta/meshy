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
using VertexInfoComparator = std::function<bool(const VertexInfo&, const VertexInfo&)>;

std::vector<VertexInfo> gather_vertices(const std::vector<Facet>& facets) {

    std::vector<VertexInfo> vertices;

    int facet_index = 0;
    for (const auto& f : facets) {
        vertices.push_back({f.v1, facet_index});
        vertices.push_back({f.v2, facet_index});
        vertices.push_back({f.v3, facet_index});

        facet_index++;
    }

    return vertices;

}

VertexInfoComparator create_comparator_joint(double tol=1e-6) {
    return [tol](const VertexInfo& vi1, const VertexInfo& vi2) -> bool {

        const auto& v1 = vi1.v;
        const auto& v2 = vi2.v;

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
        std::cout << "Usage: spikemg model.stl\n";
        return -1;
    }

    auto fname = argv[1];
    std::vector<Facet> facets = read_stl(fname);

    auto all_vertices = gather_vertices(facets);
    std::sort(all_vertices.begin(), all_vertices.end(), create_comparator_joint());

    for (int i = 0; i < 100; i++) {
        const auto& v = all_vertices[i].v;
        int fid = all_vertices[i].facet_id;
        std::cout << v(0) << " " << v(1) << " " << v(2);
        std::cout << "(" << fid << ")" << std::endl;
    }

    return 0;
}