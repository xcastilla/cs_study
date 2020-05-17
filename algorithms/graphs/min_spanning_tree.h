#include "../../data_structures/graph/graph.h"
#include "../../data_structures/union_find_set/union_find_set.h"
#include <limits>
#include <queue>

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


std::pair<float, std::vector<int>> kruskal(Graph *g) {
    // Cost of the MST
    float cost;
    // Vector to store the minimum spanning tree
    std::vector<int> parents(g->nNodes_, -1);
    // Union-find set used to track which components a vertex belongs to
    UnionFindSet components(g->nNodes_);
    // Comparison functor for the priority queue
    struct EdgeComparison {
        bool operator() (const Edge& lhs, const Edge& rhs) {
            return lhs.weight > rhs.weight;
        }
    };
    // Priority queue containing all edges sorted by increasing weight
    std::priority_queue<Edge, std::vector<Edge>, EdgeComparison> edges;
    for(int i = 0; i < g->nNodes_; i++) {
        for(Edge &ed: g->adjList_[i]) {
            edges.push(ed);
        }
    }

    // Iterate through the priority queue. For the next best edge, if 
    // its start and end nodes do not belong to the same component merge them
    for(int i = 0; i < g->nEdges_; i++) {
        while(!edges.empty()) {
            Edge ed = edges.top();
            edges.pop(); 
            if(!components.same_components(ed.fromIdx, ed.toIdx)) {
                parents[ed.toIdx] = ed.fromIdx;
                cost += ed.weight;
                components.merge(ed.fromIdx, ed.toIdx);
            }
        }
    }

    return std::pair<float, std::vector<int>>(cost, parents);
}