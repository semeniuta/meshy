//
// Created by Oleksandr Semeniuta on 07/02/2020.
//

#ifndef MESHY_MESHGRAPH_H
#define MESHY_MESHGRAPH_H

#include "stl.h"
#include <set>

using Segment = std::set<int>;

struct IndexedFacet {
    VectorXd normal;
    int v1;
    int v2;
    int v3;
    Segment s1;
    Segment s2;
    Segment s3;
};

class MeshGraph {

private:

    std::vector<VectorXd> vertices_;




};


#endif //MESHY_MESHGRAPH_H
