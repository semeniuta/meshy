//
// Created by Oleksandr Semeniuta on 19/03/2020.
//

#ifndef MESHY_BREADTHFIRSTSEARCH_H
#define MESHY_BREADTHFIRSTSEARCH_H

#include "MeshGraph.h"
#include <queue>

class BreadthFirstSearch {

public:

    BreadthFirstSearch() = delete;

    explicit BreadthFirstSearch(const MeshGraph& mg)
        : mesh_graph_{mg},
          marked_facets_(mg.adj_facets_.size()),
          marked_segments_(mg.adj_segments_.size()),
          edgeto_facets_(mg.adj_facets_.size()),
          edgeto_segments_(mg.adj_segments_.size()) {};

    void bfs(unsigned int start_facet);

private:

    const MeshGraph& mesh_graph_;
    std::vector<bool> marked_facets_;
    std::vector<bool> marked_segments_;
    std::vector<int> edgeto_facets_;
    std::vector<int> edgeto_segments_;

};

struct BFSEntry {
    unsigned int index;
    MeshGraphNodeType node_type;
};


#endif //MESHY_BREADTHFIRSTSEARCH_H
