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

struct BipartiteDigraph {

    std::set<int> nodes_;
    std::vector<std::set<int>> adj_;

    explicit BipartiteDigraph(unsigned int size) : adj_(size) {}

    void add_edge(unsigned int a, unsigned int b) {

        if (a >= adj_.size() || b >= adj_.size()) {
            throw std::runtime_error("too high node index");
        }

        adj_[a].insert(b);
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
