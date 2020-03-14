//
// Created by Oleksandr Semeniuta on 07/02/2020.
//

#ifndef MESHY_MESHGRAPH_H
#define MESHY_MESHGRAPH_H

#include "stl.h"
#include <set>
#include <map>
#include <array>

class Segment : public std::set<int> {
public:
    Segment(int p1, int p2) : std::set<int>{p1, p2} {};

    int p1() {
        auto it = begin();
        return *it;
    }

    int p2() {
        auto it = begin();
        it++;
        return *it;
    }
};

struct IndexedFacet {
    VectorXd normal;
    std::array<int, 3> vertices;
    std::array<Segment, 3> segments;
};

struct FacetVertex {
    int facet_id;
    int vertex_id_within_facet;
};

struct VertexInfo {
    VectorXd v;
    FacetVertex facet;
};

using VertexInfoComparator = std::function<bool(const VertexInfo&, const VertexInfo&)>;

struct VertexAggregated {
    VectorXd v;
    std::vector<FacetVertex> facets;
};

struct IndexedMesh {

    std::vector<IndexedFacet> facets_;
    std::vector<VertexAggregated> vertices_;
    std::vector<Segment> segments_;
    std::map<Segment, std::vector<int>> segments_adjacency_;
    VectorXd centroid_;

    explicit IndexedMesh(const std::vector<Facet>& facets);

};

struct MeshGraph {

    std::vector<std::vector<int>> adj_f2s_;
    std::vector<std::vector<int>> adj_s2f_;

    MeshGraph() = delete;

    MeshGraph(unsigned long n_facets, unsigned long n_segments)
        : adj_f2s_(n_facets), adj_s2f_(n_segments) {}

    void add_edge(unsigned int f, unsigned int s) {

        if (f >= adj_f2s_.size()) {
            throw std::runtime_error("too high facet index");
        }

        if (s >= adj_s2f_.size()) {
            throw std::runtime_error("too high segment index");
        }

        adj_f2s_[f].push_back(s);
        adj_s2f_[s].push_back(f);

    }

};

std::vector<Segment> detect_segment_anomalies(const IndexedMesh& im);

std::vector<VertexInfo> gather_vertices(const std::vector<Facet>& facets);

VertexInfoComparator create_comparator_joint(double tol=1e-6);

std::vector<VertexAggregated> aggregate_vertices(const std::vector<VertexInfo>& sorted_vertices, double tol=1e-6);

std::vector<IndexedFacet> gather_indexed_facets(
        const std::vector<VertexAggregated>& va,
        const std::vector<Facet>& facets);

std::vector<Segment> gather_segments_in_a_vector(const std::map<Segment, std::vector<int>>& segments);

#endif //MESHY_MESHGRAPH_H
