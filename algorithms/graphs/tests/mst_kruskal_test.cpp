#include "../min_spanning_tree.h"

int main(int argc, char* argv[]) {
    if(argc != 2) {
        std::cerr << "Usage: prim [INPUT_FILE]" << std::endl;
        exit(1);
    } 
    Graph *g = Graph::fromFile(argv[1], true);
    auto ret = kruskal(g);
    std::vector<int> mst = ret.second;
    std::cout << "Graph:" << std::endl << *g;
    std::cout << "MST:" << std::endl;
    for(int i = 0; i < mst.size(); i ++) {
        std::cout << "Parent of " << i << ": " << mst[i] << std::endl;
    }
    std::cout << "Cost of MST: " << ret.first << std::endl;

    delete g;
}
