#include "../dfs.h"

int main(int argc, char* argv[]) {
    if(argc != 2) {
        std::cerr << "Usage: dfs [INPUT_FILE]" << std::endl;
        exit(1);
    } 
    Graph *g = Graph::fromFile(argv[1], true);
    std::cout << "Graph: " << *g;
    
    std::pair<std::vector<int>, std::vector<state>> ret = dfs(g, 0);
    auto depths = ret.first;

    std::cout << "Depths:" << std::endl;
    for(int i = 0; i < depths.size(); i ++) {
        std::cout << "Node " << i << ": " << depths[i] << std::endl;
    }

    delete g;
}