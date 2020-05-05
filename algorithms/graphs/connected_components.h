#include "bfs.h"

void combine(const std::vector<state>& reached, std::vector<bool>& processed) {
    for(int i = 0; i < processed.size(); i++) {
        if(processed[i] == false && reached[i] == state::PROCESSED) {
            processed[i] = true;
        }
    }
}

int connected_components(Graph *g) {
    std::vector<bool> processed(g->nNodes_, false);
    int components = 0;
    for(int i = 0; i < g->nNodes_; i++) {
        if(processed[i] == false) {
            components++;
            auto ret = bfs(g, i);
            std::vector<state> reached = ret.second;
            combine(reached, processed);
        }
    }
    return components;
}