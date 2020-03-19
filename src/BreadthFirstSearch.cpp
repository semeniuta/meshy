//
// Created by Oleksandr Semeniuta on 19/03/2020.
//

#include "BreadthFirstSearch.h"
#include <iostream>

void BreadthFirstSearch::bfs(unsigned int start_facet) {

    if (start_facet >= mesh_graph_.adj_facets_.size()) {
        throw std::runtime_error("too high facet index");
    }

    std::queue<BFSEntry> q;

    q.push({start_facet, MeshGraphNodeType::facet});
    marked_facets_[start_facet] = true;

    while (!q.empty()) {

        std::cout << "[qsize: " << q.size() << "]\t";

        auto node_index = q.front().index;
        auto node_type = q.front().node_type;
        q.pop();

        if (node_type == MeshGraphNodeType::facet) {
            std::cout << "Facet ";
        } else {
            std::cout << "Segment ";
        }
        std::cout << node_index << "\n";

        const std::vector<unsigned int>& adj =
                (node_type == MeshGraphNodeType::facet) ?
                mesh_graph_.adj_facets_[node_index] :
                mesh_graph_.adj_segments_[node_index];

        std::vector<bool>& marked =
                (node_type == MeshGraphNodeType::facet) ?
                marked_segments_ :
                marked_facets_;

        MeshGraphNodeType next_node_type =
                (node_type == MeshGraphNodeType::facet) ?
                MeshGraphNodeType::segment :
                MeshGraphNodeType::facet;

        for (unsigned int adjacent_node_index : adj) {

            if (!marked[adjacent_node_index]) {

                marked[adjacent_node_index] = true;
                q.push({adjacent_node_index, next_node_type});

            }

        }

    }

}
