#include "../../data_structures/graph/graph.h"
#include <limits>

// Dijkstra is very similar to Prim. The main difference is the way we update the keys vector 
// in prim vs how we update distances in Dijkstra. In Dijkstra, we will accumulate the sum
// of the weights of all the edges traversed until we reached the current node into the distance
// value of it.
// If we only want the distance & path to node `to`, we can terminate early when we reach
// it. In this case, we will calculate the distance to the rest of nodes.
std::pair<float, std::vector<int>> dijkstra(Graph* g, int from, int to) {
    // Vector containing distances to each other node starting from node `from`
    std::vector<float> distances(g->nNodes_, std::numeric_limits<float>::max());
    // Vector containing the minimum paths
    std::vector<int> parents(g->nNodes_, -1);
    // Vector containing which nodes are already in the path
    std::vector<bool> inPath(g->nNodes_, false);

    distances[from] = 0;
    parents[from] = -1;
    for(int i = 0; i < g->nNodes_; i++) {
        float minDistance = std::numeric_limits<float>::max();
        int minIdx;
        for(int j = 0; j < g->nNodes_; j++) {
            if(!inPath[j] && distances[j] < minDistance) {
                minDistance = distances[j];
                minIdx = j;
            }
        }

        inPath[minIdx] = true;

        for(Edge& ed: g->adjList_[minIdx]) {
            if(!inPath[ed.toIdx] && distances[ed.fromIdx] + ed.weight < distances[ed.toIdx]) {
                parents[ed.toIdx] = ed.fromIdx;
                distances[ed.toIdx] = distances[ed.fromIdx] + ed.weight;
            }
        }
    }

    return std::pair<float, std::vector<int>>(distances[to], parents);
}