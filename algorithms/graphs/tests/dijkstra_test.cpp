#include "../dijkstra.h"
#include <list>

int main(int argc, char* argv[]) {
    if(argc != 2) {
        std::cerr << "Usage: dijkstra [INPUT_FILE]" << std::endl;
        exit(1);
    } 
    Graph *g = Graph::fromFile(argv[1], true);
    auto ret = dijkstra(g, 0, 5);
    std::vector<int> parents = ret.second;
    std::cout << "Graph:" << std::endl << *g;

    std::list<int> path;
    int cur = 5;
    while(true) {
        path.push_front(cur);
        if(cur == 0) break;
        cur = parents[cur];
    }
    std::cout << "Path:";
    for(int i: path) {
        std::cout << " " << i;
    }
    std::cout << std::endl;
    std::cout << "Cost of Path: " << ret.first << std::endl;

    delete g;
}
