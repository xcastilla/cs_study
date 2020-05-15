#include "../../data_structures/graph/graph.h"
#include <limits>

std::pair<float, std::vector<int>> prim(Graph *g, int start) {
    // Vector to store the minimum spanning tree
    std::vector<int> parents(g->nNodes_, -1);
    // Vector keeping which vertexes form part of the MST
    std::vector<bool> inMST(g->nNodes_, false);
    // Vector keeping minimum weight edges
    std::vector<float> keys(g->nNodes_, std::numeric_limits<float>::max());

    float cost = 0;
    keys[start] = 0;
    for (int c = 0; c < g->nNodes_; c++) {
        // Find min key for a vertex not in the MST
        float min = std::numeric_limits<float>::max();
        int minIdx;
        for(int i = 0; i < g->nNodes_; i++) {
            if(!inMST[i] && keys[i] < min) {
                min = keys[i];
                minIdx = i;
            }
        }
        // Include the vertex in the MST and update cost
        inMST[minIdx] = true;
        cost += min;

        // Update keys for the vertexes adjacent to the selected vertex
        for(Edge &ed: g->adjList_[minIdx]) {
            if(!inMST[ed.toIdx] && ed.weight < keys[ed.toIdx]) {
                keys[ed.toIdx] = ed.weight;
                parents[ed.toIdx] = minIdx;
            }
        }
    }
    return std::pair<float, std::vector<int>>(cost, parents);
}