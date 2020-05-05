#include "../../data_structures/graph/graph.h"
#include <deque>
#include <vector>

std::pair<std::vector<int>, std::vector<state>> bfs(Graph *g, int start) {
    // Initialize aux structures
    std::vector<state> nodeState(g->nNodes_, state::UNDISCOVERED);
    std::vector<int> parents(g->nNodes_, -1);
    // Working queue
    std::deque<int> q;

    nodeState[start] = state::DISCOVERED;
    q.push_back(start);
    while(!q.empty()) {
        int cur = q.front();
        q.pop_front();
        for(Edge& ed: g->adjList_[cur]) {
            if(nodeState[ed.toIdx] == state::UNDISCOVERED) {
                nodeState[ed.toIdx] = state::DISCOVERED;
                parents[ed.toIdx] = cur;
                q.push_back(ed.toIdx);
            } 
        }
        nodeState[cur] = state::PROCESSED;
    }
    return std::pair<std::vector<int>, std::vector<state>>(parents, nodeState);
}
