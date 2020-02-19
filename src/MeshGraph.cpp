//
// Created by Oleksandr Semeniuta on 07/02/2020.
//

#include "MeshGraph.h"
#include <iostream>

MeshGraph::MeshGraph(const std::vector<Facet>& facets) {

    auto vertices_all = gather_vertices(facets);
    std::sort(vertices_all.begin(), vertices_all.end(), create_comparator_joint());

    vertices_ = aggregate_vertices(vertices_all);

    VectorXd sum = VectorXd::Zero(3);
    for (const auto& va : vertices_) {
        sum += va.v;
    }
    centroid_ = sum / vertices_.size();
    std::cout << centroid_ << std::endl;

    facets_ = gather_indexed_facets(vertices_, facets);

    for (int facet_idx = 0; facet_idx < facets.size(); facet_idx++) {

        const auto& s1 = facets_[facet_idx].segments[0];
        const auto& s2 = facets_[facet_idx].segments[1];
        const auto& s3 = facets_[facet_idx].segments[2];

        segments_[s1].push_back(facet_idx);
        segments_[s2].push_back(facet_idx);
        segments_[s3].push_back(facet_idx);

    }

}

std::vector<VertexInfo> gather_vertices(const std::vector<Facet>& facets) {

    std::vector<VertexInfo> vertices;

    int facet_index = 0;
    for (const auto& f : facets) {
        vertices.push_back({f.v1, facet_index, 0});
        vertices.push_back({f.v2, facet_index, 1});
        vertices.push_back({f.v3, facet_index, 2});

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
    std::vector<FacetVertex> facet_ids;
    facet_ids.push_back(sorted_vertices[current_i].facet);

    for (int i = 1; i < sorted_vertices.size(); i++) {

        const auto& current_vertex = sorted_vertices[current_i];
        const auto& next_vertex = sorted_vertices[i];

        double d = (current_vertex.v - next_vertex.v).norm();
        if (d <= tol) {
            facet_ids.push_back(next_vertex.facet);
            continue;
        }

        res.push_back({current_vertex.v, std::move(facet_ids)});

        current_i = i;
        facet_ids = std::vector<FacetVertex>();
        facet_ids.push_back(sorted_vertices[current_i].facet);

    }

    return res;

}

std::vector<IndexedFacet> gather_indexed_facets(
        const std::vector<VertexAggregated>& va,
        const std::vector<Facet>& facets) {

    std::vector<std::array<int, 3>> vertices_of_facets;
    vertices_of_facets.assign(facets.size(), {-1, -1, -1});

    for (int i = 0; i < va.size(); i++) {
        const auto& v = va[i];
        for (const auto& f : v.facets) {
            vertices_of_facets[f.facet_id][f.vertex_id_within_facet] = i;
        }
    }

    std::vector<IndexedFacet> res;

    for (int i = 0; i < vertices_of_facets.size(); i++) {

        int idx_v1 = vertices_of_facets[i][0];
        int idx_v2 = vertices_of_facets[i][1];
        int idx_v3 = vertices_of_facets[i][2];

        Segment s1{idx_v1, idx_v2};
        Segment s2{idx_v2, idx_v3};
        Segment s3{idx_v3, idx_v1};

        IndexedFacet f{
            facets[i].normal,
            vertices_of_facets[i],
            {s1, s2, s3}
        };

        res.push_back(f);

    }

    return res;

}

