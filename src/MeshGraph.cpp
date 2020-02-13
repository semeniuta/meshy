//
// Created by Oleksandr Semeniuta on 07/02/2020.
//

#include "MeshGraph.h"

MeshGraph::MeshGraph(const std::vector<Facet>& facets) {

    for (int facet_idx = 0; facet_idx < facets.size(); facet_idx++) {

        auto f = facets[facet_idx];

        vertices_.push_back(f.v1);
        int idx_v1 = (int)vertices_.size() - 1;

        vertices_.push_back(f.v2);
        int idx_v2 = (int)vertices_.size() - 1;

        vertices_.push_back(f.v3);
        int idx_v3 = (int)vertices_.size() - 1;

        Segment s1{idx_v1, idx_v2};
        Segment s2{idx_v2, idx_v3};
        Segment s3{idx_v3, idx_v1};

        segments_[s1].push_back(facet_idx);
        segments_[s2].push_back(facet_idx);
        segments_[s3].push_back(facet_idx);

        IndexedFacet f_indexed{
            f.normal,
            idx_v1,
            idx_v2,
            idx_v3,
            s1,
            s2,
            s3
        };

        facets_.push_back(f_indexed);

    }

}

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

VertexInfoComparator create_comparator_joint(double tol) {
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

std::vector<VertexAggregated> aggregate_vertices(const std::vector<VertexInfo>& sorted_vertices, double tol) {

    std::vector<VertexAggregated> res;

    int current_i = 0;
    std::vector<int> facet_ids;
    facet_ids.push_back(sorted_vertices[current_i].facet_id);

    for (int i = 1; i < sorted_vertices.size(); i++) {

        const auto& current_vertex = sorted_vertices[current_i];
        const auto& next_vertex = sorted_vertices[i];

        double d = (current_vertex.v - next_vertex.v).norm();
        if (d <= tol) {
            facet_ids.push_back(next_vertex.facet_id);
            continue;
        }

        res.push_back({current_vertex.v, std::move(facet_ids)});

        current_i = i;
        facet_ids = std::vector<int>();
        facet_ids.push_back(sorted_vertices[current_i].facet_id);

    }

    return res;

}

