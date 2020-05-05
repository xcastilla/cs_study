#include "../bfs.h"

int main(int argc, char* argv[]) {
    if(argc != 2) {
        std::cerr << "Usage: bfs [INPUT_FILE]" << std::endl;
        exit(1);
    } 
    Graph *g = Graph::fromFile(argv[1], true);
    std::cout << "Graph: " << *g;
    auto ret = bfs(g, 0);
    std::vector<int> parents = ret.first;
    std::cout << "Path from 0 to 5:" << std::endl;
    std::deque<int> path;
    int i = 5;
    path.push_front(i);
    while(parents[i] != -1) {
        i = parents[i];
        path.push_front(i);
    } 

    for(int el: path) {
        std::cout << el << " ";
    }
    std::cout << std::endl;

    delete g;
}