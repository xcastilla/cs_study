#include "../../data_structures/graph/graph.h"
#include <stack>
#include <vector>

std::pair<std::vector<int>, std::vector<state>> dfs(Graph *g, int start) {
    std::vector<state> nodeStatus(g->nNodes_, state::UNDISCOVERED);
    std::vector<int> depth(g->nNodes_, -1);

    // Initial status for the start node
    nodeStatus[start] = state::DISCOVERED;
    depth[start] = 0;
    dfs_(g, start, nodeStatus, depth);

    return std::pair<std::vector<int>, std::vector<state>>(depth, nodeStatus);
}

void dfs_(Graph *g, int node, std::vector<state>& nodeStatus, std::vector<int>& depth) {
    for(Edge& ed: g->adjList_[node]) {
        if(nodeStatus[ed.toIdx] == state::UNDISCOVERED) {
            nodeStatus[ed.toIdx] = state::DISCOVERED;
            depth[ed.toIdx] = depth[node] + 1;
            dfs_(g, ed.toIdx, nodeStatus, depth);
        }   
    }
    nodeStatus[node] = state::PROCESSED;
}

