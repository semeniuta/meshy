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
    distances_[start_facet] = 0;

    while (!q.empty()) {

        auto node_index = q.front().index;
        auto node_type = q.front().node_type;
        q.pop();

        if (node_type == MeshGraphNodeType::facet) {

            int dist = distances_[node_index];

            if (dist_map_.find(dist) == dist_map_.end()) {
                // create new vector
                dist_map_[dist] = std::vector<int>();
            }

            dist_map_[dist].push_back(node_index);

        }

        const std::vector<unsigned int>& adj =
                (node_type == MeshGraphNodeType::facet) ?
                mesh_graph_.adj_facets_[node_index] :
                mesh_graph_.adj_segments_[node_index];

        std::vector<bool>& marked =
                (node_type == MeshGraphNodeType::facet) ?
                marked_segments_ :
                marked_facets_;

        std::vector<int>& edgeto =
                (node_type == MeshGraphNodeType::facet) ?
                edgeto_segments_ :
                edgeto_facets_ ;

        MeshGraphNodeType next_node_type =
                (node_type == MeshGraphNodeType::facet) ?
                MeshGraphNodeType::segment :
                MeshGraphNodeType::facet;

        for (unsigned int adjacent_node_index : adj) {

            if (!marked[adjacent_node_index]) {

                marked[adjacent_node_index] = true;

                edgeto[adjacent_node_index] = node_index;

                if (next_node_type == MeshGraphNodeType::facet) {
                    int prev_facet = edgeto_segments_[node_index];
                    int dist_so_far = distances_[prev_facet];
                    distances_[adjacent_node_index] = dist_so_far + 1;
                }

                q.push({adjacent_node_index, next_node_type});

            }

        }

    }

}

std::vector<int> BreadthFirstSearch::facets_around(unsigned int max_dist) {

    std::vector<int> facets;

    for (int d = 0; d < max_dist; d++) {

        for (int idx : dist_map_[d]) {
            facets.push_back(idx);
        }

    }

    return  facets;

}
