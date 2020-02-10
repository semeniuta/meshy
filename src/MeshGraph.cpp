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

