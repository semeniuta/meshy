//
// Created by Oleksandr Semeniuta on 07/02/2020.
//

#ifndef MESHY_MESHGRAPH_H
#define MESHY_MESHGRAPH_H

#include "stl.h"
#include <set>
#include <map>

class Segment : public std::set<int> {
public:
    Segment(int p1, int p2) : std::set<int>{p1, p2} {};
};

struct IndexedFacet {
    VectorXd normal;
    int v1;
    int v2;
    int v3;
    Segment s1;
    Segment s2;
    Segment s3;
};

struct VertexInfo {
    VectorXd v;
    int facet_id;
};

struct VertexAggregated {
    VectorXd v;
    std::vector<int> facets;
};

class MeshGraph {

private:
    std::vector<IndexedFacet> facets_;
    std::vector<VectorXd> vertices_;
    std::map<Segment, std::vector<int>> segments_;

public:
    MeshGraph(const std::vector<Facet>& facets);



};


#endif //MESHY_MESHGRAPH_H
